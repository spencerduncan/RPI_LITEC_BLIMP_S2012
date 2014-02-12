/*-----------------------------------------------------------------------------
 * battery.h - contains code relating to battery management 
 *-----------------------------------------------------------------------------*/
#ifndef BATTERY_H__
#define BATTERY_H__

//#include <c8051_SDCC.h>

unsigned char get_battery_voltage(void)
{
  AMX1SL=4;                         //read analog input from P1.4
  ADC1CN &=~0x20;			              //clear the completed flag
  ADC1CN |=0x10;			              //Initialize A/D conversion
  while((ADC1CN & 0x20) ==0x00);		//wait for the conversion to complete
  return ( ADC1 * 100 )/255;        //Convert to a percentage

}

#endif
