PURPOSE:

This example will use the "P1.isBaseActive" functions to demonstrate how the Base Controller 
can be monitored for a loss of 24V power. When this occurs, the Base Controller will need to be 
re-initialized using P1.init(). USB will need to be connected for serial communication and power.
  
This example works with all P1000 Series:
- Discrete output modules such as P1-08TRS, P1-08TD1, P1-16TR, etc.
- Discrete combo modules such as P1-15CDD1, P1-15CDD2, P1-16CDR, etc.  
  
This example will toggle channel 2 of slot 1 on and off every second after a base reset. 

To detect a base failure and re-init:
- 1: Load program in current form.
- 2: Connect USB cable from PC to P1AM-100.
- 3: Remove 24Vdc power and reapply. *Note: Open serial Monitor. You should have no errors.
- 4: Verify Slot 1 Channel 2 output is blinking.


 
To see a failure:
- 5: Comment out lines 55-62.
- 6: Upload to the P1AM-100.
- 7: Remove 24Vdc power & reapply.*Note: Open serial Monitor you will get a "Base Sync Timeout" error.
- 8: The output on Slot 1 Channel 2 should not be blinking.

It will also provide error feedback to the serial monitor on loss of 24Vdc.

*The information provided in the AutomationDirect knowledge base is provided "as is" without warranty of any kind. AutomationDirect disclaims all warranties, either express or implied, including the warranties of merchantability and fitness for a particular purpose. In no event shall AutomationDirect or its suppliers be liable for any damages whatsoever including direct, indirect, incidental, consequential, loss of business profits or special damages, even if AutomationDirect or its suppliers have been advised of the possibility of such damages. Some states do not allow the exclusion of limitation of liability for consequential or incidental damages so the foregoing limitation may not apply.
