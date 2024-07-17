// Define Connections to 74HC595
const int dataPin_CRGB = D5;
const int latchPin_CRGB = D6;
const int clockPin_CRGB = D7;

bool flag[5];

enum colors
{
  red = 1,
  blue = 2,
  green = 3
};

enum sections
{
  none = 0,
  A = 1,
  B = 2,
  C = 3,
  D = 4,
  E = 5
};

const int rowSelect[] = {
    B11111111, // 0
    B11000000, // A
    B00110000, // B
    B11110000, // C
    B00001111, // D
    B11111111, // E
};

const int colSelect[] = {
    B11111111, // 0
    B11001111, // A
    B11001111, // B
    B00111111, // C
    B00001111, // D
    B11110000, // E
};
// const int rowSelect_A = B11000000;
// const int rowSelect_B = B00110000;
// const int rowSelect_C = B11110000;
// const int rowSelect_D = B00001111;
// const int rowSelect_E = B11111111;

// const int colSelect_A = B11001111;
// const int colSelect_B = B11001111;
// const int colSelect_C = B00111111;
// const int colSelect_D = B00001111;
// const int colSelect_E = B11110000;

void cleardata()
{
  digitalWrite(latchPin_CRGB, LOW);
  shiftOut(dataPin_CRGB, clockPin_CRGB, LSBFIRST, 255); // Green
  shiftOut(dataPin_CRGB, clockPin_CRGB, LSBFIRST, 255); // Blue
  shiftOut(dataPin_CRGB, clockPin_CRGB, LSBFIRST, 255); // Red
  shiftOut(dataPin_CRGB, clockPin_CRGB, LSBFIRST, 255); // Row
  digitalWrite(latchPin_CRGB, HIGH);
}

void light_section(sections section, colors color)
{
  int selectrow = rowSelect[section];
  int selectcol = colSelect[section];

  if (color == colors::red)
  {
    cleardata();
    digitalWrite(latchPin_CRGB, LOW);
    shiftOut(dataPin_CRGB, clockPin_CRGB, LSBFIRST, 255);       // Green
    shiftOut(dataPin_CRGB, clockPin_CRGB, LSBFIRST, 255);       // Blue
    shiftOut(dataPin_CRGB, clockPin_CRGB, LSBFIRST, selectcol); // Red
    shiftOut(dataPin_CRGB, clockPin_CRGB, LSBFIRST, selectrow); // Row
    digitalWrite(latchPin_CRGB, HIGH);
  }

  else if (color == colors::blue)
  {
    cleardata();
    digitalWrite(latchPin_CRGB, LOW);
    shiftOut(dataPin_CRGB, clockPin_CRGB, LSBFIRST, 255);       // Green
    shiftOut(dataPin_CRGB, clockPin_CRGB, LSBFIRST, selectcol); // Blue
    shiftOut(dataPin_CRGB, clockPin_CRGB, LSBFIRST, 255);       // Red
    shiftOut(dataPin_CRGB, clockPin_CRGB, LSBFIRST, selectrow); // Row
    digitalWrite(latchPin_CRGB, HIGH);
  }
  else if (color == colors::green)
  {
    cleardata();
    digitalWrite(latchPin_CRGB, LOW);
    shiftOut(dataPin_CRGB, clockPin_CRGB, LSBFIRST, selectcol); // Green
    shiftOut(dataPin_CRGB, clockPin_CRGB, LSBFIRST, 255);       // Blue
    shiftOut(dataPin_CRGB, clockPin_CRGB, LSBFIRST, 255);       // Red
    shiftOut(dataPin_CRGB, clockPin_CRGB, LSBFIRST, selectrow); // Row
    digitalWrite(latchPin_CRGB, HIGH);
  }
}

