/* Example: RTC NTP Sync
 * 
 * Synchronizes internal RTC to Google's NTP server for up to date time
 * Default Sync period in this code is once a day and the timezeone
 * is set for Eastern Standard Time
 * 
 * Based off of Arduino Udp NTP Client Example
 * and Arduino RTCZero Examples
 * 
 * Arduino Udp NTP Client Example
 * created 4 Sep 2010
 * by Michael Margolis
 * modified 9 Apr 2012
 * by Tom Igoe
 * modified 4 Mar 2020
 * by FACTS Engineering
 * 
 * This code is in the public domain.
 */


#include <Ethernet.h>
#include <Time.h>
#include <RTCZero.h>

// Enter a MAC address for your controller below.
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177); //IP Address of the P1AM-ETH module.
IPAddress subnet(255, 255, 0, 0); //IP Address of the network mask.
IPAddress gateway(192, 168, 1, 1); //IP Address of the gateway.
IPAddress dns(8, 8, 8, 8); //IP Address of the DNS server.
IPAddress timeServer(216, 239, 35, 8);  // Google's ntp server address

RTCZero rtc;  //rtc object to get the time from

#define MINUTE 60
#define HOUR 60 * MINUTE
#define DAY 24 * HOUR
const unsigned int ntpSyncTime = DAY; //86400 seconds. Resync every 24 hours.

//If your timezone isn't here, lookup an epoch offset list to find the correct value
const long EDT = -4*HOUR;// epoch offset for EDT timezone
const long EST = -5*HOUR;// epoch offset for EST timezone
const long PDT = -7*HOUR;// epoch offset for PDT timezone
const long PST = -8*HOUR;// epoch offset for PST timezone
long timeZoneOffset = EDT;  // timezone to report time from. 


unsigned int localPort = 8888;
const int NTP_PACKET_SIZE = 48; //size of ntp buffer
byte packetBuffer[NTP_PACKET_SIZE]; // buffer to store ntp data
EthernetUDP Udp;  // udp instance
unsigned long ntpLastUpdate = 0;  // var to store time of last sync

void setup()
{
  Serial.begin(115200);
  //Ethernet.begin(mac);//Use with a DHCP Server
  Ethernet.begin(mac,ip,dns,gateway,subnet);//Use for a fixed IP
  delay(1000);
  getTimeAndDate();   // initial sync from ntp server
  rtc.begin();  // start real-time-clock
}

void loop()
{
  checkForResync(); // See if we are due to resync with the NTP server
  printTime();  //Print current time and date from RTC
  delay(1000);
}
void checkForResync(){

  unsigned long currentEpoch = rtc.getEpoch();  // current total RTC seconds
  if (currentEpoch - ntpLastUpdate > ntpSyncTime) {   // resync time after  ntpSyncTime interval. We have this for every day above
    if(getTimeAndDate()) {  // try to resync time from ntp server
      Serial.println("Resync successful.");
    }
    else {
      Serial.println("Resync failed.");
    }
  }
  
}

void printTime() {  // print time and date from rtc
  Serial.print(rtc.getHours());
  printDigits(rtc.getMinutes());
  printDigits(rtc.getSeconds());
  Serial.println();
  Serial.print(rtc.getMonth());
  Serial.print("/");
  Serial.print(rtc.getDay());
  Serial.print("/");
  Serial.println(rtc.getYear());
  Serial.println();
}

void printDigits(int digits) {  // print preceding ':' and '0' for time
  Serial.print(':');
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address) {
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
int getTimeAndDate() {  // sync time on rtc from ntp server
  int flag = 0;
  Udp.begin(localPort);
  sendNTPpacket(timeServer); // send packet to ntp server
  delay(250);
  if (Udp.parsePacket()) {  // read response from ntp server
    Udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
    unsigned long highWord, lowWord, epoch;
    highWord = word(packetBuffer[40], packetBuffer[41]);
    lowWord = word(packetBuffer[42], packetBuffer[43]);
    epoch = highWord << 16 | lowWord;
    epoch = epoch - 2208988800 + timeZoneOffset;
    flag = 1;
    rtc.setEpoch(epoch);  // set rtc to up-to-date epoch
    ntpLastUpdate = epoch;  // set last time time was synced
  }
  return flag;  // return true on successful update
}
