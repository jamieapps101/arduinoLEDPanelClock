#ifndef LEDPANELDEF
#define LEDPANELDEF
#include <SPI.h>
#include "digitsDefs.h"

class LEDPanel
{
  public:
  LEDPanel(byte dataPin, byte clockPin, byte CSPin, byte panels);
  void setLEDIntensity(byte level);
  void enable();
  void disable();
  void writeBufferToPanel(byte *LEDBuffer,byte panel);
  void writeBuffer(byte *LEDBuffer);
  void writeBufferToAll(byte *LEDBuffer);
  void bufferRotate(byte *inputBuffer);
  void scrollRender(int index);
  void writeString(String input, bool scroll);
  void writeString_old(String input, bool scroll);
  byte getScrollWindowSize();
  byte getScrollWindowIndex();
  
  private:
  bool _scroll;
  byte _scrollWindowIndex;
  byte _maxScrollWindowIndex;
  byte _dataPin;
  byte _clockPin; 
  byte _CSPin; 
  byte _panels;
  void writeToAll(byte reg, byte data);
  byte *_totalFrameBuffer;
  byte *_frameBuffer;
};

// digit stuff
extern byte redef_A[8];
extern byte redef_B[8];
extern byte redef_C[8];
extern byte redef_D[8];
extern byte redef_E[8];
extern byte redef_F[8];
extern byte redef_G[8];
extern byte redef_H[8];
extern byte redef_I[8];
extern byte redef_L[8];
extern byte redef_V[8];
extern byte redef_P[8];
extern byte redef_M[8];

extern byte redef_one[8];
extern byte redef_two[8];
extern byte redef_three[8];
extern byte redef_four[8];
extern byte redef_five[8];
extern byte redef_six[8];
extern byte redef_seven[8];
extern byte redef_eight[8];
extern byte redef_nine[8];
extern byte redef_zero[8];
extern byte redef_blank[8];
extern byte redef_colon[8];

extern byte *getVerticalLetter(char character);

#endif
