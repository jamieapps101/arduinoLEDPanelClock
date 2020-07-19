#include "LEDPanel.h"

LEDPanel::LEDPanel(byte dataPin, byte clockPin, byte CSPin, byte panels)
{
  // setup internal variables
  _dataPin = dataPin;
  _clockPin = clockPin;
  _CSPin = CSPin;
  _panels = panels;
  _scroll = false;

  // ignoring input pins rn to use hardware SPI
  // start the SPI library:
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  //  SPI.setDataMode(SPI_MODE0); // commented to use defaults (0,2,3 all work equally well)
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
    SPI.transfer16(data);
    for (byte i = 0; i < panelDiff; i++) // for other panels, simply fill with zeros
    {
      SPI.transfer16(0x00);
    }
    digitalWrite(_CSPin, HIGH);
  }
}

void LEDPanel::writeBuffer(byte *LEDBuffer)  // should be a pointer referencing 8*_panels bytes
{
  for (int i = 0; i < _panels; i++) // clear out registers before clocking data in
  {
    SPI.transfer16(0x00);
  }

  for(int panel = 0; panel < _panels; panel++)
  {
//    Serial.println("sending:");
//    for(int row = 0; row < 8; row++)
//    {
//      Serial.println( *(LEDBuffer+(panel*8)+row));
//    }
    //Serial.println("");
      writeBufferToPanel((LEDBuffer+(panel*8)),panel);
  }

}

void LEDPanel::writeBufferToAll(byte *LEDBuffer)  // should be a pointer referencing 1*_panels bytes
{
  for(int panel = 0; panel<_panels; panel++)
  {
    writeBufferToPanel(LEDBuffer,panel);
  }
}


 void LEDPanel::writeString_old(String input, bool scroll)
 {
  // render the frame buffer
    // for each letter, create a buffer of any length
  byte *panelBuffer;
  byte *panelBufferModified;
  byte maxScrollWindowIndex_temp;
  byte bufferPanelRowsEquiv = 0;
  byte panelBufferRows = 0;
  if(scroll == false)
  {
    byte rows = _panels*8;
    panelBuffer = (byte*)calloc(rows,sizeof(byte));
    bufferPanelRowsEquiv = rows;
  }
  else
  {
    // enough for all letters plus blank screen at end of scroll
    byte rows = _panels*8 + (input.length()*5);
    panelBuffer = (byte*)calloc(rows,sizeof(byte)); 
    panelBufferModified = (byte*)calloc(rows,sizeof(byte));
    maxScrollWindowIndex_temp = _panels*8 + ceil((input.length()*5)/8)*8;
    bufferPanelRowsEquiv = _panels*8 + (input.length()*5);
  }
  
  for(int i = 0; i < input.length(); i++)
  {
    char currentChar = input.charAt(i);
    byte charVal = (byte)currentChar;
    byte *renderedChar;
    renderedChar = getVerticalLetter(charVal);
    byte byteIndex = i*6; // ie the character we're on times 5 char wdith + 1 space
    for(int a = 0; a < 5; a++)
    {
      panelBuffer[byteIndex+a] = renderedChar[a];
    }
    panelBuffer[byteIndex+5] = 0; 
  }

//  byte frameBuffer[_panels*8];
  // transpose the frame buffer, aka going from ||||||||||| to horizontally stacked
//  if(scroll == true)
//  {
//    for(
//  }
  
  for(int panel =0; panel<(bufferPanelRowsEquiv/8); panel++) // for now assume that we are not scrolling
  {
    bufferRotate(panelBuffer+(panel*8));
  }
  writeBuffer(panelBuffer);
  // deal with scroll settings if enabled:
  if(scroll == true)
  {
    _scroll = true;
    _scrollWindowIndex = 0;
    _frameBuffer = panelBuffer;
    _maxScrollWindowIndex = maxScrollWindowIndex_temp;
  }
  else
  {
    _scroll = false;
    _scrollWindowIndex = 0;
    _maxScrollWindowIndex = 0;
    free(_frameBuffer);
  }
 }

 
 void LEDPanel::writeString(String input, bool scroll)
 {

  // see if scroll required
  if(scroll == true && (input.length()*6) <= _panels*8)
  {
    scroll = false;
  }
  // initialise variables
  byte *panelBuffer;
  byte *panelBufferModified;
  byte maxScrollWindowIndex_temp;
  byte panelBufferRows = 0;
  // allocate space
  if(scroll == false)
  {
    panelBufferRows =  _panels*8;
    panelBuffer = (byte*)calloc(panelBufferRows,sizeof(byte));
  }
  else
  {
    // enough for all letters plus blank screen at end of scroll
    panelBufferRows = _panels*8 + ceil((input.length()*6)/8)*8;
    panelBuffer = (byte*)calloc(panelBufferRows,sizeof(byte)); 
    panelBufferModified = (byte*)calloc(panelBufferRows,sizeof(byte));
  }

  // convert string to vertical stacked array
  for(int i = 0; i < input.length(); i++)
  {
    char currentChar = input.charAt(i);
    byte charVal = (byte)currentChar;
    byte *renderedChar;
    renderedChar = getVerticalLetter(charVal);
    byte byteIndex = i*6; // ie the character we're on times 5 char wdith + 1 space
    for(int a = 0; a < 5; a++)
    {
      panelBuffer[byteIndex+a] = renderedChar[a];
    }
    panelBuffer[byteIndex+5] = 0; 
  }

  // make copy to preserve original
  if(scroll == true)
  {
    for(int row = 0; row < panelBufferRows; row++)
    {
      panelBufferModified[row] = panelBuffer[row];
    }
    for(int panel =0; panel<(panelBufferRows/8); panel++)
    {
      bufferRotate(panelBufferModified+(panel*8));
    }
    writeBuffer(panelBufferModified);
    free(panelBufferModified);
  }
  else
  {
    for(int panel =0; panel<(panelBufferRows/8); panel++)
    {
      bufferRotate(panelBuffer+(panel*8));
    }
    writeBuffer(panelBuffer);
  }
    // deal with scroll settings if enabled:
  if(scroll == true)
  {
    _scroll = true;
    _scrollWindowIndex = 0;
    _frameBuffer = panelBuffer;
    _maxScrollWindowIndex = panelBufferRows-_panels*8;
    Serial.print("panelBufferRows: ");
    Serial.println(panelBufferRows);
    Serial.print("_panels*8: ");
    Serial.println(_panels*8);
    Serial.print("_maxScrollWindowIndex: ");
    Serial.println(_maxScrollWindowIndex);
  }
  else
  {
    _scroll = false;
    _scrollWindowIndex = 0;
    _maxScrollWindowIndex = 0;
    free(panelBuffer);
    free(_frameBuffer);
  }
 }


