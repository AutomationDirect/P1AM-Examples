/*
  Modbus TCP Client Simple for P1AM-100/P1AM-ETH

  This sketch toggles the coil of a Modbus TCP server connected
  on and off every second.
  
  This example uses Serial.print() to display status information.
  The Serial Monitor must be running for the sketch to start.

  Required Libraries which need to be installed.
  https://github.com/arduino-libraries/ArduinoModbus
  https://github.com/arduino-libraries/ArduinoRS485

  created 16 July 2018
  by Sandeep Mistry
  Modified by AutomationDirect for P1AM-100/P1AM-ETH
*/

#include <SPI.h>
#include <Ethernet.h>

#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>

byte mac[] = { //Use the Reserved MAC printed on the right-side label of your P1AM-ETH.
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(10, 11, 0, 177);//IP Address of the P1AM-ETH module.

EthernetClient client;
ModbusTCPClient modbusTCPClient(client);

IPAddress server(10, 11, 0,  22); //IP Addresses of the Server

void setup() {
  Ethernet.begin(mac, ip);
  modbusTCPClient.setTimeout(500);//Adjust Response Timeout from 30 seconds to 500 ms.
  Serial.begin(115200);
  while (!Serial) {};// wait for serial port to connect.
  Serial.println("Modbus TCP Client Simple Example");
  Serial.print("P1AM-ETH at IP:");
  Serial.println(ip);
}

void loop() {

  if (!modbusTCPClient.connected()) {// client not connected, start the Modbus TCP client
    Serial.print("Attempting to connect to Modbus TCP server at IP:");
    Serial.println(server);
    if (!modbusTCPClient.begin(server)) {
      Serial.println("Modbus TCP Client failed to connect!");
      delay(1000);
    } else {
      Serial.println("Modbus TCP Client connected");
    }
  } else {// client connected
    // write the value of 0x01, to the coil at address 0x00
    if (!modbusTCPClient.coilWrite(0x00, 0x01)) {
      Serial.print("Failed to write coil! ");
      Serial.println(modbusTCPClient.lastError());
    }

    // wait for 1 second
    delay(1000);
    
    // write the value of 0x00, to the coil at address 0x00
    if (!modbusTCPClient.coilWrite(0x00, 0x00)) {
      Serial.print("Failed to write coil! ");
      Serial.println(modbusTCPClient.lastError());
    }

    // wait for 1 second
    delay(1000);
  }
}
