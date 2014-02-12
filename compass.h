/*-----------------------------------------------------------------------------
 * compass.h - Compass & Steering code 
 *-----------------------------------------------------------------------------*/
#ifndef COMPASS_H__
#define COMPASS_H__

#define PW_CENTER 2750 //Center PW
#define PW_MIN 2000 //Min PW
#define PW_MAX 3500 //max PW

// None of the LITEC headers have
// multiple include protection, so
// those are all included in Lab5.c
//#include <c8051_SDCC.h>
//#include <i2c.h>

                                                /* Current error is calculated when needed */
  signed   int compass_old_error = 0;               /* Old header used for derivative control */
  unsigned int heading;                         /* The compass heading */

__xdata	float compass_kp;                       /* Steering proportional gain constant */
__xdata	float compass_kd;                       /* Steering derivative gain contant */
__xdata	unsigned int desired_heading;           /* Steering target heading */

signed int compass_error();                     /* Function to calculate current error */
unsigned int read_compass(void);                /* Function to read the compass */
void Steering_Servo();                          /* Set the steering servo */
void steering_neutral(void);                    /* Sets the steering to neutral ( off ) */

signed int compass_error()
{
  /* 
   * ===  FUNCTION  ======================================================================
   *         Name:  compass_error
   *  Description:  Calculates and returns the error based on the set desired heading and
   *  the current heading. Corrects for wrap around error. 
   * =====================================================================================
   */
  signed int error = desired_heading - heading;
  if (error <=-1800)
  {
    error=error+3600;
  }
  else if (error >=1800)												
  {	
    error = error - 3600;
  }
  return error;			
}

unsigned int read_compass(void)
{
  /* 
   * ===  FUNCTION  ======================================================================
   *         Name:  read_compass
   *  Description:  Polls the compass and returns the heading in tenths of a degree
   * =====================================================================================
   */
  unsigned char Data[2]; // Data is an array with a length of 2
  i2c_read_data(0xC0, 2, Data, 2); // read two byte, starting at reg 2
  return (((unsigned int)Data[0] << 8) | Data[1]); //combine the two values
  //heading has units of 1/10 of a degree
}

void Steering_Servo()
{	
  /* 
   * ===  FUNCTION  ======================================================================
   *         Name:  Steering_Servo
   *  Description:  Applies the PD control algorithm to compute a pulse width, and sets
   *  CEX0.
   * =====================================================================================
   */
  signed int error = compass_error();           /* Get error */
  unsigned long PW = 0;
  if ( error > -20 && error < 20)		//within 2 degrees
    PW=PW_CENTER;			//keep the car straight

  else
    PW= PW_CENTER + compass_kp*error - compass_kd*( compass_old_error - error ) ;
  
  //printf("the error is %d", error/10);			//in degree

  // Boundary control
  if (PW < PW_MIN)
    PW = PW_MIN;

  if (PW > PW_MAX)
    PW = PW_MAX;
    
//	printf("PW: %u\n", PW);
  PCA0CPL0 = 0xFFFF - PW;
  PCA0CPH0 = (0xFFFF - PW) >> 8;

  compass_old_error = error;                    /* Set the old error for the next loop */

}

void steering_neutral(void)
{
  /* 
   * ===  FUNCTION  ======================================================================
   *         Name:  steering_neutral
   *  Description:  Turns of the steering fan/servo
   * =====================================================================================
   */

  PCA0CPL0 = 0xFFFF - PW_CENTER;
  PCA0CPH0 = (0xFFFF - PW_CENTER) >> 8;

}

#endif
