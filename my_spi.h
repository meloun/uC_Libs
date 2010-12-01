#ifndef _spi_h
#define _spi_h

//*********************************************************************************
// Mapovani pinu SPI
//*********************************************************************************
#define DDR_SPI		DDRB
#define DD_SS		4
#define DD_MOSI		5
#define DD_MISO 	6
#define DD_SCK		7

//*********************************************************************************
//*	SPI driver public functions
//*********************************************************************************
void SPI_MasterInit(void);
byte SPI_MasterTransmit(byte tx_data); 
unsigned char SPI_MasterTransmit2(unsigned char data); 

//*********************************************************************************


#endif


