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
#define NR_MESSMODULES  4

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



// SELECT MESSMODULE
#define MESSMODULE_SELECT(nr){ \    
    switch(nr){ \
        case 0: SPI_SET_CS2; break; \
        case 1: SPI_SET_CS3; break; \
        case 2: SPI_SET_CS4; break; \
        case 3: SPI_SET_CS5; break; \        
        default: break;\
    } \
}

#define MESSMODULE_DESELECT  SPI_CLEAR_ALL_CS

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
       
        
}tMESSMODULE_VALUES;



typedef struct{
    char status; 
	
    tMESSMODULE_VALUES   values;

}tMESSMODULE;

typedef struct{
	
    tMESSMODULE sModule[4];
    
    byte nr_available_modules;
    byte nr_current_module;
    byte rest_flag;         
}tMESSMODULES;

void Messmodul_Init();
void Messmodul_spi(byte nr_module);
void Messmodul_Manager();
void Messmodul_Rest();
byte Messmodul_getCountVoltage();
byte Messmodul_getCountCurrent();

extern tMESSMODULES  sMm;


#endif /* MESSMODULES_H_ */
