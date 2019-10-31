// LED matrix driver for max7219
#include "LEDPanel.h"
#include "digits.h"


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
  panel.writeBufferToPanel(J,0);
  panel.writeBufferToPanel(A,1);
}

void loop() 
{
  int sum = 0;
  int vals[] = {0,0,0,0,0};
  while(sum < 9999)
  {
    vals[4]++;
    for(int i = 4; i >= 1; i--)
    {
      if(vals[i] == 10)
      {
        vals[i] = 0;
        vals[i-1]++;
      }
    }
    sum = vals[1]*1000 + vals[2]*100 + vals[3]*10 + vals[4];
    panel.writeBufferToPanel(getNumbers(vals[1]),0);
    panel.writeBufferToPanel(getNumbers(vals[2]),1);
    panel.writeBufferToPanel(getNumbers(vals[3]),2);
    panel.writeBufferToPanel(getNumbers(vals[4]),3);
    delay(250);
  }
//    for(int i = 0; i < 10; i++)
//    {
//      panel.writeBufferToPanel(getNumbers(i),0);
//      panel.writeBufferToPanel(getNumbers((i+1)%10),1);
//      panel.writeBufferToPanel(getNumbers((i+2)%10),2);
//      panel.writeBufferToPanel(getNumbers((i+3)%10),3);
//      delay(500);
//    } 
}
