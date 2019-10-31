byte A[] = {
  B00000000,
  B00110000, // 0x60
  B01001000, // 0x90
  B01001000, // 0x90
  B01111000, // 0xF0
  B01001000, // 0x90
  B01001000, // 0x90
  B00000000
  };

 byte J[] = {
  B00000000,
  B00010000,
  B00010000,
  B00010000,
  B00010000,
  B10010000,
  B01100000,
  B00000000
  };

 byte ON[] = {
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0xFF
 };

 byte OFF[] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
 };

 byte one[] = {
  B01000000,
  B11000000,
  B01000000,
  B01000000,
  B01000000,
  B01000000,
  B01000000,
  B00000000
 };

 byte two[] = {
  B01100000,
  B10010000,
  B00010000,
  B00100000,
  B01000000,
  B10000000,
  B11110000,
  B00000000
 };

byte three[] = {
  B01100000,
  B10010000,
  B00010000,
  B01100000,
  B00010000,
  B10010000,
  B01100000,
  B00000000
 };

 byte four[] = {
  B10010000,
  B10010000,
  B10010000,
  B11110000,
  B00010000,
  B00010000,
  B00010000,
  B00000000
 };

  byte five[] = {
  B11110000,
  B10000000,
  B10000000,
  B11110000,
  B00010000,
  B10010000,
  B01100000,
  B00000000
 };

  byte six[] = {
  B01100000,
  B10010000,
  B10000000,
  B11100000,
  B10010000,
  B10010000,
  B01100000,
  B00000000
 };

 byte seven[] = {
  B11110000,
  B00010000,
  B00010000,
  B00010000,
  B00100000,
  B00100000,
  B00100000,
  B00000000
 };

  byte eight[] = {
  B01100000,
  B10010000,
  B10010000,
  B01100000,
  B10010000,
  B10010000,
  B01100000,
  B00000000
 };

 byte nine[] = {
  B01100000,
  B10010000,
  B10010000,
  B01110000,
  B00010000,
  B10010000,
  B01100000,
  B00000000
 };

 byte zero[] = {
  B01100000,
  B10010000,
  B10010000,
  B10010000,
  B10010000,
  B10010000,
  B01100000,
  B00000000
 };

byte colon[] = {
  B00000000,
  B11000000,
  B11000000,
  B00000000,
  B11000000,
  B11000000,
  B00000000,
  B00000000
 };

 byte numbers[] = {zero,one,two,three,four,five,six,seven,eight,nine}; 

 byte *getNumbers(byte input) 
 {
  switch(input)
  {
    case 0:
    return zero;
    break;
    case 1:
    return one;
    break;
    case 2:
    return two;
    break;
    case 3:
    return three;
    break;
    case 4:
    return four;
    break;
    case 5:
    return five;
    break;
    case 6:
    return six;
    break;
    case 7:
    return seven;
    break;
    case 8:
    return eight;
    break;
    case 9:
    return nine;
    break;
  }
 }
