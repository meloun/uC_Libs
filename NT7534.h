//**********************************************************************************************
// NT7534.h - radic pro display BATRON (BT45182)
// (C)2010 Knuerr s.r.o, Ing. Lubos Melichar, Ing. Petr Kerndl
//**********************************************************************************************

//**********************************************************************************************

#ifndef NT7534_H_
#define NT7534_H_
#include <types.h>

//data
#define PIN_A0_DDR      DDRA.2   
#define PIN_A0          PORTA.2   

//reset
#define PIN_RES_DDR     DDRA.1
#define PIN_RES         PORTA.1

//chip select
#define NT7534_CS_DDR       DDRB.4
#define NT7534_SET_CS	    PORTB.4 = 0
#define NT7534_CLEAR_CS     PORTB.4 = 1

//
//#define SET_COMMA


#define A0          PORTA.2   //display mode select
#define CS0         PORTB.4   //display chip enable
#define RES         PORTA.1   //display reset


#define NR_ROWS         8
#define NR_COLUMNS      21


void NT7534_Init();
void NT7534_clear_screen(void);
void NT7534_set_screen(byte *pRows[NR_ROWS]);
void NT7534_set_paging(byte current, byte max);
void NT7534_manager();

  


#endif /* NT7534_H_ */
