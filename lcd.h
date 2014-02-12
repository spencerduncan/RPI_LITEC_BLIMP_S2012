
/*-----------------------------------------------------------------------------
 *  lcd.h - Printing to the LCD screen and getting input from the keypad
 *-----------------------------------------------------------------------------*/
#ifndef LCD_H__
#define LCD_H__

//#include <c8051_SDCC.h>
//#include <i2c.h>
#include "utilities.h"

unsigned int read_heading(void);		//read desired heading from LCD
unsigned int read_gain(void);			  //read gain value from LCD
char getKey(void);          //Get a key from the keypad
unsigned int read_gain_high(void);    //higher gain values for differential gain
unsigned int read_gain_thrust_high();
unsigned int read_gain_thrust();


unsigned int read_heading()
{	
  /* 
   * ===  FUNCTION  ======================================================================
   *         Name:  read_heading
   *  Description:  Allows the user to enter a new target heading
   * =====================================================================================
   */
  unsigned int output;
  char keypad;
  unsigned char i;
  lcd_clear();
  lcd_print("  Pick a direction. ");
  lcd_print("   keypad = NW N NE ");
  lcd_print("            W  X  E ");
  lcd_print("X=heading   SW S SE");
  keypad = getKey();
  if ( keypad == '1' )		//press 1
    return 3150;
  if ( keypad == '2' )		//press 2
    return    0;
  if ( keypad == '3' )		//press 3
    return  450;
  if ( keypad == '4' )		//press 4
    return 2700;
  if ( keypad == '6' )		//press 6
    return  900;
  if ( keypad == '7' )		//press 7
    return 2250;
  if ( keypad == '8' )		//press 8
    return 1800;
  if ( keypad == '9' )		//press 9
    return 1350;
  if ( keypad == '5' )    //press 5 
  {
    lcd_clear();
    output = 0;
    lcd_print("Enter desired heading:");
    for (i=0; i < 3; i++)
    {
      keypad = getKey();
      printf("The key entered was %d\n\r",keypad-48);
      output *= 10;
      output += ( keypad - 0x30 );
      lcd_clear();
      lcd_print("Enter desired heading:\n  %d", output);
    }
    output *= 10;
   printf("The heading is set to %d\r\n", output);
   while (output >= 3600)
     output -= 3600;
   return output;
  }
  else return read_heading();
}


unsigned int read_gain_high()
{
  /* 
   * ===  FUNCTION  ======================================================================
   *         Name:  read_gain_high
   *  Description:  Asks the user what they want the differential steering gain value to be
   * =====================================================================================
   */
  char keypad;
  char keycount = 0;
  unsigned int input = 0;
  lcd_clear();
  lcd_print("Set DiffGain rudder:\n");
  /*lcd_print("1:1  2:2 3:3");
  lcd_print("4:4 5:5 6:6");
  lcd_print("7:7 8:8 9:0");*/
  while (keycount < 3)
  {
    keypad = getKey();
    input *= 10;
    input += (keypad - 0x30);
    ++keycount;
    lcd_clear();
    lcd_print("Set DiffGain rudder:\n%d", input);
    
  }
  printf("\n\rInput is: %d", input);
  return input;

  /*char keypad;
  lcd_clear();
  lcd_print("Set DiffGain rudder:");
  lcd_print("1:1.0  2:5.0 3:10");
  lcd_print("4:0  5:0.40 6:0.50");
  //lcd_print("7:0.38 8:0.36 9:0.34");
  keypad = getKey();
  printf("your key was: %c\n\r", keypad);
  if (keypad == '1')
    return 1;
  if (keypad == '2')
    return 5;
  if (keypad == '3')
    return 10;
  if (keypad == '4')
    return 0;
  if (keypad == '5')
    return 0.40;
  if (keypad == '6')
    return 0.50;
  if (keypad == '7')
    return 0.38;
  if (keypad == '8')
    return 0.36;
  if (keypad == '9')
    return 0.34;
  else
    return 1;*/
}

