/*
 * cards.h
 *
 *  Created on: 29.10.2008
 *      Author: Luboš Melichar
 */

#ifndef CARDS_H_
#define CARDS_H_

#include <hw_def.h>
#include <IQhouseComm\IQhouseMID.h>
#include "lru\card_di.h"
#include "lru\card_do.h"
#include "lru\card_vc.h"

#define CARD_SET_SPI_SPEED(type){ \
	switch(type){ \
		case CARD_TYPE_DI: \
			SET_SPI_SPEED_4 \
			break; \
		case CARD_TYPE_DO: \
			SET_SPI_SPEED_8 \
			break; \
		default: \
		 break; \
	} \
}
//disable int, chipselect card
#define CARD_START_COMM(nr_card) \
  TIMSK0 = 0x00;\    	//zakaz kernel interruptu
  EIMSK &= ~0x20;\   	//zakaz ext interruptu
  CLEAR_SPI_ALL_CS;\ 	//all slaves inactive
  SET_SPI_CS(nr_card);\ //select next slave
	CARD_SET_SPI_SPEED(sCards[nr_card-1].type)\

#define CARD_END_COMM \
	CLEAR_SPI_ALL_CS;\ 	// all slaves inactive
  TIMSK0 = 0x02;\    	// povoleni kernel interruptu
  EIMSK |= 0x20    		// povoleni ext interuptu


#define NR_CARDS			  	  4
#define NR_INPUTS_CARDS   	2
#define NR_OUTPUTS_CARDS  	2

//delays for spi
#define DELAY_US_SEND						10//5 //after sending
#define DELAY_US_RECEIVE				10//5 //after receiving

//CARD TYPES DEFINES
#define NR_CARD_TYPES		5

//PROCEED
#define CARDS_PERIODIC_READ
#define CARDS_EXTERNAL_INTERRUPT
//parameters for proceed
#define CARDS_PERIODIC_READ_CNT		100


typedef flash struct{
	char name[12+1];
  byte nr_pins;
  void *(* spi_function) (byte nr_card);
}tCARDTYPE_DEF;

//!!pri zmene poradi upravit tabulky v channels.c
/*#define NONE							0
#define	CARD_TYPE_NONE		0
#define	AI								1
#define	CARD_TYPE_AI			1
#define DI								2
#define	CARD_TYPE_DI			2
#define	VC								3
#define	CARD_TYPE_PMDC		3
#define DO								4
#define	CARD_TYPE_DO			4*/

#define NONE							0
#define	CARD_TYPE_NONE		0
#define DI								1
#define	CARD_TYPE_DI			1
#define DO								2
#define	CARD_TYPE_DO			2
#define	VC								3
#define	CARD_TYPE_PMDC		3
#define	AI								4
#define	CARD_TYPE_AI			4



#define NR_CMDS										20
#define CMD_DI_OFFSET							0x00
#define CMD_READ_CNTR							0x01+CMD_DI_OFFSET  //read all counters
//#define	CMD_RESET_CNTR					0x02+CMD_DI_OFFSET  //reset one counters (or all 0xFF)
#define CMD_RESET_CNTR_MASK				0x03+CMD_DI_OFFSET	//reset more counters during mask
#define	CMD_SET_CNTR							0x04+CMD_DI_OFFSET	//set counter
#define CMD_READ_INPUTS						0x05+CMD_DI_OFFSET	//read all input states
#define CMD_WATCH_IN							0x06+CMD_DI_OFFSET	//watch inputs, interrupt bei change, 1.word - high level, 2.word - low lovel
#define CMD_SET_EDGES							0x07+CMD_DI_OFFSET	//1.word - rising edge, 2.word - falling edge
#define CMD_GET_IRQ								0x08+CMD_DI_OFFSET
#define CMD_CLEAR_IRQ							0x09+CMD_DI_OFFSET
#define	CMD_SET_EXT_PULLUP				0x0A+CMD_DI_OFFSET  //
#define CMD_SWITCH_INPUTS					0x0B+CMD_DI_OFFSET  //
#define	CMD_SET_LOWPASS						0x0C+CMD_DI_OFFSET  //
#define	CMD_SET_HIGHPASS					0x0D+CMD_DI_OFFSET  //
#define CMD_SET_APPLICATION       0x0E+CMD_DI_OFFSET  // nastaveni aplikacne pro jednotlive piny DI karty (PIR, Inputs, Light Switch,...)
#define CMD_SET_ACTIVE_STATE      0x0F+CMD_DI_OFFSET  // nastaveni aktivniho stavu (0,1)
#define CMD_SET_MIN_TU            0x10+CMD_DI_OFFSET  // nastaveni minimalni delky trvani zmeny stavu, vyznam je ruzny podle aplikace
#define CMD_SET_MAX_TU            0x11+CMD_DI_OFFSET  // nastaveni maximalni delky trvani zmeny stavu, vyznam je ruzny podle aplikace
#define CMD_SET_IDLE_TU           0x12+CMD_DI_OFFSET  // nastaveni minimalni delky trvani bez zmeny stavu, vyznam je ruzny podle aplikace



