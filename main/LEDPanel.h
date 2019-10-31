#include <SPI.h>

class LEDPanel
{
  public:
  LEDPanel(byte dataPin, byte clockPin, byte CSPin, byte panels);
  void setLEDIntensity(byte level);
  void enable();
  void disable();
  void writeBufferToPanel(byte *LEDBuffer,byte panel);
  void writeBuffer(byte *LEDBuffer);
  
  private:
  byte _dataPin;
  byte _clockPin; 
  byte _CSPin; 
  byte _panels;
  void writeToAll(byte reg, byte data);
};
