/*
  P1AM Example Series #2 - Web Server Analog Input
  This example uses the P1AM-ETH shield to create a webserver that displays the input values of a P1-04ADL02 to a webpage.
  You can visit this webpage by entering it's IP address in a browser. the default address is 192.168.1.177. 
  This page will display the readings of all 4 channels in volts and in counts.
 
  You can find information on the P1-04ADL-2 and other modules here: https://facts-engineering.github.io/modules/P1-04ADL-2/P1-04ADL-2.html
  The analog input module we used is the P1-04ADL-2, though you can easily use any analog or discrete module as long as you tweak
  the conversions for your range and resolution.
  If you use another input module you may find our configuration tool handy for setting ranges: https://facts-engineering.github.io/config.html
  This example can easily be changed to display multiple modules and their data. This is great for any sort of remote monitoring you might want.
  If you're comfortable with basic web development you can spruce up the website and add plenty of features of your own design.
  
  created 18 Dec 2009
  by David A. Mellis
  
  modified 9 Apr 2012
  by Tom Igoe
  
  modified 02 Sept 2015
  by Arturo Guadalupi
  
  modified 13 Feb 2020
  by Kevin Cochran and Adam Cummick for FACTS Engineering
*/


#include <Ethernet.h>
#include <P1AM.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};  // P1AM-ETH have unique MAC IDs on their product label
IPAddress ip(192, 168, 1, 177); //IP Address our webpage will be at
EthernetServer server(80);  //initilizes ethernet using port 80

void setup() {
  
  Serial.begin(115200);
  while(!Serial); //Wait for Serial port to open. Remove this line if you want it to start automatically 
  while(!P1.init());  //Wait for module sign-on
  Ethernet.init(5);   //CS pin for P1AM-ETH
  Ethernet.begin(mac, ip); // start the Ethernet connection

  if (Ethernet.hardwareStatus() == EthernetNoHardware) { // Check for Ethernet hardware present
    Serial.println("Ethernet shield is missing. Please try again");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>"); //Start our HTML here
          client.println("<h1>Slot 1 Module Readings</h1>");  //Print the title
          client.println("<br>");
          client.println("<font size= \" 6 \" >"); //This line makes our text larger. Since we need to send the " character we have to "escape" it using a /"

          //----------------------This code handles the Analog values displayed on the webpage----------------------------

          for (int i = 1; i <= 4; i++) { //Run our loop for i at 1, 2, 3, and 4
            int inputCounts = P1.readAnalog(1, i); //reads analog data from slot 1 for the channel indiciated by our loop variable "i"
            Serial.println(inputCounts);  //Debug print to serial monitor
            float inputVolts = 10 * ((float)inputCounts / 8191);   //math to convert 13-bit counts to a floating point voltage value
            Serial.println(inputVolts); //Debug print to serial monitor

            client.print("Voltage input in counts is ");  //Print this text exactly
            client.print(inputCounts);  //Print our current reading on counts
            client.print(" for channel ");
            client.println(i);  //Print Current channel
            client.println("<br>"); //New line

            client.print("Voltage input in volts is "); //Print this text exactly
            client.print(inputVolts); //Print our current reading on Volts
            client.print(" for channel ");
            client.println(i);
            client.println("<br>"); //New line
            client.println("<br>");
          }

          //------------------------------------------------------------------------------------------------------------

          client.println("</font>");
          client.println("</html>");  //Our HTML ends here
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