//IQhouse v2 commands
#define CMD_IQHOUSE_OFFSET									200 //56 cmds pro iqhouse
#define CMD_GET_VARS												1+CMD_IQHOUSE_OFFSET //posli promennou od daneho device
#define CMD_GET_BITVARS											2+CMD_IQHOUSE_OFFSET //posli bitove promenne od vsech kanalu, typicky stav vsech vystupu
#define CMD_GET_VAR_FROM_ALL_CHANNELS				3+CMD_IQHOUSE_OFFSET //posli promenne od vsech kanalu, typicky stav stav pwm vystupu

#define CMD_SET_BITVARS_PER_CHANNELSMASK		5+CMD_IQHOUSE_OFFSET //nastav promenne u vybranych kanalu
#define CMD_SET_VARS												6+CMD_IQHOUSE_OFFSET // | CMD_SET_VARS(b) | CHANNEL(b) | VAR_ID(w) | VAR(w) | CHANNELS(b) | VAR_ID(w) | VAR(w) | ...

// DEFAULT VALUES
#define DF_LP_FREQ_DEFAULT				1000
#define	DF_HP_FREQ_DEFAULT				0
#define DI_LOW_MASK_DEFAULT				0x0000
#define DI_HIGH_MASK_DEFAULT			0x0000
#define DI_LEADING_EDGE_DEFAULT		0xFFFF
#define DI_TRAILING_EDGE_DEFAULT	0x0000
#define DI_EXT_PULLUP_MASK				0x0F
#define DI_CARD_INPUTS_ON					1
#define DI_APP_DEFAULT            DI_APP_INPUT   // Input module
#define DI_ACTIVE_STATE_DEFAULT   0x0000
#define DI_MIN_TU_DEFAULT         DI_SWITCH_MIN_TU
#define DI_MAX_TU_DEFAULT         DI_SWITCH_MAX_TU
#define DI_IDLE_TU_DEFAULT        DI_SWITCH_IDLE_TU
#define DI_MAX_TU                 0xFFFFFFFFL

//SPI COMMANDS
#define NR_WAITS_FOR_ANSWER					150		//waiting for start byte (answer)
#define	LENGHT_WITHOUT_DATA					0x04 	//lenght of each packet without data - start, command/acknowledge, lenght,(data), xor
#define LENGHT_DATA_MAX							100 	//maximal number of receiving data bytes
#define START_BYTE									0x53


typedef struct{
	byte command;
	byte datalength;
	byte data[LENGHT_DATA_MAX];
}tFRAME;

typedef struct{
	byte card_exist[NR_CARD_TYPES];
}tCARDS_COMMON;

typedef struct{
	dword values[NR_COUNTERS];
}tAI;

#define RAW_SIZE	sizeof(tDI)
typedef union{
	byte raw[RAW_SIZE];
	tDI	sDi; //binary and counters
	tDO	sDo;
	tVC	sVc;
}tCARD;

typedef struct{
	byte type;								//di, do, pmdc etc.
	word int_mask;			 			//maska zdroju interuptu od karty
	byte int_mask_req;				//pozadavek na vycteni masky
	byte int_clear_req;				//pozadavek na smazani interruptu
	byte proceed_flag;	//flag pro vyvolani obsluzne funkce
	byte cmds_error[NR_CMDS]; //chyby
	tCARD uCard;
}tCARDS;


//extern flash byte CARDS_NAMES[NR_CARD_TYPES][10];
extern flash tCARDTYPE_DEF sCARDTYPE_DEF[NR_CARD_TYPES];
extern tCARDS sCards[];

void Cards_Init(void);
byte cards_setRequests(byte slave, dword req_mask);
void Cards_proceed(void);
//void spi_f_cards_router(byte slave);
byte card_spi_send_receive_verify(byte nr_card, tFRAME *sFrame);

// byte getChannelPos(byte channel, byte card_type);
// byte getCardId(byte channel, byte card_type);
//byte getCardNr(byte card_type);

#pragma used-
#pragma library cards.lib
#endif /* CARDS_H_ */
