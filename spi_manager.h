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
    #define SET_SPI_SPEED_128 \
		SPSR &= ~0x01;\
		SPCR |= 0x03;
	            
   /*******************************************/
   // INIT CS
   /*******************************************/
   //nastaveni vsech SS jako vystupy       
   #define SPI_INIT_CS1     SPI_CS1_PORT_DIR |= SPI_CS1_PIN;
   #define SPI_INIT_CS2     SPI_CS2_PORT_DIR |= SPI_CS2_PIN;
   #define SPI_INIT_CS3     SPI_CS3_PORT_DIR |= SPI_CS3_PIN;
   #define SPI_INIT_CS4     SPI_CS4_PORT_DIR |= SPI_CS4_PIN;
   #define SPI_INIT_CS5     SPI_CS5_PORT_DIR |= SPI_CS5_PIN;
   #define SPI_INIT_CS6     SPI_CS6_PORT_DIR |= SPI_CS6_PIN;
   #define SPI_INIT_CS7     SPI_CS7_PORT_DIR |= SPI_CS7_PIN;
   #define SPI_INIT_CS8     SPI_CS8_PORT_DIR |= SPI_CS8_PIN;  
        
   #define SPI_INIT_ALL_CS	\
        SPI_INIT_CS1 \
        SPI_INIT_CS2 \
        SPI_INIT_CS3 \
        SPI_INIT_CS4 \
        SPI_INIT_CS5 \
                                
    /*******************************************/
    // SET CS
    /*******************************************/
    // SELECT SLAVE
    #define SPI_SET_CS1	 SPI_CS1_PORT &= ~SPI_CS1_PIN;
    #define SPI_SET_CS2  SPI_CS2_PORT &= ~SPI_CS2_PIN;
    #define SPI_SET_CS3  SPI_CS3_PORT &= ~SPI_CS3_PIN;
    #define SPI_SET_CS4  SPI_CS4_PORT &= ~SPI_CS4_PIN;
    #define SPI_SET_CS5  SPI_CS5_PORT &= ~SPI_CS5_PIN;
    #define SPI_SET_CS6  SPI_CS6_PORT &= ~SPI_CS7_PIN;
    #define SPI_SET_CS7  SPI_CS7_PORT &= ~SPI_CS7_PIN;
    #define SPI_SET_CS8  SPI_CS8_PORT &= ~SPI_CS8_PIN;	

    // SELECT SLAVE FROM PARAMETER
    #define SPI_SET_CS(nr){ \
        SET_SPI_SPEED_4;\
        switch(nr){ \
            case 0: break; \
            case 1: SPI_SET_CS1; break; \
            case 2: SPI_SET_CS2; break; \
            case 3: SPI_SET_CS3; break; \
            case 4: SPI_SET_CS4; break; \
            case 5: SPI_SET_CS5; break; \
            default: break;\
        } \
    }

    /*******************************************/
    // CLEAR CS
    /*******************************************/
    // ALL SLAVES INACTIVE
    #define SPI_CLEAR_ALL_CS	\
        SPI_CS1_PORT |= SPI_CS1_PIN; \
        SPI_CS2_PORT |= SPI_CS2_PIN; \
        SPI_CS3_PORT |= SPI_CS3_PIN; \
        SPI_CS4_PORT |= SPI_CS4_PIN; \
        SPI_CS5_PORT |= SPI_CS5_PIN; \				
        #asm("nop"); #asm("nop");

	typedef void ( *pSPI_FUNCTION ) (byte);

	//extern byte actual_slave;

	//extern void SPI_Manager_Init(void);
    /*extern void SPI_Manager(void);*/

#endif  /* SPI_MANAGER_H_ */


