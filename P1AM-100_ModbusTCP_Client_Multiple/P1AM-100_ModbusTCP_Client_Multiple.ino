/*
  Modbus TCP Client Multiple for P1AM-100/P1AM-ETH

  This sketch increments a register of a Modbus TCP server.
  Multiple Clients can be created and maintained, but the Library
  code is blocking.  So all delays in communictions will delay the 
  main loop() execution.

  This example uses Serial.print() to display status information.
  The Serial Monitor must be running for the sketch to start.

  Required Libraries which need to be installed.
  https://github.com/arduino-libraries/ArduinoModbus
  https://github.com/arduino-libraries/ArduinoRS485
*/

#include <SPI.h>
#include <Ethernet.h>

#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>

byte mac[] = { //Use the Reserved MAC printed on the right-side label of your P1AM-ETH.
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(10, 11, 0, 177);//IP Address of the P1AM-ETH module.
int HR400001;
int HR400002;

EthernetClient clients[4];
ModbusTCPClient modbusTCPClient[4]={
  ModbusTCPClient(clients[0]),
  ModbusTCPClient(clients[1]),
  ModbusTCPClient(clients[2]),
  ModbusTCPClient(clients[3])
};

IPAddress servers[4]={//IP Addresses of the Servers
  IPAddress(10, 11, 0,  22),
  IPAddress(10, 11, 0,  23),
  IPAddress(10, 11, 0,  24),
  IPAddress(10, 11, 0,  25)
};

void setup() {
  Ethernet.begin(mac, ip);
  modbusTCPClient[0].setTimeout(500);//Adjust Response Timeout from 30 seconds to 500 ms.
  modbusTCPClient[1].setTimeout(500);//Adjust Response Timeout from 30 seconds to 500 ms.
  Serial.begin(115200);// wait for serial port to connect.
  while (!Serial) {};// wait for serial port to connect.
  Serial.println("Modbus TCP Client Multiple Example");
  Serial.print("P1AM-ETH at IP:");
  Serial.println(ip);
}

void loop() {

  if (!modbusTCPClient[0].connected()) {// client not connected, start the Modbus TCP client
    Serial.print("Attempting to connect to Modbus TCP server at IP:");
    Serial.println(servers[0]);
    if (!modbusTCPClient[0].begin(servers[0])) {
      Serial.println("Modbus TCP Client failed to connect!");
    } else {
      Serial.println("Modbus TCP Client connected");
    }
  } else {// client connected
    if (!modbusTCPClient[0].holdingRegisterWrite(0x00, HR400001++)) {
      Serial.print("Failed to write! ");
      Serial.println(modbusTCPClient[0].lastError());
    }
  }

  if (!modbusTCPClient[1].connected()) {// client not connected, start the Modbus TCP client
    Serial.print("Attempting to connect to Modbus TCP server at IP:");
    Serial.println(servers[1]);
    if (!modbusTCPClient[1].begin(servers[1])) {
      Serial.println("Modbus TCP Client failed to connect!");
    } else {
      Serial.println("Modbus TCP Client connected");
    }
  } else {// client connected
    if (!modbusTCPClient[1].holdingRegisterWrite(0x01, HR400002--)) {
      Serial.print("Failed to write! ");
      Serial.println(modbusTCPClient[1].lastError());
    }
  }
}