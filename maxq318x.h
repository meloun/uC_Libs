//*******************************************************************
// messmodules.h
// (C)2010 Knuerr s.r.o, Ing. Lubos Melichar
//*******************************************************************
// 
//*******************************************************************
#ifndef MAX318X_H_
#define MAX318X_H_

#include <types.h>
#include <maxq318x_commands.h>

/* PARAMETERS */
#define LENGHT_DATA_MAX     20



typedef enum {
	eREAD = 0x00, eWRITE = 0x01
} eMAXQ_READ_WRITE;

typedef enum {
	eONE_BYTE = 0x00, eTWO_BYTES = 0x01, eFOUR_BYTES = 0x02, eEIGHT_BYTES = 0x03
} eMAXQ_DATALENGTH;

typedef struct{
	byte read_write; //0 - reead, 1 - write
	byte datalength;
    byte address1;
    byte address2;
	byte data[LENGHT_DATA_MAX];
}tMAXQ_FRAME;

void maxq_Init();
signed char maxq_read_write(byte read_write, word address, char* pData, byte datalength);
signed char maxq_read(word address, char* pData, byte datalength);
signed char maxq_read_enum(eCOMMNADS_INDEX cmd_index, char* pData);
signed char maxq_write(word address, char* pData, byte datalength);




#endif /* MAX318X_H_ */
