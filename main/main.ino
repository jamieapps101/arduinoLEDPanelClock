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
  Serial.begin(9600);
  panel.enable();
  //panel.writeBufferToPanel(J,0);
  //panel.writeBufferToPanel(A,1);
  //panel.writeString("ABCD",false);
  //panel.writeBuffer(cBuffer);
  panel.writeBufferToPanel(bBuffer,1);
  rotate2(bBuffer);
  panel.writeBufferToPanel(bBuffer,0);
  
  
}

byte * rotate(byte *panelBuffer)
{
  byte frameBuffer[8];
  for(int x = 0; x < 8; x++) // bc there are 8 rows
  {
    frameBuffer[x] = 0;
    for(int y = 0; y < 8; y++)//bc there are 8 bits for a byte
    {
      frameBuffer[y] = panelBuffer[x];
    }
    Serial.println(frameBuffer[x]);
  }
  return frameBuffer;
}

void rotate2(byte *inputBuffer)
{
  bool intInputBuffer[8][8];
  bool intOutputBuffer[8][8];
  for(int x = 0; x < 8; x++)
  {
    for(int y = 0; y< 8; y++)
    {
      intInputBuffer[x][y] = inputBuffer[x] && (1<<y);
    }
  }
  for(int x = 0; x < 8; x++)
  {
    inputBuffer[x] = 0;
    for(int y = 0; y < 8; y++)
    {
      inputBuffer[x] |= intInputBuffer[y][x] << y;
    }
  }
  
}

void loop() 
{
  

}
