byte def_A[] = {
  B01111110,
  B10100000,
  B10100000,
  B10100000,
  B01111110,
  B00000000,
  B00000000,
  B00000000
};

byte def_B[] = {
  B11111110,
  B10010010,
  B10010010,
  B10010010,
  B01101100,
  B00000000,
  B00000000,
  B00000000
};


byte def_C[] = {
  B01111100,
  B10000010,
  B10000010,
  B10000010,
  B01000100,
  B00000000,
  B00000000,
  B00000000
};


byte def_D[] = {
  B11111110,
  B10000010,
  B10000010,
  B10000010,
  B01111100,
  B00000000,
  B00000000,
  B00000000
};

byte def_E[] = {
  B11111110,
  B10010010,
  B10010010,
  B10010010,
  B10000010,
  B00000000,
  B00000000,
  B00000000
};

byte def_F[] = {
  B11111110,
  B10010000,
  B10010000,
  B10010000,
  B10000000,
  B00000000,
  B00000000,
  B00000000
};

byte def_G[] = {
  B01111100,
  B10000010,
  B10000010,
  B10010010,
  B01011100,
  B00000000,
  B00000000,
  B00000000
};

byte def_H[] = {
  B11111110,
  B00010000,
  B00010000,
  B00010000,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};

byte def_I[] = {
  B00000000,
  B10000010,
  B11111110,
  B10000010,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

byte def_L[] = {
  B11111110,
  B00000010,
  B00000010,
  B00000010,
  B00000010,
  B00000000,
  B00000000,
  B00000000
};

byte def_V[] = {
  B11111000,
  B00000100,
  B00000010,
  B00000100,
  B11111000,
  B00000000,
  B00000000,
  B00000000
};


byte def_P[] = {
  B11111110,
  B10001000,
  B10001000,
  B10001000,
  B01110000,
  B00000000,
  B00000000,
  B00000000
};

byte def_M[] = {
  B11111110,
  B01000000,
  B00100000,
  B01000000,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};

byte def_one[] = {
  B00000000,
  B01000000,
  B11111110,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

byte def_two[] = {
  B01000010,
  B10000010,
  B10000110,
  B10001010,
  B01110010,
  B00000000,
  B00000000,
  B00000000
};

byte def_three[] = {
  B10000010,
  B10010010,
  B10010010,
  B10010010,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};

byte def_four[] = {
  B11110000,
  B00010000,
  B00010000,
  B00010000,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};


byte def_five[] = {
  B11110000,
  B10010010,
  B10010010,
  B10010010,
  B10001110,
  B00000000,
  B00000000,
  B00000000
};

byte def_six[] = {
  B11111110,
  B10010010,
  B10010010,
  B10010010,
  B10011110,
  B00000000,
  B00000000,
  B00000000
};

byte def_seven[] = {
  B10000000,
  B10000000,
  B10001110,
  B10010000,
  B11100000,
  B00000000,
  B00000000,
  B00000000
};

byte def_eight[] = {
  B11111110,
  B10010010,
  B10010010,
  B10010010,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};
byte def_nine[] = {
  B11110010,
  B10010010,
  B10010010,
  B10010010,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};

byte def_zero[] = {
  B11111110,
  B10000010,
  B10000010,
  B10000010,
  B11111110,
  B00000000,
  B00000000,
  B00000000
};

byte def_blank[] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};

byte def_colon[] = {
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
      return def_A;
    break;
    case 'B':
      return def_B;
    break;
    case 'C':
      return def_C;
    break;
    case 'D':
      return def_D;
    break;
    case 'E':
      return def_E;
    break;
    case 'F':
      return def_F;
    break;
    case 'G':
      return def_G;
    break;
    case 'H':
      return def_H;
    break;
    case 'I':
      return def_I;
    break;
    case 'L':
      return def_L;
    break;
    case 'M':
      return def_M;
    break;
    case 'P':
      return def_P;
    break;
    case 'V':
      return def_V;
    break;
    case ':':
      return def_colon;
    break;
    case ' ':
      return def_blank;
    break;
    case '0':
      return def_zero;
    break;
    case '1':
      return def_one;
    break;
    case '2':
      return def_two;
    break;
    case '3':
      return def_three;
    break;
    case '4':
      return def_four;
    break;
    case '5':
      return def_five;
    break;
    case '6':
      return def_six;
    break;
    case '7':
      return def_seven;
    break;
    case '8':
      return def_eight;
    break;
    case '9':
      return def_nine;
    break;
    default:
      return def_blank;
    break;
  }
}
