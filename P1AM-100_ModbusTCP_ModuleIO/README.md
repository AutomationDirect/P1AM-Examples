  PURPOSE:

  Ethernet Modbus TCP Server with P1 IO Modules
  for use with the P1AM-ETH module.

  This sketch creates a Modbus TCP Server for single connection.
  Slot1 Inputs are mapped to Modbus Input Bits 100001 to 100008.
  Slot2 Outputs are controlled by Modbus Coil Bits 000001 to 000008.
  Modbus Holding Register 400001 is always incrementing.

  The P1AM-100 cpu will require external 24vdc power
  for the IO modules to function.  This example uses
  Serial.print() to display status information.  The
  Serial Monitor must be running for the sketch to start.

  DEPENDENCIES:

  https://github.com/arduino-libraries/ArduinoModbus \
  https://github.com/arduino-libraries/ArduinoRS485

  ******The information provided in the AutomationDirect knowledge base is provided "as is" without warranty of any kind. AutomationDirect disclaims all warranties, either express or implied, including the warranties of merchantability and fitness for a particular purpose. In no event shall AutomationDirect or its suppliers be liable for any damages whatsoever including direct, indirect, incidental, consequential, loss of business profits or special damages, even if AutomationDirect or its suppliers have been advised of the possibility of such damages. Some states do not allow the exclusion of limitation of liability for consequential or incidental damages so the foregoing limitation may not apply.*****