void LEDPanel::bufferRotate(byte *inputBuffer)
{
  bool temp[8][8];
  for(int x = 0; x < 8; x++)
  {
    for(int y = 0; y < 8; y++)
    {
       temp[x][y] = inputBuffer[x] & (1<<y);
    }
  }
  bool temp2[8][8];
  for(int x = 0; x < 8; x++)
  {
    for(int y = 0; y < 8; y++)
    {
      // select line below as required
       //temp2[x][y] = temp[7-x][7-y];
       temp2[x][y] = temp[7-y][7-x];
    }
  }
  for(int x = 0; x < 8; x++)
  {
    inputBuffer[x] = 0;
    for(int y = 0; y < 8; y++)
    {
       inputBuffer[x] |= (temp2[x][y]) << y;
    }
  } 
}


void LEDPanel::scrollRender(int index)
{
  if(_scroll == true)
  {
    if(index > 0 && index < _maxScrollWindowIndex)
    {
       _scrollWindowIndex = index;
    }
    byte *temp;
    temp = (byte*)calloc(_panels*8,sizeof(byte)); 
    for(int row = 0; row < _panels*8; row++)
    {
      temp[row] = _frameBuffer[row+_scrollWindowIndex];
    }
    for(int panel = 0; panel < _panels; panel++)
    {
      bufferRotate(temp+(panel*8));
    }
    writeBuffer(temp);
    free(temp);
    _scrollWindowIndex++;
    if(_scrollWindowIndex >= _maxScrollWindowIndex)
    {
      _scrollWindowIndex = 0;
    }
  }
}

byte LEDPanel::getScrollWindowSize()
{
  return _maxScrollWindowIndex;
}

byte LEDPanel::getScrollWindowIndex()
{
  return _scrollWindowIndex;
}




byte redef_A[] = {
  B01111110,
  B10010000,
  B10010000,
  B10010000,
  B01111110,
  B00000000,
  B00000000,
  B00000000
};

byte redef_B[] = {
  B11111110,
  B10010010,
  B10010010,
  B10010010,
  B01101100,
  B00000000,
  B00000000,
  B00000000
};


