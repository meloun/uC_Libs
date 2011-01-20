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

typedef struct{

    /* RAM */ 
      
    //1F REAL REGISTERS
    word linefr;
    word rawtemp;
 
    //3F REAL REGISTERS
    //conversion coefficients
    //word volt_cc;     
    //word amp_cc;
    //word pwr_cc;
    //word enr_cc;           
    //dword vrms[3];
    //dword irms[3];    
    //signed long act[3]; 
    //signed long app[3];
    //dword eapos[3];
    //dword eaneg[3];
    signed int pf[4]; //complete power factor is virtual reg 

    /* VIRTUAL */
    byte v_x[4][8];
    byte i_x[4][8];
    byte pwrp_x[4][8];
    byte pwrs_x[4][8];
    byte enrp_x[4][8];       
    byte enrs_x[4][8];       

}tMAXQ_REGISTERS;


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
signed char maxq_write(word address, char* pData, byte datalength);




#endif /* MAX318X_H_ */
