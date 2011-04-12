//**********************************************************************************************
// SPI communication driver
// (C)2010 Knuerr s.r.o., Ing. Lubos Melichar
//**********************************************************************************************
  #include <mega324a.h>    
  #include <types.h>
  #include <my_spi.h>


#include <stdio.h>
//**********************************************************************************************

void SPI_MasterInit(void)
{
 
    /* Set MOSI and SCK output, all others input */
    //DDRB = 0xB0;          
    DDRB.0 = 1; //cs4 output
    DDRB.1 = 1; //cs3 output
    DDRB.2 = 1; //cs2 output
    DDRB.3 = 1; //cs1 output
    DDRB.4 = 1; //cs0 output (display)        
    DDRB.5 = 1; //mosi output   
    DDRB.6 = 0; //miso input
    PORTB.6 = 1; //miso pullup
    DDRB.7 = 1; //SCK output    
    //printf("\nDDR_SPI: %x, %x \n", DDRB, (1<<DD_MOSI)|(1<<DD_SCK));
 
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);
    
}

//**********************************************************************************************
byte SPI_MasterTransmit(byte tx_data)
{
  //byte auxb;              

  //auxb = SPDR;        // vycteni bufferu (shozeni pripadneho flagu SPIF)
  
  /* Start transmission */
  SPDR = tx_data;
  
  /* Wait for transmission complete */
  while(!(SPSR & (1<<SPIF)));

  //read  
  return(SPDR);
}

unsigned char SPI_MasterTransmit2(unsigned char data)
{
SPDR=data;
while ((SPSR & (1<<SPIF))==0);
return SPDR;
}