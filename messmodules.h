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

/* CONVERSION */
#define VOLTAGE_CONVERSION         7852
#define CURRENT_CONVERSION         793
#define POWER_ACT_CONVERSION       412
#define POWER_APP_CONVERSION       412
#define ENERGY_ACT_CONVERSION      412
#define ENERGY_APP_CONVERSION      412
#define PF_CONVERSION              412

/* RESTRICTION */
#define VOLTAGE_MIN                20   // [V * 10]
#define CURRENT_MIN                5    // [A * 10]
#define POWER_ACT_MIN              2    // [W * 10]
#define POWER_APP_MIN              2    // [VA * 10]
#define ENERGY_ACT_MIN             2    // []
#define ENERGY_APP_MIN             2    // []



typedef struct{
    byte* pFlag;
    byte read_write; //
    byte command_index;
    byte* pBuffer;
}tMESSMODUL_REQUEST_DEF;


typedef struct{
                
    word temperature; 
    word frequence;
    word voltage[4]; //posledni je nulova, obezlicka kvuli prochazeni v cyklu
    word current[4];
    signed long power_act[4];
    signed long power_app[4];
    signed long energy_act[4]; 
    signed long energy_app[4];
    signed long power_factor[4];
   
        
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
