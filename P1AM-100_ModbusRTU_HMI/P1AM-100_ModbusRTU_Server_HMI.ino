/*
  created 18 July 2018
  by Sandeep Mistry
  
  modified 28 April 2023
  by AutomationDirect.com
  
  Modbus RTU Server for P1AM-SERIAL with access to P1 Input/Output Modules
  This sketch creates a Modbus RTU Server on Port 2 of the P1AM-SERIAL shield.

  Slot 1 Inputs are mapped to Modbus Input Bits 10001 to 10008.
  Slot 2 Outputs are controlled by Modbus Coil Bits 00001 to 00008.
  Slot 3 Analog Inputs are mapped to Modbus Input Registers 30001 to 30004 and are disabled by default.
  Slot 4 Analog Outputs are controlled by Modbus Holding Registers 40003 to 40006 and are disabled by default.
  Modbus Holding Register 40001 increments once every second.

  The P1AM-100 cpu will require external 24vdc power for the IO modules to function.  
  This example uses Serial.print() to display status information. 
  The Serial Monitor must be running for the sketch to start.
  
  Serial wiring between port 1 RJ12 connector on HMI
  and port 2 terminal block on P1AM-SERIAL shield is as follows:
  RJ12 pin 1 - terminal G
  RJ12 pin 3 - terminal TX/-
  RJ12 pin 4 - terminal RX/+

  For wiring, consider using a ZL-RJ12-CBL-2 cable and ZL-RTB-RJ12 terminal block
    
  Required Libraries which need to be installed.
  https://github.com/facts-engineering/P1AM_Serial
*/

#include <P1AM.h>         //include the FACTS Engineering P1AM library
#include <P1AM_Serial.h>  //include the FACTS Engineering P1AM-SERIAL library
#include <ArduinoModbus.h>

boolean MB_C[16];              //Modbus Coil Bits
boolean MB_I[16];              //Modbus Input Bits
int MB_HR[16];                 //Modbus Holding Registers
int MB_IR[16];                 //Modbus Input Registers
unsigned long lastMillis = 0;  // used to reference last time millis() was called

ModbusRTUServerClass port2_server(Port2);

void setup() {
  Serial.begin(115200);
  while (!Serial);  // wait for serial port to connect.
  Serial.println("Modbus RTU Server and Module I/O Example");
  while (!P1.init());  //Wait for P1 Modules to Sign on

  serial_port_config(2, RS232_MODE);  // Set port 2 to RS232 prior to starting modbus client

  // start the Modbus RTU server on Port 2, with (slave) id 10, 9600 baud rate, 8 data bits, Even parity, 1 stop bit
  // see https://www.arduino.cc/reference/en/language/functions/communication/serial/begin/ for other configurations
  if (!port2_server.begin(10, 9600, SERIAL_8E1)) {
    Serial.println("Failed to start Modbus RTU Server!");
    while (1);
  }

  // configure Modbus addresses
  port2_server.configureCoils(0x00, 16);             //Coils
  port2_server.configureDiscreteInputs(0x00, 16);    //Discrete Inputs
  port2_server.configureHoldingRegisters(0x00, 16);  //Holding Register Words
  port2_server.configureInputRegisters(0x00, 16);    //Input Register Words

  Serial.println("Done with setup()");
}

void loop() {

  // poll for Modbus RTU requests
  int packetReceived = port2_server.poll();

  //If there are packets available, receive them and process them.
  if (packetReceived) {
    updateCoils();             //Read the Coil bits from the Modbus Library
    updateHoldingRegisters();  //Read the Holding Register words from the Modbus Library
    for (int i = 0; i < 8; i++) {
        P1.writeDiscrete(MB_C[i], 2, i + 1);  //Data,Slot,Channel ... Channel is one-based.
    }
  }

  //Read from Discrete Input Module and then write into Modbus memory
  int Slot1_Inputs = P1.readDiscrete(1);  //Read from Discrete Input Module in slot 1
  for (int i = 0; i < 8; i++) {
    MB_I[i] = Slot1_Inputs & (1 << i);
  }
  updateInputs();  //Write current state of the Modbus Inputs into MB_I[]

  //To Read from Analog Input Module in slot 3 and then write into Modbus memory, uncomment the following 4 lines
  //  for (int i=0; i<4; i++){
  //    MB_IR[i] = P1.readAnalog(3, i+1); //Slot, Channel (channel is one-based)
  //  }
  //  updateInputRegisters(); //Write current state of the Modbus Inputs into MB_IR[]

  //To write the values in Modbus Registers 40003, 40004, 40005, & 40006 to Analog Output Module channels in slot 4,
  //uncomment the following 3 lines
  //    for (int i=0; i<4; i++){
  //      P1.writeAnalog(MB_HR[2+i], 4, i+1); //Value, Slot, Channel (channel is one-based)
  //    }
  //NOTE: for P1.writeAnalog, the value being written to the analog output channel must be within the resolution of the module
  //(e.g. 12-bit resolution is 0-4095)

  //Compare current millisecond value to previous to execute every 1 second
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    MB_HR[0]++;
    port2_server.holdingRegisterWrite(0, MB_HR[0]); //increment the Modbus Register 40001 every second just to have data changing.
  }
}

void updateCoils() {  //Read the Coil bits from the Modbus Library
  for (int i = 0; i < 16; i++) {
    MB_C[i] = port2_server.coilRead(i);
  }
}

void updateInputs() {  //Write the Input bits to the Modbus Library
  for (int i = 0; i < 16; i++) {
    port2_server.discreteInputWrite(i, MB_I[i]);
  }
}

void updateHoldingRegisters() {  //Read the Holding Register words from the Modbus Library
  for (int i = 0; i < 16; i++) {
    MB_HR[i] = port2_server.holdingRegisterRead(i);
  }
}

void updateInputRegisters() {  //Write the Input Registers to the Modbus Library
  for (int i = 0; i < 16; i++) {
    port2_server.inputRegisterWrite(i, MB_IR[i]);
  }
}
