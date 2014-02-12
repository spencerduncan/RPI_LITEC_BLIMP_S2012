/*
 * =====================================================================================
 *
 *       Filename:  Lab5.c
 *
 *    Description:  LITEC code for Lab 5 
 *
 *        Version:  1.0
 *        Created:  4/24/2012 8:47:14 AM
 *       Compiler:  SDCC
 *
 *         Author:  Spencer Duncan et al
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <c8051_SDCC.h>
#include <i2c.h>
#include "init.h"
#include "interrupts.h"
#include "compass.h"
#include "battery.h"
#include "lcd.h"
#include "ranger.h"
#include "utilities.h"

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

// This is about as scary as it looks

//__sbit __at 0xB7 SS; // SS port pin
char SS = 0;

//-----------------------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------------------
void main(void)
{
  desired_range = 150;
  // initialize board
  Sys_Init();
  putchar(' '); //the quotes in this line may not format correctly
  PCA_Init();
  ADC_Init();
  Interrupt_Init();
  Port_Init();
  XBR0_Init();
  SMB_Init();
  putchar('\r');

  //print beginning message
  printf("En taro Adun, Executor!\r\n");

  // set the PCA output to a neutral setting
  steering_neutral();
  ranger_neutral();

  wait();                                       /* Let stuff warm up */

  // Get the PD constants and target heading from the keypad
  compass_kp              = read_gain()/10.;
  desired_heading         = read_heading();
  compass_kd              = read_gain_high();

  ranger_kp		           = read_gain_thrust()/10.;
  ranger_kd		           = read_gain_thrust_high();

  //Write the settings to the record
  printf ( "Compass KP = %d, Compass KD = %d, Desired Heading = %d, Ranger KP = %d, Ranger KD = %d, Desired Range = %d\r\n", 
      compass_kp,
      compass_kd, 
      desired_heading, 
      ranger_kp, 
      ranger_kd, 
      desired_range );

  printf ( "Time, heading, range\r\n ");

  PCA0CPL1 =   0xFFFF - 3200;
  PCA0CPH1 = ( 0xFFFF - 3200 ) >> 8 ;

  // Start at time 0.
  time = 0;

  while(1)                                      /* Infinite loop is go */
  {	
    if ( nCounts == 50 )
    {
      // Update the LCD loop
      lcd_clear();
      lcd_print( "Batt level: %d\n", get_battery_voltage() );
      lcd_print("Heading :%d\n", heading/10);
      lcd_print("Alt: %d", range );
      if (SS)
        lcd_print("PAUSED\n");
      else
        lcd_print("\n");
      lcd_print("# forHead, * forGain");
      
      }
    if ( read_keypad() != -1 )
    {
      // Check the keypad
      pause();
      if ( getKey() == '#' )
      {
        // If # was pressed, get a new heading
        steering_neutral();
        ranger_neutral();				
        desired_heading = read_heading();
        time = 0;
        printf ( "Compass KP = %d, Compass KD = %d, Desired Heading = %d, Ranger KP = %d, Ranger KD = %d, Desired Range = %d\r\n", 
            compass_kp,
            compass_kd, 
            desired_heading, 
            ranger_kp, 
            ranger_kd, 
            desired_range );

        printf ( "Time, heading, range\r\n ");
      }
      else if( getKey() == '*' )
      {
        // If * was pressed, get new gain contants
        steering_neutral();
        ranger_neutral();	
        compass_kp = read_gain()/10.;
        compass_kd = read_gain_high();
        ranger_kp  = read_gain_thrust()/10.;
        ranger_kd  = read_gain_thrust_high();
        time = 0;
        printf ( "Compass KP = %d, Compass KD = %d, Desired Heading = %d, Ranger KP = %d, Ranger KD = %d, Desired Range = %d\r\n", 
            compass_kp,
            compass_kd, 
            desired_heading, 
            ranger_kp, 
            ranger_kd, 
            desired_range );

        printf ( "Time, heading, range\r\n ");
      }
    }
    else
      pause();
    if(SS)			//while the SS is off
    {
      //printf("The slide switch is OFF \r\n");
      steering_neutral();
      ranger_neutral();
    }
    if(!SS)		//SS is On
    {
      //printf("The Slide switch is On \r\n");
      if ( new_heading )
        printf("%lu,%d,%d\r\n",
            time,
            compass_old_error, 
            ranger_old_error );
      if (new_heading)    //wait for 40ms
      {	
        heading=read_compass();
        //printf("The heading result is %d\r\n", heading);
        new_heading=0;
        Steering_Servo(  );
      }
      if (new_range)
      {
        ReadRanger(  );
        Speed_Cont(  );		//adjust motor speed
        new_range=0;		//reset ranger flag
      }
    }	
  }
}

