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
  Serial.begin(9600);
  panel.enable();
  //panel.writeBufferToPanel(J,0);
  //panel.writeBufferToPanel(A,1);
  //panel.writeString("ABCD",false);
  //panel.writeBuffer(cBuffer);
  panel.writeBufferToPanel(pBuffer,0);
  rotate2(pBuffer);
  panel.writeBufferToPanel(pBuffer,1);
  rotate2(pBuffer);
  panel.writeBufferToPanel(pBuffer,2);
  rotate2(pBuffer);
  panel.writeBufferToPanel(pBuffer,3);
  rotate2(pBuffer);
  
  
  
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
  bool temp[8][8];
  Serial.println("Input");
  for(int x = 0; x < 8; x++)
  {
    Serial.print(inputBuffer[x]);
    Serial.print(" --> ");
    for(int y = 0; y < 8; y++)
    {
       temp[x][y] = inputBuffer[x] & (1<<y);
       Serial.print(inputBuffer[x],BIN);
       Serial.print(",");
       Serial.print((1<<y),BIN);
       Serial.print("=");
       Serial.print(temp[x][y]);
       Serial.print("  ");
    }
    Serial.println();
  }
  bool temp2[8][8];
  Serial.println("Output");
  for(int x = 0; x < 8; x++)
  {
    for(int y = 0; y < 8; y++)
    {
       temp2[x][y] = temp[y][7-x];
       Serial.print(temp2[x][y]);
       Serial.print(" ");
    }
    Serial.println("");
  }
  Serial.println("Output Buffer");
  for(int x = 0; x < 8; x++)
  {
    inputBuffer[x] = 0;
    for(int y = 0; y < 8; y++)
    {
       inputBuffer[x] |= (temp2[x][y]) << y;
       Serial.print(temp2[x][y]);
       Serial.print("  ");
    }
    Serial.println("");
  }
  
}

void loop() 
{
  

}