byte redef_C[] = {
  B01111100,
  B10000010,
  B10000010,
  B10000010,
  B01000100,
  B00000000,
  B00000000,
  B00000000
};


byte redef_D[] = {
  B11111110,
  B10000010,
  B10000010,
  B10000010,
  B01111100,
  B00000000,
  B00000000,
  B00000000
};

byte redef_E[] = {
  B11111110,
  B10010010,
  B10010010,
  B10010010,
  B10000010,
  B00000000,
  B00000000,
  B00000000
};

byte redef_F[] = {
  B11111110,
  B10010000,
  B10010000,
  B10010000,
  B10000000,
  B00000000,
  B00000000,
  B00000000
};

byte redef_G[] = {
  B01111100,
  B10000010,
  B10000010,
  B10010010,
  B01011100,
  B00000000,
  B00000000,
  B00000000
};

byte redef_H[] = {
  B11111110,
  B00010000,
  B00010000,
  B00010000,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};

byte redef_I[] = {
  B00000000,
  B10000010,
  B11111110,
  B10000010,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

byte redef_L[] = {
  B11111110,
  B00000010,
  B00000010,
  B00000010,
  B00000010,
  B00000000,
  B00000000,
  B00000000
};

byte redef_V[] = {
  B11111000,
  B00000100,
  B00000010,
  B00000100,
  B11111000,
  B00000000,
  B00000000,
  B00000000
};


byte redef_P[] = {
  B11111110,
  B10001000,
  B10001000,
  B10001000,
  B01110000,
  B00000000,
  B00000000,
  B00000000
};

byte redef_M[] = {
  B11111110,
  B01000000,
  B00100000,
  B01000000,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};

byte redef_one[] = {
  B00000000,
  B01000000,
  B11111110,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

byte redef_two[] = {
  B01000010,
  B10000010,
  B10000110,
  B10001010,
  B01110010,
  B00000000,
  B00000000,
  B00000000
};

byte redef_three[] = {
  B10000010,
  B10010010,
  B10010010,
  B10010010,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};

byte redef_four[] = {
  B11110000,
  B00010000,
  B00010000,
  B00010000,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};


byte redef_five[] = {
  B11110000,
  B10010010,
  B10010010,
  B10010010,
  B10001110,
  B00000000,
  B00000000,
  B00000000
};

byte redef_six[] = {
  B11111110,
  B10010010,
  B10010010,
  B10010010,
  B10011110,
  B00000000,
  B00000000,
  B00000000
};

byte redef_seven[] = {
  B10000000,
  B10000000,
  B10001110,
  B10010000,
  B11100000,
  B00000000,
  B00000000,
  B00000000
};

byte redef_eight[] = {
  B11111110,
  B10010010,
  B10010010,
  B10010010,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};
byte redef_nine[] = {
  B11110010,
  B10010010,
  B10010010,
  B10010010,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};

byte redef_zero[] = {
  B11111110,
  B10000010,
  B10000010,
  B10000010,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};

byte redef_blank[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

byte redef_colon[] = {
  B00000000,
  B00000000,
  B01000100,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

byte *getVerticalLetter(char character)
{
  switch(character)
  {
    case 'A':
      return redef_A;
    break;
    case 'B':
      return redef_B;
    break;
    case 'C':
      return redef_C;
    break;
    case 'D':
      return redef_D;
    break;
    case 'E':
      return redef_E;
    break;
    case 'F':
      return redef_F;
    break;
    case 'G':
      return redef_G;
    break;
    case 'H':
      return redef_H;
    break;
    case 'I':
      return redef_I;
    break;
    case 'L':
      return redef_L;
    break;
    case 'M':
      return redef_M;
    break;
    case 'P':
      return redef_P;
    break;
    case 'V':
      return redef_V;
    break;
    case ':':
      return redef_colon;
    break;
    case ' ':
      return redef_blank;
    break;
    case '0':
      return redef_zero;
    break;
    case '1':
      return redef_one;
    break;
    case '2':
      return redef_two;
    break;
    case '3':
      return redef_three;
    break;
    case '4':
      return redef_four;
    break;
    case '5':
      return redef_five;
    break;
    case '6':
      return redef_six;
    break;
    case '7':
      return redef_seven;
    break;
    case '8':
      return redef_eight;
    break;
    case '9':
      return redef_nine;
    break;
    default:
      return redef_blank;
    break;
  }
}
