PURPOSE:  

Modbus TCP Server for P1AM-ETH with access to P1 Input/Output Modules

This sketch creates a Modbus TCP Server for up to 8 connections.
Slot1 Inputs are mapped to Modbus Input Bits 100001 to 100008.
Slot2 Outputs are controlled by Modbus Coil Bits 000001 to 000008.
Modbus Holding Register 400001 is always incrementing.

1.) The included EAP9 file can be opened with the C-more Programming Software (EA9-PGMSW ver. 6.52) for use with a C-more HMI Operator Panel.

2.) The included EA3 .MGP file can be opened with the C-more Micro Programming Software (EA-MG-PGMSW ver. 4.40) for use with a C-micro HMI Operator Panel.

  The P1AM-100 cpu will require external 24vdc power for the IO modules to function.  This example uses Serial.print() to display status information.  The
  Serial Monitor must be running for the sketch to start.


DEPENDENCIES:

https://github.com/arduino-libraries/ArduinoModbus 
https://github.com/arduino-libraries/ArduinoRS485
  
  ******The information provided in the AutomationDirect knowledge base is provided "as is" without warranty of any kind. AutomationDirect disclaims all warranties, either express or implied, including the warranties of merchantability and fitness for a particular purpose. In no event shall AutomationDirect or its suppliers be liable for any damages whatsoever including direct, indirect, incidental, consequential, loss of business profits or special damages, even if AutomationDirect or its suppliers have been advised of the possibility of such damages. Some states do not allow the exclusion of limitation of liability for consequential or incidental damages so the foregoing limitation may not apply.*****
  
