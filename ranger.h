
/*-----------------------------------------------------------------------------
 *  ranger.h - Read the ultrasonic ranger and control speed / altitude
 *-----------------------------------------------------------------------------*/
#ifndef RANGER_H__
#define RANGER_H__

#define MOTOR_PW_MIN 2002
#define MOTOR_PW_MAX 3458
#define PW_NEUT 2730
//#include <c8051_SDCC.h>
//#include <i2c.h>

  signed   int ranger_old_error;
  unsigned int range;

__xdata	float ranger_kp;
__xdata	float ranger_kd;
__xdata	unsigned int desired_range;

void ReadRanger(  );			//read ranger value
void Speed_Cont(  );				//control the motor speed	
void ranger_neutral(void);

void ReadRanger(  )
{
  /* 
   * ===  FUNCTION  ======================================================================
   *         Name:  ReadRanger
   *  Description:  Read the ranger
   * =====================================================================================
   */
//	unsigned char addr1 = 0xE0;                       // the address of the sensor, 0xE0 for the ranger
  unsigned char Data1[2];                             // Data is an array with a length of 2
  i2c_read_data(0xE0, 2, Data1, 2);	                  //Read 2 bytes of Data starting at register 2
  range = (((unsigned int)Data1[0] << 8) | Data1[1]);	//computes range using i2c Data
  Data1[0]=0x51;                                      //write 0x51 to reg 0 of ranger
  i2c_write_data(0xE0,0, Data1, 1);	                  //write 1 byte of data to reg 0 at addr1
//	printf("The range is: %u \r\n", range);		        //print range
}

void ranger_neutral()
{
  /* 
   * ===  FUNCTION  ======================================================================
   *         Name:  ranger_neutral
   *  Description:  Set the altitude/speed motors to neutral
   * =====================================================================================
   */

//	MOTOR_PW = PW_NEUT;			//motor
  PCA0CPL2 = 0xFFFF - PW_NEUT;
  PCA0CPH2 = (0xFFFF - PW_NEUT) >> 8;
  PCA0CPL3 = 0xFFFF - PW_NEUT;
  PCA0CPH3 = (0xFFFF - PW_NEUT) >> 8;

}

void Speed_Cont(  )
{
  /* 
   * ===  FUNCTION  ======================================================================
   *         Name:  Speed_Cont
   *  Description:  Set the altitude/speed motors based on the PD algorithm
   * =====================================================================================
   */
  unsigned long MOTOR_PW=0;
  unsigned int  error = (range - desired_range);

  if( error < 10 && error > -10 )
    MOTOR_PW=PW_NEUT;

  else
    MOTOR_PW=  PW_NEUT + ranger_kp * error -
               ranger_kd * ( ranger_old_error - error );

  if ( MOTOR_PW > MOTOR_PW_MAX)
    MOTOR_PW = MOTOR_PW_MAX;
  
  else if (MOTOR_PW < MOTOR_PW_MIN)
    MOTOR_PW = MOTOR_PW_MIN;
  
  PCA0CPL2 = 0xFFFF - MOTOR_PW;
  PCA0CPH2 = (0xFFFF - MOTOR_PW) >> 8;
  PCA0CPL3 = 0xFFFF - MOTOR_PW;
  PCA0CPH3 = (0xFFFF - MOTOR_PW) >> 8;

  ranger_old_error = error;
}	

#endif
