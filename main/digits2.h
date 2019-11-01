byte A[] = {
  B01111110,
  B10100000,
  B10100000,
  B10100000,
  B01111110,
  B00000000,
  B00000000,
  B00000000
};

byte B[] = {
  B11111110,
  B10010010,
  B10010010,
  B10010010,
  B01101100,
  B00000000,
  B00000000,
  B00000000
};


byte C[] = {
  B01111100,
  B10000010,
  B10000010,
  B10000010,
  B01000100,
  B00000000,
  B00000000,
  B00000000
};


byte D[] = {
  B11111110,
  B10000010,
  B10000010,
  B10000010,
  B01111100,
  B00000000,
  B00000000,
  B00000000
};

byte E[] = {
  B11111110,
  B10010010,
  B10010010,
  B10010010,
  B10000010,
  B00000000,
  B00000000,
  B00000000
};

byte F[] = {
  B11111110,
  B10010000,
  B10010000,
  B10010000,
  B10000000,
  B00000000,
  B00000000,
  B00000000
};

byte P[] = {
  B11111110,
  B10001000,
  B10001000,
  B10001000,
  B01110000,
  B00000000,
  B00000000,
  B00000000
};

byte M[] = {
  B11111110,
  B01000000,
  B00100000,
  B01000000,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};

byte one[] = {
  B00000000,
  B00000000,
  B11111110,
  B01000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

byte two[] = {
  B01000010,
  B10000010,
  B10000110,
  B10001010,
  B01110010,
  B00000000,
  B00000000,
  B00000000
};

byte three[] = {
  B10000010,
  B10010010,
  B10010010,
  B10010010,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};

byte four[] = {
  B11110000,
  B00010000,
  B00010000,
  B00010000,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};


byte five[] = {
  B10001100,
  B10010010,
  B10010010,
  B10010010,
  B11110010,
  B00000000,
  B00000000,
  B00000000
};

byte six[] = {
  B10011110,
  B10010010,
  B10010010,
  B10010010,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};

byte seven[] = {
  B10000000,
  B10000000,
  B10001110,
  B10010000,
  B11100000,
  B00000000,
  B00000000,
  B00000000
};

byte eight[] = {
  B01101100,
  B10010010,
  B10010010,
  B10010010,
  B01101100,
  B00000000,
  B00000000,
  B00000000
};
byte nine[] = {
  B11110010,
  B10010010,
  B10010010,
  B10010010,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};

byte zero[] = {
  B01111100,
  B10000010,
  B10000010,
  B10000010,
  B01111100,
  B00000000,
  B00000000,
  B00000000
};

byte blank[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

byte colon[] = {
  B00000000,
  B00000000,
  B01000100,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

void *getVerticalLetter(char character)
{
  switch(character)
  {
    case 'A':
      return A;
    break;
    case 'B':
      return B;
    break;
    case 'C':
      return C;
    break;
    case 'D':
      return D;
    break;
    case 'E':
      return E;
    break;
    case 'F':
      return F;
    break;
    case 'P':
      return P;
    break;
    case 'M':
      return M;
    break;
    case ':':
      return colon;
    break;
    case ' ':
      return blank;
    break;
    case '0':
      return zero;
    break;
    case '1':
      return one;
    break;
    case '2':
      return two;
    break;
    case '3':
      return three;
    break;
    case '4':
      return four;
    break;
    case '5':
      return five;
    break;
    case '6':
      return six;
    break;
    case '7':
      return seven;
    break;
    case '8':
      return eight;
    break;
    case '9':
      return nine;
    break;
  }
}
