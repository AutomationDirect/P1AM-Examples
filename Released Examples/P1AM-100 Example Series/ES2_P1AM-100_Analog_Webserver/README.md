Purpose:

This example uses the P1AM-ETH shield to create a webserver that displays the input values of a P1-04ADL02 to a webpage.
You can visit this webpage by entering it's IP address in a browser. the default address is 192.168.1.177.
This page will display the readings of all 4 channels in volts and in counts.

You can find information on the P1-04ADL-2 and other modules here: https://facts-engineering.github.io/...1-04ADL-2.html

The analog input module we used is the P1-04ADL-2, though you can easily use any analog or discrete module as long as you tweak
the conversions for your range and resolution.
If you use another input module you may find our configuration tool handy for setting ranges: https://facts-engineering.github.io/config.html

This example can easily be changed to display multiple modules and their data. This is great for any sort of remote monitoring you might want.
If you're comfortable with basic web development you can spruce up the website and add plenty of features of your own design.

Dependencies:

P1AM - In the library manager or or on GitHub: https://github.com/facts-engineering/P1AM

Products Used:
P1AM-100
P1AM-ETH
P1-04ADL-2


****The information provided in the AutomationDirect knowledge base is provided "as is" without warranty of any kind. AutomationDirect disclaims all warranties, either express or implied, including the warranties of merchantability and fitness for a particular purpose. In no event shall AutomationDirect or its suppliers be liable for any damages whatsoever including direct, indirect, incidental, consequential, loss of business profits or special damages, even if AutomationDirect or its suppliers have been advised of the possibility of such damages. Some states do not allow the exclusion of limitation of liability for consequential or incidental damages so the foregoing limitation may not apply.****