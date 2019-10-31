#include "LEDPanel.h"

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
      SPI.transfer(0x00);
      SPI.transfer(0x00);
    }
    int data = ((row + 1) << 8) | LEDBuffer[row];
    SPI.transfer16(data);
    for (byte i = 0; i < panelDiff; i++) // for other panels, simply fill with zeros
    {
      SPI.transfer(0x00);
      SPI.transfer(0x00);
    }
    digitalWrite(_CSPin, HIGH);
  }
  Serial.println("End\n");
}

void LEDPanel::writeBuffer(byte *LEDBuffer)  // should be a pointer referencing 8*_panels bytes
{
  for (int i = 0; i < _panels; i++) // clear out registers before clocking data in
  {
    SPI.transfer(0x00);
    SPI.transfer(0x00);
  }
  for (int row = 0; row < 8; row++)
  {
    digitalWrite(_CSPin, LOW);
    for (int panel = 0; panel < _panels; panel++)
    {
      SPI.transfer(row + 1); // row address is row index + 1
      SPI.transfer(LEDBuffer[(panel * 8) + row]);
    }
    digitalWrite(_CSPin, HIGH);
  }
}

void LEDPanel::writeBufferToAll(byte *LEDBuffer)  // should be a pointer referencing 1*_panels bytes
{
  for(int panel = 0; panel<_panels; panel++)
  {
    writeBufferToPanel(*LEDBuffer,panel);
  }
}
