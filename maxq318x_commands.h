//*******************************************************************
// messmodules.h
// (C)2010 Knuerr s.r.o, Ing. Lubos Melichar
//*******************************************************************
// 
//*******************************************************************
#ifndef MAX318X_COMMANDS_H_
#define MAX318X_COMMANDS_H_

#include <types.h>



/* PARAMETERS */
#define NR_COMMAND     20


typedef enum{ 
    eSTATUS, //0
    eOP_MODE1, eOP_MODE2, eOP_MODE3, //1-3
    eIRQ_FLAG, eIRQ_MASK, //4-5
    //eSCAN_IA, eSCAN_VA, eSCAN_IC, eSCAN_VC, eSCAN_IB, eSCAN_VB, SCAN_IN, SCAN_TE, //6-13
    //eAUX_CFG, eSYS_KHZ, eVOLT_CC, eAMP_CC, ePWR_CC, eENR_CC, eCYCNT, ePLSCFG1, //17-24
    //ePLS1_WD, eTHR1, eREJ_NS, eAVG_NS, //25 -28
    eLINEFR,
    eA_PF, eA_VRMS, eA_IRMS, 
    eB_PF, eB_VRMS, eB_IRMS,
    eC_PF, eC_VRMS, eC_IRMS,
    eRAWTEMP
                      
    }eCOMMNADS_INDEX;  
    
typedef enum{eAFE_READ, eAFE_WRITE}eAFE_READ_WRITE;    

/* REGISTER MAP */
//RAM

//status
#define AFE_STATUS    0x000
#define AFE_OP_MODE1  0x001
#define AFE_OP_MODE2  0x002
#define AFE_OP_MODE3  0x003
#define AFE_IRQ_FLAG  0x004
#define AFE_IRQ_MASK  0x006

#define AFE_LINEFR    0x062

#define AFE_SCAN_IA   0x008
#define AFE_SCAN_VA   0x009
#define AFE_SCAN_TE   0x00F

//configuration
#define AFE_VOLT_CC 0x014 //default 0x0001
#define AFE_AMP_CC  0x016 //default 0x0001
#define AFE_PWR_CC  0x018 //default 0x0001
#define AFE_ENR_CC  0x01A //default 0x0001

//calibration
#define AFE_A_I_GAIN    0x130 //default 0x0000
#define AFE_A_V_GAIN    0x132 //default 0x0000

#define AFE_R_ADCRATE    0x04E //default 0x013f

//line A
//#define A_I_GAIN  0x130
//#define A_V_GAIN  0x132
#define AFE_A_E_GAIN  0x134

//line B
#define AFE_B_I_GAIN  0x21C
#define AFE_B_V_GAIN  0x21E
#define AFE_B_E_GAIN  0x220

//line C
#define AFE_C_I_GAIN  0x308
#define AFE_C_V_GAIN  0x30A
#define AFE_C_E_GAIN  0x30C


//line A
#define AFE_A_PF    0x1C6
#define AFE_A_VRMS  0x1C8
#define AFE_A_IRMS  0x1CC
#define AFE_A_ACT   0x1D0
#define AFE_A_APP   0x1D8
#define AFE_A_EAPOS 0x1E8
#define AFE_A_EANEG 0x1EC


//line B
#define AFE_B_PF    0x2B2
#define AFE_B_VRMS  0x2B4
#define AFE_B_IRMS  0x2B8
#define AFE_B_ACT   0x2BC
#define AFE_B_APP   0x2C4
#define AFE_B_EAPOS 0x2D4
#define AFE_B_EANEG 0x2D8


//line C
#define AFE_C_PF    0x39E
#define AFE_C_VRMS  0x3A0
#define AFE_C_IRMS  0x3A4
#define AFE_C_ACT   0x3A8
#define AFE_C_APP   0x3B0
#define AFE_C_EAPOS 0x3C0
#define AFE_C_EANEG 0x3C4

//total





//VIRTUAL

//power
#define AFE_PWRP_A  0x801
#define AFE_PWRP_B  0x802
#define AFE_PWRP_C  0x804

#define AFE_PWRS_A  0x821
#define AFE_PWRS_B  0x822
#define AFE_PWRS_C  0x824


//voltage
#define AFE_V_A  0x831
#define AFE_V_B  0x832
#define AFE_V_C  0x834


//current
#define AFE_I_N  0x840
#define AFE_I_A  0x841
#define AFE_I_B  0x842
#define AFE_I_C  0x844

//energy
#define AFE_A_ENRP  0x871
#define AFE_B_ENRP  0x872
#define AFE_C_ENRP  0x874

#define AFE_A_ENRS  0x871
#define AFE_B_ENRS  0x872
#define AFE_C_ENRS  0x874



#define AFE_RAWTEMP 0xC01


typedef struct{
    word address;
    byte size;
    byte read_write;
}tCOMMAND_DEF;



extern flash tCOMMAND_DEF COMMAND_DEF[];


#endif /* MAX318X_H_ */
