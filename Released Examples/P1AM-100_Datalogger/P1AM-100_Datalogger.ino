/*
 SD card datalogger for P1AM-100

 This example shows how to log data 
 to an SD card using the SD library.

 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin SDCARD_SS_PIN(28)

 created  24 Nov 2010
 modified 9 Apr 2012
 by Tom Igoe
 Modified by AutomationDirect for P1AM-100

 This example code is in the public domain.
 */

#include <SPI.h>
#include <SD.h>

const int chipSelect = SDCARD_SS_PIN;
int myInt1=0;
int myInt2=0;
int myInt3=0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  SD_Begin();
}

void loop() {
  // make a string for assembling the data to log:
  String dataString = "";

  delay(1000);
  myInt1+=1;
  myInt2+=10;
  myInt3+=100;
  dataString += String(myInt1);
  dataString += ",";
  dataString += String(myInt2);
  dataString += ",";
  dataString += String(myInt3);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.csv", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.csv");
    SD_Begin();    
  }
}

bool SD_Begin(void){
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return(0);
  }
  else {
    Serial.println("card initialized.");
    return(1);
  }
}