void displayTime(int hour, int minutes)
{
  Serial.print(hour);
  Serial.print(minutes);
  Serial.println();
  // Hour
  switch (hour)
  {
  case 0:
    /* code */
    light_section(sections::none, colors::red);
    flag[0] = false;
    flag[1] = false;
    flag[2] = false;
    flag[3] = false;
    flag[4] = false;
    break;

  case 1:
    /* code */
    light_section(sections::A, {!flag[0] ? colors::red : colors::green});
    flag[0] = true; // First  1
    flag[1] = false;
    flag[2] = false;
    flag[3] = false;
    flag[4] = false;
    break;

  case 2:
    /* code */
    light_section(sections::A, {!flag[0] ? colors::red : colors::green});
    light_section(sections::B, {!flag[1] ? colors::red : colors::green});
    flag[0] = true; // First  1
    flag[1] = true; // Second 1
    flag[2] = false;
    flag[3] = false;
    flag[4] = false;
    break;

  case 3:
    /* code */
    light_section(sections::B, {!flag[1] ? colors::red : colors::green});
    light_section(sections::C, {!flag[2] ? colors::red : colors::green});
    flag[0] = false;
    flag[1] = true; // Second 1
    flag[2] = true; // 2
    flag[3] = false;
    flag[4] = false;
    break;

  case 4:
    /* code */
    light_section(sections::B, {!flag[1] ? colors::red : colors::green});
    light_section(sections::D, {!flag[3] ? colors::red : colors::green});
    flag[0] = false;
    flag[1] = true; // Second 1
    flag[2] = false;
    flag[3] = true; // 3
    flag[4] = false;
    break;

  case 5:
    /* code */
    light_section(sections::C, {!flag[2] ? colors::red : colors::green});
    light_section(sections::D, {!flag[3] ? colors::red : colors::green});
    flag[0] = false;
    flag[1] = false;
    flag[2] = true; // 2
    flag[3] = true; // 3
    flag[4] = false;
    break;

  case 6:
    /* code */
    light_section(sections::B, {!flag[1] ? colors::red : colors::green});
    light_section(sections::C, {!flag[2] ? colors::red : colors::green});
    light_section(sections::D, {!flag[3] ? colors::red : colors::green});
    flag[0] = false;
    flag[1] = true; // Second 1
    flag[2] = true; // 2
    flag[3] = true; // 3
    flag[4] = false;
    break;

  case 7:
    /* code */
    light_section(sections::A, {!flag[0] ? colors::red : colors::green});
    light_section(sections::B, {!flag[1] ? colors::red : colors::green});
    light_section(sections::E, {!flag[4] ? colors::red : colors::green});
    flag[0] = true; // First  1
    flag[1] = true; // Second 1
    flag[2] = false;
    flag[3] = false;
    flag[4] = true; // 5
    break;

  case 8:
    /* code */
    light_section(sections::D, {!flag[3] ? colors::red : colors::green});
    light_section(sections::E, {!flag[4] ? colors::red : colors::green});
    flag[0] = false;
    flag[1] = false;
    flag[2] = false;
    flag[3] = true; // 3
    flag[4] = true; // 5
    break;

  case 9:
    /* code */
    light_section(sections::A, {!flag[0] ? colors::red : colors::green});
    light_section(sections::B, {!flag[1] ? colors::red : colors::green});
    light_section(sections::C, {!flag[2] ? colors::red : colors::green});
    light_section(sections::E, {!flag[4] ? colors::red : colors::green});
    flag[0] = true; // First  1
    flag[1] = true; // Second 1
    flag[2] = true; // 2
    flag[3] = false;
    flag[4] = true; // 5
    break;

  case 10:
    /* code */
    light_section(sections::A, {!flag[0] ? colors::red : colors::green});
    light_section(sections::B, {!flag[1] ? colors::red : colors::green});
    light_section(sections::D, {!flag[3] ? colors::red : colors::green});
    light_section(sections::E, {!flag[4] ? colors::red : colors::green});
    flag[0] = true; // First  1
    flag[1] = true; // Second 1
    flag[2] = false;
    flag[3] = true; // 3
    flag[4] = true; // 5
    break;

  case 11:
    /* code */
    light_section(sections::B, {!flag[1] ? colors::red : colors::green});
    light_section(sections::C, {!flag[2] ? colors::red : colors::green});
    light_section(sections::D, {!flag[3] ? colors::red : colors::green});
    light_section(sections::E, {!flag[4] ? colors::red : colors::green});
    flag[0] = false;
    flag[1] = true; // Second 1
    flag[2] = true; // 2
    flag[3] = true; // 3
    flag[4] = true; // 5
    break;

  case 12:
    /* code */
    light_section(sections::A, {!flag[0] ? colors::red : colors::green});
    light_section(sections::B, {!flag[1] ? colors::red : colors::green});
    light_section(sections::C, {!flag[2] ? colors::red : colors::green});
    light_section(sections::D, {!flag[3] ? colors::red : colors::green});
    light_section(sections::E, {!flag[4] ? colors::red : colors::green});
    flag[0] = true; // First  1
    flag[1] = true; // Second 1
    flag[2] = true; // 2
    flag[3] = true; // 3
    flag[4] = true; // 5
    break;

  default:
    /* code */
    flag[0] = false;
    flag[1] = false;
    flag[2] = false;
    flag[3] = false;
    flag[4] = false;
    break;
  }

  // Serial.print(flag[0]);
  // Serial.print(flag[1]);
  // Serial.print(flag[2]);
  // Serial.print(flag[3]);
  // Serial.print(flag[4]);
  // Serial.println("\n");

  // Switch the minutes section

  switch (minutes)
  {
  case 0:
    /* code */
    light_section(sections::none, colors::blue);
    flag[0] = false;
    flag[1] = false;
    flag[2] = false;
    flag[3] = false;
    flag[4] = false;
    break;

  case 1:
    /* code */
    light_section(sections::A, {flag[0] ? colors::green : colors::blue});
    flag[0] = true; // First  1
    flag[1] = false;
    flag[2] = false;
    flag[3] = false;
    flag[4] = false;
    break;

  case 2:
    /* code */
    light_section(sections::A, {flag[0] ? colors::green : colors::blue});
    light_section(sections::B, {flag[1] ? colors::green : colors::blue});
    flag[0] = true; // First  1
    flag[1] = true; // Second 1
    flag[2] = false;
    flag[3] = false;
    flag[4] = false;
    break;

  case 3:
    /* code */
    light_section(sections::B, {flag[1] ? colors::green : colors::blue});
    light_section(sections::C, {flag[2] ? colors::green : colors::blue});
    flag[0] = false;
    flag[1] = true; // Second 1
    flag[2] = true; // 2
    flag[3] = false;
    flag[4] = false;
    break;

  case 4:
    /* code */
    light_section(sections::B, {flag[1] ? colors::green : colors::blue});
    light_section(sections::D, {flag[3] ? colors::green : colors::blue});
    flag[0] = false;
    flag[1] = true; // Second 1
    flag[2] = false;
    flag[3] = true; // 3
    flag[4] = false;
    break;

  case 5:
    /* code */
    light_section(sections::C, {flag[2] ? colors::green : colors::blue});
    light_section(sections::D, {flag[3] ? colors::green : colors::blue});
    flag[0] = false;
    flag[1] = false;
    flag[2] = true; // 2
    flag[3] = true; // 3
    flag[4] = false;
    break;

  case 6:
    /* code */
    light_section(sections::B, {flag[1] ? colors::green : colors::blue});
    light_section(sections::C, {flag[2] ? colors::green : colors::blue});
    light_section(sections::D, {flag[3] ? colors::green : colors::blue});
    flag[0] = false;
    flag[1] = true; // Second 1
    flag[2] = true; // 2
    flag[3] = true; // 3
    flag[4] = false;
    break;

  case 7:
    /* code */
    light_section(sections::A, {flag[0] ? colors::green : colors::blue});
    light_section(sections::B, {flag[1] ? colors::green : colors::blue});
    light_section(sections::E, {flag[4] ? colors::green : colors::blue});
    flag[0] = true; // First  1
    flag[1] = true; // Second 1
    flag[2] = false;
    flag[3] = false;
    flag[4] = true; // 5
    break;

  case 8:
    /* code */
    light_section(sections::D, {flag[3] ? colors::green : colors::blue});
    light_section(sections::E, {flag[4] ? colors::green : colors::blue});
    flag[0] = false;
    flag[1] = false;
    flag[2] = false;
    flag[3] = true; // 3
    flag[4] = true; // 5
    break;

  case 9:
    /* code */
    light_section(sections::A, {flag[0] ? colors::green : colors::blue});
    light_section(sections::B, {flag[1] ? colors::green : colors::blue});
    light_section(sections::C, {flag[2] ? colors::green : colors::blue});
    light_section(sections::E, {flag[4] ? colors::green : colors::blue});
    flag[0] = true; // First  1
    flag[1] = true; // Second 1
    flag[2] = true; // 2
    flag[3] = false;
    flag[4] = true; // 5
    break;

  case 10:
    /* code */
    light_section(sections::A, {flag[0] ? colors::green : colors::blue});
    light_section(sections::B, {flag[1] ? colors::green : colors::blue});
    light_section(sections::D, {flag[3] ? colors::green : colors::blue});
    light_section(sections::E, {flag[4] ? colors::green : colors::blue});
    flag[0] = true; // First  1
    flag[1] = true; // Second 1
    flag[2] = false;
    flag[3] = true; // 3
    flag[4] = true; // 5
    break;

  case 11:
    /* code */
    light_section(sections::B, {flag[1] ? colors::green : colors::blue});
    light_section(sections::C, {flag[2] ? colors::green : colors::blue});
    light_section(sections::D, {flag[3] ? colors::green : colors::blue});
    light_section(sections::E, {flag[4] ? colors::green : colors::blue});
    flag[0] = false;
    flag[1] = true; // Second 1
    flag[2] = true; // 2
    flag[3] = true; // 3
    flag[4] = true; // 5
    break;

  case 12:
    /* code */
    light_section(sections::A, {flag[0] ? colors::green : colors::blue});
    light_section(sections::B, {flag[1] ? colors::green : colors::blue});
    light_section(sections::C, {flag[2] ? colors::green : colors::blue});
    light_section(sections::D, {flag[3] ? colors::green : colors::blue});
    light_section(sections::E, {flag[4] ? colors::green : colors::blue});
    flag[0] = true; // First  1
    flag[1] = true; // Second 1
    flag[2] = true; // 2
    flag[3] = true; // 3
    flag[4] = true; // 5
    break;

  default:
    /* code */
    flag[0] = false;
    flag[1] = false;
    flag[2] = false;
    flag[3] = false;
    flag[4] = false;
    break;
  }
}
