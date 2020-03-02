  PURPOSE:

  Modbus TCP Client Multiple for P1AM-100/P1AM-ETH

  This sketch increments a register of a Modbus TCP server.
  Multiple Clients can be created and maintained, but the Library
  code is blocking.  So all delays in communictions will delay the 
  main loop() execution.

  This example uses Serial.print() to display status information.
  The Serial Monitor must be running for the sketch to start.

  Dependencies:

  https://github.com/arduino-libraries/ArduinoModbus \
  https://github.com/arduino-libraries/ArduinoRS485

  ******* The information provided in the AutomationDirect knowledge base is provided "as is" without warranty of any kind. AutomationDirect disclaims all warranties, either express or implied, including the warranties of merchantability and fitness for a particular purpose. In no event shall AutomationDirect or its suppliers be liable for any damages whatsoever including direct, indirect, incidental, consequential, loss of business profits or special damages, even if AutomationDirect or its suppliers have been advised of the possibility of such damages. Some states do not allow the exclusion of limitation of liability for consequential or incidental damages so the foregoing limitation may not apply.******
