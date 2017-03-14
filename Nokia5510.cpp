#include "Nokia5510.h"


Nokia5510::Nokia5510(int SCE, int RESET, int LIGHT, int DC, int SDIN, int SCLK){
  PIN_SCE = SCE;
  PIN_RESET = RESET;
  PIN_LIGHT = LIGHT;
  PIN_DC = DC;
  PIN_SDIN = SDIN;
  PIN_SCLK=SCLK;
  //Configure control pins
  pinMode(PIN_SCE, OUTPUT);
  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_DC, OUTPUT);
  pinMode(PIN_SDIN, OUTPUT);
  pinMode(PIN_SCLK, OUTPUT);
  pinMode(PIN_LIGHT,OUTPUT);
  digitalWrite(PIN_LIGHT,LOW);
  digitalWrite(PIN_SCE,LOW);
  digitalWrite(PIN_RESET, LOW);
  digitalWrite(PIN_RESET, HIGH);
  WriteData(LCD_COMMAND, 0x21); //Tell LCD that extended commands follow
  WriteData(LCD_COMMAND, 0xB0); //Set LCD Vop (Contrast): Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark
  WriteData(LCD_COMMAND, 0x04); //Set Temp coefficent
  WriteData(LCD_COMMAND, 0x14); //LCD bias mode 1:48: Try 0x13 or 0x14
  WriteData(LCD_COMMAND, 0x20); //We must send 0x20 before modifying the display control mode
  WriteData(LCD_COMMAND, 0x0C); //Set display control, normal mode. 0x0D for inverse
}


void Nokia5510::WriteData(byte data_or_command, byte data) {
  digitalWrite(PIN_DC, data_or_command); 
  shiftOut(PIN_SDIN, PIN_SCLK, MSBFIRST, data); // Send data to LCD
}


void Nokia5510::gotoxy(int x, int y) {
  WriteData(0, 0x80 | x);  // Column  x - range: 0 to 84
  WriteData(0, 0x40 | y);  // Row     y - range: 0 to 5
}

void Nokia5510::DrawBitmap(char my_array[]){
  for (int index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
    WriteData(LCD_DATA, my_array[index]);
}


void Nokia5510::WriteCharacter(char character) {
  WriteData(LCD_DATA, 0x00); //Blank vertical line padding
  for (int index = 0 ; index < 5 ; index++)
    WriteData(LCD_DATA, ASCII[character - 0x20][index]);
  WriteData(LCD_DATA, 0x00); //Blank vertical line padding
}


void Nokia5510::WriteString(char *characters) {
  while (*characters)
    WriteCharacter(*characters++);
}

void Nokia5510::DisplayClear(void) {
  for (int index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
    WriteData(LCD_DATA, 0x00);
  gotoxy(0, 0); //After we clear the display, return to the home position
}

