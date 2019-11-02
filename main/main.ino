// LED matrix driver for max7219
#include "LEDPanel.h"
//#include "digits.h"


/*
 * MOSI 11
 * SCK 13
 * ss 9 
 */

LEDPanel panel = LEDPanel(11, 13, 9, 4);
byte aBuffer[] = {
  0x00,
  0x01,
  0x02,
  0x03,
  0x04,
  0x05,
  0x06,
  0x07,
  0x08,
  0x09,
  0x0a,
  0x0b,
  0x0c,
  0x0d,
  0x0e,
  0x0f,
  0x10,
  0x11,
  0x12,
  0x13,
  0x14,
  0x15,
  0x16,
  0x17,
  0x18,
  0x19,
  0x1a,
  0x1b,
  0x1c,
  0x1d,
  0x1e,
  0x1f,
  0x20,
  0x21,
};

byte bBuffer[] = {
  0x01,
  0x02,
  0x04,
  0x08,
  0x10,
  0x20,
  0x40,
  0x80
  };

 byte pBuffer[] = {
  1,
  3,
  7,
  31,
  24,
  0,
  0,
  0
  };


byte cBuffer[] = {
  0x01,
  0x02,
  0x04,
  0x08,
  0x10,
  0x20,
  0x40,
  0x80,
  0x01,
  0x02,
  0x04,
  0x08,
  0x10,
  0x20,
  0x40,
  0x80,
  0x01,
  0x02,
  0x04,
  0x08,
  0x10,
  0x20,
  0x40,
  0x80,
  0x01,
  0x02,
  0x04,
  0x08,
  0x10,
  0x20,
  0x40,
  0x80
  };

void setup()
{
  panel.disable();
  panel.setLEDIntensity(0);
  Serial.begin(115200);
  panel.enable();
//  panel.writeBufferToPanel(pBuffer,0);
//  panel.bufferRotate(pBuffer);
//  panel.writeBufferToPanel(pBuffer,1);
//  panel.bufferRotate(pBuffer);
//  panel.writeBufferToPanel(pBuffer,2);
//  panel.bufferRotate(pBuffer);
//  panel.writeBufferToPanel(pBuffer,3);
//  panel.bufferRotate(pBuffer); 
  panel.writeString("ABCDEFG",true);
}

void loop() 
{
  panel.scrollRender(-1);
  delay(500);
}
