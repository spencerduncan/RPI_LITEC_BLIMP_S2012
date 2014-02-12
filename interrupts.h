
/*-----------------------------------------------------------------------------
 *  interrupts.h - PCA interrupt handling & variables
 *-----------------------------------------------------------------------------*/

#ifndef INTERRUPT_H__
#define INTERRUPT_H__

unsigned long time=0;
unsigned char nCounts=0;
unsigned char h_count=0;
unsigned char r_count=0;

unsigned char new_range=0;
unsigned char new_heading=0;

// Interrupt Service Routine for Programmable Counter Array Overflow Interrupt
//
void PCA_ISR ( void ) __interrupt 9
{
  // reference to the sample code in Example 4.5 -Pulse Width Modulation 
  // implemented using the PCA (Programmable Counter Array), p. 50 in Lab Manual.
  if (CF)			//PCA Counter/Timer overflow flag
    {
      CF=0;	// Clear overflow flag

      PCA0L = 28614;  // low byte of start count
      PCA0H = 28614 >> 8; // High byte of start count 
      ++h_count;
      ++r_count;
      ++nCounts;
      ++time;
      if ( nCounts > 50)
      {
        nCounts = 0;
  //			Counts++;
      }
      if(h_count >=2)		//2 overflows is about 40ms
        {
        new_heading =1;
        h_count=0;
        }
      if( r_count >= 5 )
      {
        new_range = 1;
        r_count = 0;
      }

    }
  else PCA0CN &= 0xC0;		// Handle other PCA interrupt source
}


#endif
