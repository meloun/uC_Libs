//*******************************************************************
// messmodules.h
// (C)2010 Knuerr s.r.o, Ing. Lubos Melichar
//*******************************************************************
// 
//*******************************************************************
#ifndef MESSMODULES_H_
#define MESSMODULES_H_

#include <types.h>
#include <maxq318x.h>

/* USER PARAMETERS */
#define NR_MESSMODULES  1

/* END OF USER PARAMETERS */

#define VOLTAGE_CONVERSION         7852
#define CURRENT_CONVERSION         793  //793053
#define POWER_CONVERSION           412

#define VOLTAGE_MIN                20   // [V * 10]
#define CURRENT_MIN                2    // [A * 10]
#define POWER_MIN                  2    // [W * 10]



typedef struct{
    byte* pFlag;
    byte read_write; //
    byte command_index;
    byte* pBuffer;
}tMESSMODUL_REQUEST_DEF;

typedef struct{

    /* RAM */ 
    //conversion coefficients
    word volt_cc;     
    word amp_cc;
    
    //gains
    word v_gain[3];
    word i_gain[3];
    
    signed int raw_pf[3];
    dword vrms[3];
    dword irms[3];
    signed long pf[3];
    signed long act[3]; 
    signed long app[3];
    dword eapos[3];
    dword eaneg[3];
    //dword app[3];
    
    
    word frequence;
    
    /* VIRTUAL */
    byte v_x[3][8];
    byte i_x[3][8];
    byte pwrp_x[3][8];              
    
    /* SPECIAL */
    word rawtemp;    
    
    
    //convert
    signed int temperature;
    signed int voltage[3];
    signed int current[3];
    signed long power[3];
    signed long energy[3];
   
        
}tMESSMODUL_VALUES;



typedef struct{
	//tMESSMODUL_FLAGS    flags;
    tMESSMODUL_VALUES   values;
    byte rest_flag;         
}tMESSMODUL;

void Messmodul_Init();
void Messmodul_spi(byte nr_messmodul);
void Messmodul_Manager();
void Messmodul_Rest();
byte Messmodul_getCountVoltage();
byte Messmodul_getCountCurrent();

extern tMESSMODUL  sMm[NR_MESSMODULES];


#endif /* MESSMODULES_H_ */
