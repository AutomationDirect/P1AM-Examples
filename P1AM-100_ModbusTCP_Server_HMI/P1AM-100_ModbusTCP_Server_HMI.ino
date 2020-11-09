/*
  Modbus TCP Server for P1AM-ETH with 
  access to P1 Input/Output Modules
  This sketch creates a Modbus TCP Server for up to 8 connections.
  Slot1 Inputs are mapped to Modbus Input Bits 100001 to 100008.
  Slot2 Outputs are controlled by Modbus Coil Bits 000001 to 000008.
  Modbus Holding Register 400001 is always incrementing.
  The P1AM-100 cpu will require external 24vdc power
  for the IO modules to function.  This example uses
  Serial.print() to display status information.  The
  Serial Monitor must be running for the sketch to start.
  Required Libraries which need to be installed.
  https://github.com/arduino-libraries/ArduinoModbus
  https://github.com/arduino-libraries/ArduinoRS485
*/

#include <SPI.h>
#include <Ethernet.h>
#include <P1AM.h>

#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>

byte mac[] = { //Use the �Reserved MAC� printed on the right-side label of your P1AM-ETH.
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(10, 11, 0, 177); //IP Address of the P1AM-ETH module.
boolean MB_C[16]; //Modbus Coil Bits
boolean MB_I[16]; //Modbus Input Bits
int MB_HR[16];    //Modbus Holding Registers
int MB_IR[16];    //Modbus Input Registers

EthernetServer server(502);
EthernetClient clients[8];
ModbusTCPServer modbusTCPServer;
int client_cnt;

void setup() {
  Serial.begin(115200);
  while (!Serial){}// wait for serial port to connect.
  Serial.println("Modbus TCP Server and Module I/O Example");
  while (!P1.init()){} ; //Wait for P1 Modules to Sign on   
  Ethernet.begin(mac, ip);
  server.begin(); // start the server to begin listening

  if (!modbusTCPServer.begin()) { // start the Modbus TCP server
    Serial.println("Failed to start Modbus TCP Server!");
    while (1); //If it can't be started no need to contine, stay here forever.
  }

  modbusTCPServer.configureCoils(0x00, 16);             //Coils
  modbusTCPServer.configureDiscreteInputs(0x00, 16);    //Discrete Inputs
  modbusTCPServer.configureHoldingRegisters(0x00, 16); //Holding Register Words
  modbusTCPServer.configureInputRegisters(0x00, 16);   //Input Register Words

  Serial.println("Done with setup()");
}

void loop() {
    EthernetClient newClient = server.accept(); //listen for incoming clients
    if (newClient) { //process new connection if possible
    for (byte i = 0; i < 8; i++) { //Eight connections possible, find first available.
      if (!clients[i]) {
        clients[i] = newClient;
        client_cnt++;
        Serial.print("Client Accept:"); //a new client connected
        Serial.print(newClient.remoteIP());
        Serial.print(" , Total:");
        Serial.println(client_cnt);
        break;
        }
      }
    }

    //If there are packets available, receive them and process them.
    for (byte i = 0; i < 8; i++) {
      if (clients[i].available()) { //if data is available
        modbusTCPServer.accept(clients[i]); //accept that data
        modbusTCPServer.poll();// service any Modbus TCP requests, while client connected
        }
    }
    for (byte i = 0; i < 8; i++) { // Stop any clients which are disconnected
      if (clients[i] && !clients[i].connected()) {
        clients[i].stop();
        client_cnt--;
        Serial.print("Client Stopped, Total: ");
        Serial.println(client_cnt);
      }
    }

  //Read from P1-08SIM Input Module and then write into Modbus memory
  int Slot1_Inputs = P1.readDiscrete(1,0);  //Read from P1-08SIM Input Simulator Module
  for (int i=0;i<8;i++){
    MB_I[i]=Slot1_Inputs&(1<<i);
  }
  updateInputs(); //Write current state of the Modbus Inputs into MB_I[]

  //Read from Analog Input Modules and then write into Modbus memory
  updateInputRegisters(); //Write current state of the Modbus Inputs into MB_IR[]

  updateCoils(); //Read current state of the Modbus Coils into MB_C[]
  for (int i=0;i<8;i++){
    P1.writeDiscrete(MB_C[i],2,i+1);//Data,Slot,Channel ... Channel is one-based.
  }
  
  updateHoldingRegisters(); //Read current state of the Modbus Registers into MB_HR[]
  MB_HR[0]++; //TestApp, increment the Modbus Register 400000 just to have data changing.
  modbusTCPServer.holdingRegisterWrite(0,MB_HR[0]);
}

void updateCoils() {//Read the Coil bits from the Modbus Library
  for (int i=0;i<16;i++){
    MB_C[i] = modbusTCPServer.coilRead(i);
  }
}

void updateInputs() { //Write the Input bits to the Modbus Library
  for (int i=0;i<16;i++){
    modbusTCPServer.discreteInputWrite(i,MB_I[i]);
  }
}

void updateHoldingRegisters() {//Read the Holding Register words from the Modbus Library
  for (int i=0;i<16;i++){
    MB_HR[i] = modbusTCPServer.holdingRegisterRead(i);
  }
}

void updateInputRegisters() { //Write the Input Registers to the Modbus Library
  for (int i=0;i<16;i++){
    modbusTCPServer.inputRegisterWrite(i,MB_IR[i]);
  }
}
