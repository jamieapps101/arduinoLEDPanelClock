// LED matrix driver for max7219
#include "LEDPanel.h"


/*
 * MOSI 11
 * SCK 13
 * ss 9 
 */

LEDPanel panel = LEDPanel(11, 13, 9, 4);
byte A[] = {
  B01100000, // 0x60
  B10010000, // 0x90
  B10010000, // 0x90
  B11110000, // 0xF0
  B10010000, // 0x90
  B10010000, // 0x90
  };

 byte J[] = {
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B10010000,
  B01100000,
  };


void setup()
{
  panel.enable();
  panel.setLEDIntensity(5);
  Serial.begin(9600);
}

void loop() {
  panel.writeBufferToPanel(J,0);
  delay(1000);
  panel.writeBufferToPanel(A,0);
  delay(1000);

}
