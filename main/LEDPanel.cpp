#include "LEDPanel.h"
#include "digits2.h"

LEDPanel::LEDPanel(byte dataPin, byte clockPin, byte CSPin, byte panels)
{
  // setup internal variables
  _dataPin = dataPin;
  _clockPin = clockPin;
  _CSPin = CSPin;
  _panels = panels;

  // ignoring input pins rn to use hardware SPI
  // start the SPI library:
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0); // commented to use defaults (0,2,3 all work equally well)
  pinMode(_CSPin, OUTPUT);
  // clear all registers
  for (byte reg = 0; reg <= 0x0F; reg++)
  {
    writeToAll(reg, 0);
  }


  // setup the max
  enable();
  setLEDIntensity(5);
  writeToAll(0x09, 0x00); // set decode mode to no decode
  writeToAll(0x0B, 0x07); // set scan limit to all on
  writeToAll(0x0F, 0x00); // turn displaytest off
  //disable();
}

void LEDPanel::writeToAll(byte reg, byte data)
{
  digitalWrite(_CSPin, LOW);
  for (int i = 0; i < _panels; i++)
  {
    SPI.transfer(reg); //Send register location first
    SPI.transfer(data);  //Send value to record into register secont
  }
  digitalWrite(_CSPin, HIGH);
}

void LEDPanel::setLEDIntensity(byte level) // 0-15
{
  level = level & 0x0F; // register only uses last 4 bits, so we shall blank out the first 12 using a mask
  writeToAll(0x0A, level); // send level to reg at 0x0A
}

void LEDPanel::enable()
{
  writeToAll(0x0C, 0x01); // write a 1 to the shutdown register to resume normal operation
}

void LEDPanel::disable()
{
  writeToAll(0x0C, 0x00); // write a 0 to the shutdown register to shutdown
}


void LEDPanel::writeBufferToPanel(byte *LEDBuffer, byte panel) // should be a pointer referencing 8 bytes
{

  byte panelDiff = panel; // assuming zero indexing
  for (byte row = 0; row < 8; row++) // for each row
  {
    digitalWrite(_CSPin, LOW);
    for (int i = 0; i < _panels; i++) // clear out registers before clocking data in
    {
      SPI.transfer16(0x00);
    }
    int data = ((row + 1) << 8) | LEDBuffer[row];
    Serial.print("address: ");
    Serial.println(row+1);
    Serial.print("data: ");
    Serial.println(LEDBuffer[row]);
    SPI.transfer16(data);
    Serial.print("padding: ");
    Serial.println(panelDiff);
    for (byte i = 0; i < panelDiff; i++) // for other panels, simply fill with zeros
    {
      Serial.print("Adding padd, ");
      SPI.transfer16(0x00);
    }
    Serial.println("");
    digitalWrite(_CSPin, HIGH);
  }
  Serial.println("End\n");
}

void LEDPanel::writeBuffer(byte *LEDBuffer)  // should be a pointer referencing 8*_panels bytes
{
  for (int i = 0; i < _panels; i++) // clear out registers before clocking data in
  {
    SPI.transfer16(0x00);
  }

  for(int panel = 0; panel < _panels; panel++)
  {
    Serial.println("sending:");
    for(int row = 0; row < 8; row++)
    {
      Serial.println( *(LEDBuffer+(panel*8)+row));
    }
    Serial.println("");
      writeBufferToPanel((LEDBuffer+(panel*8)),panel);
  }

}

void LEDPanel::writeBufferToAll(byte *LEDBuffer)  // should be a pointer referencing 1*_panels bytes
{
  for(int panel = 0; panel<_panels; panel++)
  {
    writeBufferToPanel(*LEDBuffer,panel);
  }
}


 void LEDPanel::writeString(String input, bool scroll)
 {
  // render the frame buffer
    // for each letter, create a buffer of any length
  byte panelBuffer[(_panels+2)*8]; // create an embty buffer with a little extra space than required
  for(int i = 0; i < input.length(); i++)
  {
    char currentChar = input.charAt(i);
    Serial.print("Current Char: ");
    Serial.println(currentChar);
//    byte charVal = (byte)(currentChar - '0');
    byte charVal = (byte)currentChar;
    byte *renderedChar;
    renderedChar = getVerticalLetter(charVal);
    byte byteIndex = i*6; // ie the character we're on times 5 char wdith + 1 space
    for(int a = 0; a < 5; a++)
    {
      panelBuffer[byteIndex+a] = renderedChar[a];
      Serial.println(renderedChar[a]);
    }
    Serial.println(" ");
  }

  
  
  byte frameBuffer[_panels*8];
  // transpose the frame buffer, aka going from ||||||||||| to horizontally stacked
  Serial.println("Frame Buffers");
  for(int panel =0; panel<_panels; panel++) // for now assume that we are not scrolling
  {
//    for(int j=0; j<8;j++)
//    {
//      frameBuffer[i+0] = ((1<<0) & panelBuffer[i*8+j]) << j;
//      frameBuffer[i+1] = ((1<<1) & panelBuffer[i*8+j]) << j;
//      frameBuffer[i+2] = ((1<<2) & panelBuffer[i*8+j]) << j;
//      frameBuffer[i+3] = ((1<<3) & panelBuffer[i*8+j]) << j;
//      frameBuffer[i+4] = ((1<<4) & panelBuffer[i*8+j]) << j;
//      frameBuffer[i+5] = ((1<<5) & panelBuffer[i*8+j]) << j;
//      frameBuffer[i+6] = ((1<<6) & panelBuffer[i*8+j]) << j;
//      frameBuffer[i+7] = ((1<<7) & panelBuffer[i*8+j]) << j;
//    }
    for(int row = 0; row < 8; row++) // bc there are 8 rows
    {
      frameBuffer[panel*8+row] = 0;
      for(int bitPos = 0; bitPos < 8; bitPos++)//bc there are 8 bits for a byte
      {
        frameBuffer[panel*8+row] |= panelBuffer[panel*8 + bitPos] >> bitPos;
      }
      Serial.println(frameBuffer[panel*8+row]);
    }
  }
  writeBuffer(frameBuffer);
 }

 
