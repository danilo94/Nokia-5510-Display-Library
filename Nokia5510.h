#include <Arduino.h>
#include "ascii.h"
#define LCD_COMMAND 0
#define LCD_DATA  1
#define LCD_X     84
#define LCD_Y     48
class Nokia5510 {
    private:
	int PIN_SCE;
	int PIN_RESET;
	int PIN_LIGHT;
	int PIN_DC;
	int PIN_SDIN;
	int PIN_SCLK;
	void displayWrite(byte data_or_command, byte data);
	void WriteData (byte data_or_command, byte data);
	void WriteCharacter(char character);
  public:
	  Nokia5510(int SCE, int RESET, int LIGHT, int DC, int SDIN, int SCLK);
	  void DrawBitmap(char my_array[]);
	  void DrawString(char );
	  void DjMode();
	  void DisplayClear(void);
	  void WriteString (char *characters);
	  void gotoxy(int x,int y);





};
