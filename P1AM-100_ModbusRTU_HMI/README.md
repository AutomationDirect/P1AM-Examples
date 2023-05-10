PURPOSE:

Modbus RTU Server for P1AM-SERIAL with access to P1 Input/Output Modules

This sketch creates a Modbus RTU Server (slave ID 10) on port 2 of the P1AM-SERIAL shield.  Port 2 is configured as RS232, 9600 baud rate, 8 data bits, even parity, and 1 stop bit.

Slot1 Inputs are mapped to Modbus Input Bits 100001 to 100008. Slot2 Outputs are controlled by Modbus Coil Bits 000001 to 000008. Modbus Holding Register 400001 increments every second (or 1000 milliseconds).

Commented out example code is also included for an analog input module at Slot 3 mapped to Modbus Input Registers 30001 to 30004 and an analog output module at Slot 4 mapped to Modbus Holding Registers 40003 to 40006.

The included EA3 .MGP file can be opened with the C-more Micro Programming Software (EA-MG-PGMSW ver. 4.51) for use with a C-micro HMI Operator Panel.

The P1AM-100 cpu will require external 24vdc power for the IO modules to function. This example uses Serial.print() to display status information. The Serial Monitor must be running for the sketch to start.

DEPENDENCIES:

https://github.com/facts-engineering/P1AM_Serial

*The information provided in the AutomationDirect knowledge base is provided "as is" without warranty of any kind. AutomationDirect disclaims all warranties, either express or implied, including the warranties of merchantability and fitness for a particular purpose. In no event shall AutomationDirect or its suppliers be liable for any damages whatsoever including direct, indirect, incidental, consequential, loss of business profits or special damages, even if AutomationDirect or its suppliers have been advised of the possibility of such damages. Some states do not allow the exclusion of limitation of liability for consequential or incidental damages so the foregoing limitation may not apply.