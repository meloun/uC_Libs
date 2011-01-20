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

    // 0-4 Messmodules
    #define NR_MESSMODULES  4
    
    /* CALIBRATION MODE */    
    // not only calibrated values also registers are saved (and showed on display)      
    #define MM_CALIBRATION_MODE 
    
    //define ONE coils type
    #define MM_COILSTYPE_TC1V   //nejstarsi verze MM, civky na DPS
    //#define MM_COILSTYPE_XX     //civky pres konektor

/* END OF USER PARAMETERS */

/* CONVERSION */
//nejstarsi verze, delic 5x100k - 1k
#ifdef  MM_COILSTYPE_TC1V
    #define VOLTAGE_CONVERSION         785
    #define CURRENT_CONVERSION         793
    #define POWER_ACT_CONVERSION       412
    #define POWER_APP_CONVERSION       412
    #define ENERGY_ACT_CONVERSION      412
    #define ENERGY_APP_CONVERSION      412
    #define PF_CONVERSION              412
#endif

//delic 3x - 1k
#ifdef  MM_COILSTYPE_XX
    #define VOLTAGE_CONVERSION         0
    #define CURRENT_CONVERSION         0
    #define POWER_ACT_CONVERSION       0
    #define POWER_APP_CONVERSION       0
    #define ENERGY_ACT_CONVERSION      0
    #define ENERGY_APP_CONVERSION      0
    #define PF_CONVERSION              0
#endif

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

/* REGISTERS */
typedef struct{      
    dword v_x[4];
    dword i_x[4];
    signed long pwrp_x[4];
    signed long pwrs_x[4];
    signed long enrp_x[4];       
    signed long enrs_x[4];
    signed long pf_x[4];
}tMESSMODULE_REGISTERS; 




typedef struct{
    char status; 
	
    tMESSMODULE_VALUES   values;
     
  #ifdef MM_CALIBRATION_MODE  
    tMESSMODULE_REGISTERS   registers; 
  #endif

}tMESSMODULE;

typedef struct{
	
    tMESSMODULE sModule[4];
    
    byte nr_available_modules;
    byte nr_current_module;
    byte rest_flag;         
}tMESSMODULES;

void Messmodul_Init();
void Messmodule_spi(byte nr_module);
void Messmodul_Manager();
void Messmodul_Rest();
byte Messmodul_getCountVoltage(byte nr_messmodul);
byte Messmodul_getCountCurrent(byte nr_messmodul);

extern tMESSMODULES  sMm;


#endif /* MESSMODULES_H_ */
