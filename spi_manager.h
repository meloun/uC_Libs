//*******************************************************************
// spi_manager.h
// (C)2010 Knuerr s.r.o., Ing. Lubos Melichar
//*******************************************************************
// uzivatelska konfigurace v spi_manager_user.h
//*******************************************************************
#ifndef _SPI_MANAGER_H
#define _SPI_MANAGER_H

    #include <my_spi.h>
    #include <spi_manager_user.h>

/** MACROS **/

  // SET SPEED
  // focs/2
	#define SET_SPI_SPEED_2 \
		SPSR |= 0x01;\
		SPCR &= ~0x03;
  // focs/4
	#define SET_SPI_SPEED_4 \
		SPSR &= ~0x01;\
		SPCR &= ~0x03;
  // focs/8
	#define SET_SPI_SPEED_8 \
		SPSR |= 0x01;\
		SPCR &= ~0x02;\
		SPCR |= 0x01;
  // focs/16
	#define SET_SPI_SPEED_16 \
		SPSR &= ~0x01;\
		SPCR &= ~0x02;\
		SPCR |= 0x01;
  // focs/64
	#define SET_SPI_SPEED_64 \
		SPSR |= 0x01;\
		SPCR |= 0x03;

	// SELECT SLAVE
	#define SET_SPI_CS1	 SPI_CS1_PORT &= ~SPI_CS1_PIN;
	#define SET_SPI_CS2  SPI_CS2_PORT &= ~SPI_CS2_PIN;
	#define SET_SPI_CS3  SPI_CS3_PORT &= ~SPI_CS3_PIN;
	#define SET_SPI_CS4  SPI_CS4_PORT &= ~SPI_CS4_PIN;
	#define SET_SPI_CS5  SPI_CS5_PORT &= ~SPI_CS5_PIN;
	#define SET_SPI_CS6  SPI_CS6_PORT &= ~SPI_CS7_PIN;
	#define SET_SPI_CS7  SPI_CS7_PORT &= ~SPI_CS7_PIN;
	#define SET_SPI_CS8  SPI_CS8_PORT &= ~SPI_CS8_PIN;
	

	// SELECT SLAVE FROM PARAMETER
	#define SET_SPI_CS(nr){ \
		SET_SPI_SPEED_4;\
		switch(nr){ \
			case 0: break; \
			case 1: SET_SPI_CS1; break; \
			case 2: SET_SPI_CS2; break; \
			case 3: SET_SPI_CS3; break; \
			case 4: SET_SPI_CS4; break; \
			default: break;\
		} \
	}

	// ALL SLAVES INACTIVE
	#define CLEAR_SPI_ALL_CS	\
		SPI_CS1_PORT |= SPI_CS1_PIN; \
		SPI_CS2_PORT |= SPI_CS2_PIN; \
		SPI_CS3_PORT |= SPI_CS3_PIN; \
		SPI_CS4_PORT |= SPI_CS4_PIN; \				
		#asm("nop"); #asm("nop");

	typedef void ( *pSPI_FUNCTION ) (byte);

	//extern byte actual_slave;

	//extern void SPI_Manager_Init(void);
    /*extern void SPI_Manager(void);*/

#endif  /* SPI_MANAGER_H_ */