unsigned int read_gain()
{
  /* 
   * ===  FUNCTION  ======================================================================
   *         Name:  read_gain
   *  Description:  Asks the user what they want the proportional steering gain value to be
   * =====================================================================================
   */
  char keypad;
  char keycount = 0;
  unsigned int input = 0;
  lcd_clear();
  lcd_print("Set PropGain rudder:");
  /*lcd_print("1:1  2:2 3:3");
  lcd_print("4:4 5:5 6:6");
  lcd_print("7:7 8:8 9:0");*/
  while (keycount < 3)
  {
    keypad = getKey();
    input *= 10;
    input += (keypad - 0x30);
    ++keycount;
    lcd_clear();
    lcd_print("Set PropGain rudder:\n%d", input);
  }
  printf("\n\rInput is: %d", input);
  return input;
  
  /*if (keypad == '1')
    return 1;
  if (keypad == '2')
    return 2;
  if (keypad == '3')
    return 3;
  if (keypad == '4')
    return 4;
  if (keypad == '5')
    return 5;
  if (keypad == '6')
    return 6;
  if (keypad == '7')
    return 7;
  if (keypad == '8')
    return 8;
  if (keypad == '9')
    return 0;
  else
    return 0.44;*/
}
unsigned int read_gain_thrust()
{
  /* 
   * ===  FUNCTION  ======================================================================
   *         Name:  read_gain_thrust
   *  Description:  Asks the user what they want the proportional thrust gain value to be
   * =====================================================================================
   */
  char keypad;
  char keycount = 0;
  unsigned int input = 0;
  lcd_clear();
  lcd_print("Set PropGain Thrust:");
  /*lcd_print("1:1  2:2 3:3");
  lcd_print("4:4 5:5 6:6");
  lcd_print("7:7 8:8 9:0");*/
  while (keycount < 3)
  {
    keypad = getKey();
    input *= 10;
    input += (keypad - 0x30);
    ++keycount;
    lcd_clear();
    lcd_print("Set PropGain thrust:\n%d", input);
  }
  printf("\n\rInput is: %d", input);
  return input;
  /*char keypad;
  lcd_clear();
  lcd_print("Set PropGain Thrust:");
  lcd_print("1:0.5  2:0.48 3:0.46");
  lcd_print("4:0.44 5:0.42 6:0.40");
  lcd_print("7:0.38 8:0.36 9:0.34");
  keypad = getKey();
  printf("your key was: %d\n\r", keypad);
  if (keypad == '1')
    return 0.5;
  if (keypad == '2')
    return 0.48;
  if (keypad == '3')
    return 0.46;
  if (keypad == '4')
    return 0.44;
  if (keypad == '5')
    return 0.42;
  if (keypad == '6')
    return 0.40;
  if (keypad == '7')
    return 0.38;
  if (keypad == '8')
    return 0.36;
  if (keypad == '9')
    return 0.34;
  else
    return 0.44;*/

}

unsigned int read_gain_thrust_high()
{
  /* 
   * ===  FUNCTION  ======================================================================
   *         Name:  read_gain_thrust_high
   *  Description:  Asks the user what they want the differential thrust gain value to be
   * =====================================================================================
   */
  char keypad;
  char keycount = 0;
  unsigned int input = 0;
  lcd_clear();
  lcd_print("Set DiffGain Thrust:");
  /*lcd_print("1:1  2:2 3:3");
  lcd_print("4:4 5:5 6:6");
  lcd_print("7:7 8:8 9:0");*/
  while (keycount < 3)
  {
    keypad = getKey();
    input *= 10;
    input += (keypad - 0x30);
    ++keycount;
    lcd_clear();
    lcd_print("Set DiffGain thrust:\n%d", input);
  }
  printf("\n\rInput is: %d", input);
  return input;

  /*char keypad;
  lcd_clear();
  lcd_print("Set DiffGain Thrust:");
  lcd_print("1:1.0  2:5.0 3:10");
  lcd_print("4:0  5:0.40 6:0.50");
  //lcd_print("7:0.38 8:0.36 9:0.34");
  keypad = getKey();
  printf("your key was: %d\n\r", keypad);
  if (keypad == '1')
    return 1;
  if (keypad == '2')
    return 5;
  if (keypad == '3')
    return 10;
  if (keypad == '4')
    return 0;
  if (keypad == '5')
    return 0.40;
  if (keypad == '6')
    return 0.50;
  if (keypad == '7')
    return 0.38;
  if (keypad == '8')
    return 0.36;
  if (keypad == '9')
    return 0.34;
  else
    return 1;*/

}

  

char getKey(void)
{
  /* 
   * ===  FUNCTION  ======================================================================
   *         Name:  getKey
   *  Description:  Gets a single keyread from the Keypad as an ASCII value.
   * =====================================================================================
   */
  char lKeypad = read_keypad();
  char out;
  pause();
  while (1)                            /* Will be broken with a return */
  {
    if ( lKeypad != -1 )
    {
      out = lKeypad;
      while ( lKeypad == out )         /* Let them hold the button down */
      {
        lKeypad = read_keypad();
        pause();
      }
      return out;
    }
    else
    {
      lKeypad = read_keypad();
      pause();
    }
  }
}

#endif
