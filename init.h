/*-----------------------------------------------------------------------------
 * init.h - All the initialization functions 
 *-----------------------------------------------------------------------------*/

#ifndef INIT_H__
#define INIT_H__

void Port_Init(void);		//Initialize Port
void PCA_Init (void);		//initialize PCA 
void XBR0_Init();			//Initialize XBR0

void Interrupt_Init(void);	//Initialize interrupt service
void SMB_Init(void);	//initialize SMB
void ADC_Init (void); 	//initialize analog digital conversion

//-----------------------------------------------------------------------------
// Port_Init
//-----------------------------------------------------------------------------
//
// Set up ports for input and output
//
void Port_Init()
{
  P0MDOUT |= 0xC0;		
  P3MDOUT &= ~0x80;		//Slide switch input at  P3.7(32)
  P3 |=0x80; 

  P1MDOUT |=0x04; 		//input for ranger

  P1MDIN &=~0x10;			//set P1.4 as analog input
  P1MDOUT &=~0x10;		//set P1.4 as open drain mode
  P1 |= 0x10;
}

//-----------------------------------------------------------------------------
// XBR0_Init
//-----------------------------------------------------------------------------
//
// Set up the crossbar
//
void SMB_Init(void)
{
  SMB0CR = 0x93;
  ENSMB=1;
}

void XBR0_Init()
{
  XBR0 = 0x27; 	//configure crossbar to 0x27					 		
}

void ADC_Init(void)
{	
  REF0CN=0x03;	//set Vref to internal reference voltage of 2.4v
  ADC1CN = 0x80;		//Enable A/D Converter
  ADC1CF |=0x01; //set A/D converter gain to 1
}
 
//-----------------------------------------------------------------------------
// PCA_Init
//-----------------------------------------------------------------------------
//
// Set up Programmable Counter Array
// PCA_ISR
void PCA_Init(void)
{
  // reference to the sample code in Example 4.5 -Pulse Width Modulation 
  // implemented using the PCA (Programmable Counter Array), p. 50 in Lab Manual.
  PCA0MD = 0x81;		//enable CF interrupt (SYSCLK/12)
  PCA0CPM0=0xC2;		//CCM0 in 16 bit compare mode
  PCA0CPM1=0xC2;		//CCM1 in 16 bit compare mode 
  PCA0CPM2=0xC2;		//CCM2 in 16 bit compare mode 
  PCA0CPM3=0xC2;		//CCM3 in 16 bit compare mode
  EIE1 |=0x08;		//Enable PCA interrupt 
  PCA0CN=0x40;		//Enable PCA counter 
  EA = 1;
}

void Interrupt_Init(void)
{
  EIE1 |= 0x08;
  EA =1;		//Enable global interrupts
}

#endif
