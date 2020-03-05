PURPOSE:

 SD card datalogger for P1AM-100

 This example shows how to log data 
 to an SD card using the SD library.

 The circuit:
 * The SD card uses an internal SPI bus that is not present on the header. 
 * The SD library handles most of the pins, but you still need give it CS.
 ** CS - pin SDCARD_SS_PIN(28)

 created  24 Nov 2010
 modified 9 Apr 2012
 by Tom Igoe

 Modified by AutomationDirect for P1AM-100

 This example code is in the public domain.\
 http://www.arduino.cc/en/Tutorial/ButtonStateChange

 Required Library which needs to be installed.\
 https://github.com/facts-engineering/P1AM

 No Dependencies

****The information provided in the AutomationDirect knowledge base is provided "as is" without warranty of any kind. AutomationDirect disclaims all warranties, either express or implied, including the warranties of merchantability and fitness for a particular purpose. In no event shall AutomationDirect or its suppliers be liable for any damages whatsoever including direct, indirect, incidental, consequential, loss of business profits or special damages, even if AutomationDirect or its suppliers have been advised of the possibility of such damages. Some states do not allow the exclusion of limitation of liability for consequential or incidental damages so the foregoing limitation may not apply.****