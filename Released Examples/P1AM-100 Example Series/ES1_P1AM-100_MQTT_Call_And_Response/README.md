Purpose:

This example uses an MQTT broker to update the outputs of a P1-08TRS the inputs of a P1-08SIM. You can easily switch these out for any discrete input or output module.

I used shiftr.io for this example. This is a free MQTT broker that provides visualisation and is great for testing. If you want to use a different broker, update the broker string to the proper URL and update any login credentials.

Both the sending and receiving portions are included in this code, but these could be separated out into separate P1AM units or web interfaces.

With a little bit of modification, you can turn this example into a remote monitoring or combine it with Modbus TCP and connect an aging PLC to the cloud.

Dependencies:

P1AM - In the library manager or or on GitHub: https://github.com/facts-engineering/P1AM
ArduinoMqttClient - In the library manager or on GitHub: https://github.com/arduino-libraries/ArduinoMqttClient

Products Used:
P1AM-100
P1AM-ETH
P1-08SIM
P1-08TRS

****The information provided in the AutomationDirect knowledge base is provided "as is" without warranty of any kind. AutomationDirect disclaims all warranties, either express or implied, including the warranties of merchantability and fitness for a particular purpose. In no event shall AutomationDirect or its suppliers be liable for any damages whatsoever including direct, indirect, incidental, consequential, loss of business profits or special damages, even if AutomationDirect or its suppliers have been advised of the possibility of such damages. Some states do not allow the exclusion of limitation of liability for consequential or incidental damages so the foregoing limitation may not apply.****