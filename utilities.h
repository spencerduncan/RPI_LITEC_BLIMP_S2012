
/*-----------------------------------------------------------------------------
 *  utilities.h - misc functions
 *-----------------------------------------------------------------------------*/
#ifndef UTILITIES_H__
#define UTILITIES_H__

#include "interrupts.h"

void pause(void);
void wait(void);

void pause(void)
{
  /* 
   * ===  FUNCTION  ======================================================================
   *         Name:  pause
   *  Description:  Wait for one PCA overflow (~20ms)
   * =====================================================================================
   */
  unsigned char count = nCounts;
  while ( count == nCounts );		
}

void wait(void)
{
  /* 
   * ===  FUNCTION  ======================================================================
   *         Name:  wait
   *  Description:  Wait for 50 PCA overflows (~50ms)
   * =====================================================================================
   */
  nCounts = 0;
  while ( nCounts < 50 );
}

#endif
