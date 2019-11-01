// LED matrix driver for max7219
#include "LEDPanel.h"
//#include "digits.h"


/*
 * MOSI 11
 * SCK 13
 * ss 9 
 */

LEDPanel panel = LEDPanel(11, 13, 9, 4);


void setup()
{
  panel.disable();
  panel.setLEDIntensity(0);
  Serial.begin(9600);
  panel.enable();
  //panel.writeBufferToPanel(J,0);
  //panel.writeBufferToPanel(A,1);
  panel.writeString("ABCD",false);
  
}

void loop() 
{
  

}
