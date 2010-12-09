//**********************************************************************************************
// messmodules.c - 
// (C)2010 Knuerr s.r.o., Ing. Lubos Melichar
//**********************************************************************************************

#include <hw_def.h>
#include <stdio.h>
#include <string.h>
#include <delay.h>
#include <maxq318x.h>
#include <maxq318x_commands.h>
#include <messmodules.h>
#include <spi_manager_user.h>
#include <spi_manager.h>
#include <uart2.h>    //124B


signed int buffer2signed(byte *pBuffer, byte length);

tMESSMODUL  sMm[1];


//flash tMESSMODUL_REQUEST_DEF MESSMODUL_REQUEST_DEF[3] = {
//    {&sMm.flags.voltage[0], 0, 6, (byte *)&sMm.values.voltages[0]}, //voltages
//    {&sMm.flags.voltage[0], 0, 6, (byte *)&sMm.values.voltages[0]}, //voltages
//    {&sMm.flags.voltage[0], 0, 6, (byte *)&sMm.values.voltages[0]} //voltages
//};

void Messmodul_Init(){

    signed char my_sign = -1;
    byte buffer[8]={1,2,3,4,5,6,7,8};
    signed long my_value = my_sign ? *(long *)buffer : -*(long *)buffer;
    
    tMESSMODUL *pMessmodul = &sMm[0];
  
    
    maxq_Init();
    //memset(&pMessmodul->flags, 0, sizeof(pMessmodul->flags));
    
    //PORTB=0x00;
    //DDRB=0xB0;
    
    //CS AS OUTPUT
    DDRB.3 = 1;
    PORTB.3 = 1; 
}

/*******************************************/
// MESSMODUL_SPI()
/*******************************************/
// receive reqeusted values from Messmodule
// convert ADC values to electrical quantity
/*******************************************/
void Messmodul_spi(byte nr_messmodul){
    byte i;
    //byte buffer[10];
    
    tMESSMODUL *pMessmodul = &sMm[nr_messmodul];   
                                    
    //1F values
    maxq_read( AFE_LINEFR,      (byte *)&pMessmodul->values.frequence,  eTWO_BYTES);     
    maxq_read( AFE_RAWTEMP,     (byte *)&pMessmodul->values.rawtemp,    eTWO_BYTES);    
    
    //voltage
    maxq_read( AFE_A_VRMS,      (byte *)&pMessmodul->values.vrms[0],    eFOUR_BYTES);                                     
    maxq_read( AFE_B_VRMS,      (byte *)&pMessmodul->values.vrms[1],    eFOUR_BYTES);
    maxq_read( AFE_C_VRMS,      (byte *)&pMessmodul->values.vrms[2],    eFOUR_BYTES);
    
    //current
    maxq_read( AFE_A_IRMS,      (byte *)&pMessmodul->values.irms[0],    eFOUR_BYTES);                                     
    maxq_read( AFE_B_IRMS,      (byte *)&pMessmodul->values.irms[1],    eFOUR_BYTES);
    maxq_read( AFE_C_IRMS,      (byte *)&pMessmodul->values.irms[2],    eFOUR_BYTES);    
    
    //power factor
    maxq_read( AFE_A_PF,        (byte *)&pMessmodul->values.pf[0],      eTWO_BYTES);                                     
    maxq_read( AFE_B_PF,        (byte *)&pMessmodul->values.pf[1],      eTWO_BYTES);   
    maxq_read( AFE_C_PF,        (byte *)&pMessmodul->values.pf[2],      eTWO_BYTES);
    
    //conversions    
    //maxq_read( AFE_VOLT_CC,     (byte *)&pMessmodul->values.volt_cc,    eTWO_BYTES);                                            
    //maxq_read( AFE_AMP_CC,      (byte *)&pMessmodul->values.amp_cc,     eTWO_BYTES);
                     

    /*******************************************/
    // POWER
    /*******************************************/  
    
    //active power
    maxq_read( AFE_A_ACT,     (byte *)&pMessmodul->values.act[0],   eFOUR_BYTES);                                     
    maxq_read( AFE_B_ACT,     (byte *)&pMessmodul->values.act[1],   eFOUR_BYTES);
    maxq_read( AFE_C_ACT,     (byte *)&pMessmodul->values.act[2],   eFOUR_BYTES); 
    
    //apparent power
    maxq_read( AFE_A_APP,     (byte *)&pMessmodul->values.app[0],   eFOUR_BYTES);                                     
    maxq_read( AFE_B_APP,     (byte *)&pMessmodul->values.app[1],   eFOUR_BYTES);
    maxq_read( AFE_C_APP,     (byte *)&pMessmodul->values.app[2],  eFOUR_BYTES);
    
    
    /*******************************************/
    // ENERGY
    /*******************************************/
    
    //real positive energy
    maxq_read( AFE_A_EAPOS,     (byte *)&pMessmodul->values.eapos[0],   eFOUR_BYTES);                                     
    maxq_read( AFE_B_EAPOS,     (byte *)&pMessmodul->values.eapos[1],   eFOUR_BYTES);
    maxq_read( AFE_C_EAPOS,     (byte *)&pMessmodul->values.eapos[2],   eFOUR_BYTES);
    
    //real negative energy
    maxq_read( AFE_A_EANEG,     (byte *)&pMessmodul->values.eaneg[0], eFOUR_BYTES);                                     
    maxq_read( AFE_B_EANEG,     (byte *)&pMessmodul->values.eaneg[1], eFOUR_BYTES);
    maxq_read( AFE_C_EANEG,     (byte *)&pMessmodul->values.eaneg[2], eFOUR_BYTES);
    
    
    //energy positive
    maxq_read( AFE_A_ENRP,     (byte *)&pMessmodul->values.enrp_x[0], eEIGHT_BYTES);                                     
    maxq_read( AFE_B_ENRP,     (byte *)&pMessmodul->values.enrp_x[1], eEIGHT_BYTES);
    maxq_read( AFE_C_ENRP,     (byte *)&pMessmodul->values.enrp_x[2], eEIGHT_BYTES);    
    //maxq_read( AFE_T_ENRP,     (byte *)&pMessmodul->values.total_enrp, eEIGHT_BYTES);
     
    
    /* CONVERSIONED VALUES */
    
      maxq_read( AFE_V_A, pMessmodul->values.v_x[0], eEIGHT_BYTES);                                     
//    maxq_read( AFE_V_B, pMessmodul->values.v_x[1], eEIGHT_BYTES);
//    maxq_read( AFE_V_C, pMessmodul->values.v_x[2], eEIGHT_BYTES);

//    maxq_read( AFE_I_A, pMessmodul->values.current[0], eEIGHT_BYTES);                                     
//    maxq_read( AFE_I_B, pMessmodul->values.current[1], eEIGHT_BYTES);
//    maxq_read( AFE_I_C, pMessmodul->values.current[2], eEIGHT_BYTES);

    //real power
//    maxq_read( AFE_PWRP_A, pMessmodul->values.pwrp_x[0], eEIGHT_BYTES);                                     
//    maxq_read( AFE_PWRP_B, pMessmodul->values.pwrp_x[1], eEIGHT_BYTES);
//    maxq_read( AFE_PWRP_C, pMessmodul->values.pwrp_x[2], eEIGHT_BYTES);

    /*******************************************/
    // CONVERT
    /*******************************************/
    pMessmodul->values.temperature =  pMessmodul->values.rawtemp / 76;
    for(i=0; i<3; i++){
        dword unsigned_value;
        signed long signed_value;
        
        //voltage
        unsigned_value = (*(dword *)pMessmodul->values.v_x[i]) >> 8; 
        pMessmodul->values.voltage[i] = (unsigned_value * VOLTAGE_CONVERSION) / 100000;  
        
        //current                      
        unsigned_value = (*(dword *)pMessmodul->values.i_x[i]) >> 8;       
        pMessmodul->values.current[i] =  (unsigned_value * CURRENT_CONVERSION) / 10000;

        //activ power
        signed_value = buffer2signed(pMessmodul->values.pwrp_x[i], 8); 
        pMessmodul->values.power_act[i] = (signed_value * POWER_ACT_CONVERSION) / 100000;

        //apparent power        
        //signed_value = buffer2signed(pMessmodul->values.pwrs_x[i], 8) 
        //pMessmodul->values.energy[i]  = (signed_value * POWER_APP_CONVERSION) / 100000;
        
        //activ energy
        signed_value = buffer2signed(pMessmodul->values.enrp_x[i], 8); 
        pMessmodul->values.energy[i]  = (signed_value * ENERGY_APP_CONVERSION) / 100000;
        
        //apparent energy
        //signed_value = buffer2signed(pMessmodul->values.enrs_x[i], 8) 
        //pMessmodul->values.energy[i]  = (signed_value * ENERGY_APP_CONVERSION) / 100000;
        
        //minimalni zmeritelte napeti
        if(pMessmodul->values.voltage[i] < VOLTAGE_MIN)
            pMessmodul->values.voltage[i] = 0;
            
        //minimalni zmeritelny proud
        if(pMessmodul->values.current[i] < CURRENT_MIN)
            pMessmodul->values.current[i] = 0;
            
        //minimalni zmeritelny vykon
        if(pMessmodul->values.power_act[i] < POWER_ACT_MIN)
            pMessmodul->values.power_act[i] = 0;             
    }
    
    sMm[0].rest_flag = 1;       
}

/*******************************************/
// MESSMODUL_MANAGER()
/*******************************************/
// process function
/*******************************************/
void Messmodul_Manager(){
    //printf("\nMM start");    
    PORTB.3 = 0;
    Messmodul_spi(0);
    PORTB.3 = 1;
    //printf("\nMM end");      
}


/*******************************************/
// MESSMODUL_REST()
/*******************************************/
// "while fuction", print debug messages
/*******************************************/
void Messmodul_Rest(){
     
    if(sMm[0].rest_flag){
        tMESSMODUL *pMessmodul = &sMm[0];        
        //print values
        printf("\n============");
        printf("\nfrequence: %u", pMessmodul->values.frequence);                                                     
        printf("\ntemperature: 0x%x, %u.%u°C", pMessmodul->values.rawtemp, pMessmodul->values.temperature / 10, pMessmodul->values.temperature % 10);
        //printf("\nCC: volt:%d, amp:%d", pMessmodul->values.volt_cc, pMessmodul->values.amp_cc);
        //printf("\nPF: %d, %d, %d", pMessmodul->values.pf[0], pMessmodul->values.pf[1], pMessmodul->values.pf[2]);
        //printf("\nPF: %ld, %ld, %ld", pMessmodul->values.pf[0], pMessmodul->values.pf[1], pMessmodul->values.pf[2]);
        //printf("\nVRMS: 0x%lx, 0x%lx, 0x%lx", pMessmodul->values.vrms[0], pMessmodul->values.vrms[1], pMessmodul->values.vrms[2]);
        //printf("\nIRMS: 0x%lx, 0x%lx, 0x%lx", pMessmodul->values.irms[0], pMessmodul->values.irms[1], pMessmodul->values.irms[2]);
        //printf("\nACT: %ld, %ld, %ld", pMessmodul->values.act[0], pMessmodul->values.act[1], pMessmodul->values.act[2]);
        //printf("\nACT: %x, %x, %x", pMessmodul->values.act[0], pMessmodul->values.act[1], pMessmodul->values.act[2]);    
        //printf("\nACT: %lx, %lx, %lx", pMessmodul->values.act[0], pMessmodul->values.act[1], pMessmodul->values.act[2]);
        //printf("\nACT: %ld, %ld, %ld", pMessmodul->values.act[0], pMessmodul->values.act[1], pMessmodul->values.act[2]);
        //printf("\nEAPOS: %lx, %lx, %lx", pMessmodul->values.eapos[0], pMessmodul->values.eapos[1], pMessmodul->values.eapos[2]);
        //printf("\nEANEG: %lx, %lx, %lx", pMessmodul->values.eaneg[0], pMessmodul->values.eaneg[1], pMessmodul->values.eaneg[2]);
        //printf("\nvoltage: %u, %u, %u", pMessmodul->values.voltage[0], pMessmodul->values.voltage[1], pMessmodul->values.voltage[2]);
        //printf("\npwrp: 0x%ld, 0x%ld | 0x%ld,  0x%ld | 0x%ld,  0x%ld",  *(dword *)pMessmodul->values.pwrp_x[0], *((dword *)pMessmodul->values.pwrp_x[0]+1), *(dword *)pMessmodul->values.pwrp_x[1], *((dword *)pMessmodul->values.pwrp_x[1]+1), *(dword *)pMessmodul->values.pwrp_x[2], *((dword *)pMessmodul->values.pwrp_x[2]+1));        
        //printf("\nvrms: %ld | %ld | %ld",  pMessmodul->values.vrms[0],  pMessmodul->values.vrms[1], pMessmodul->values.vrms[2]);
        //printf("\nirms: %ld | %ld | %ld",  pMessmodul->values.irms[0],  pMessmodul->values.irms[1], pMessmodul->values.irms[2]);
        printf("\nvoltage: %ld | %ld | %ld",  pMessmodul->values.voltage[0], pMessmodul->values.voltage[1], pMessmodul->values.voltage[2]);
        printf("\nvrms: %ld",  pMessmodul->values.vrms[0]);
        printf("\nv_x: %ld | %ld",  *(dword *)&(pMessmodul->values.v_x[0][0]), *(dword *)&(pMessmodul->values.v_x[0][4]));
        printf("\nv_x: %x,%x,%x,%x,%x,%x,%x,%x", pMessmodul->values.v_x[0][0], pMessmodul->values.v_x[0][1], pMessmodul->values.v_x[0][2], pMessmodul->values.v_x[0][3], pMessmodul->values.v_x[0][4], pMessmodul->values.v_x[0][5], pMessmodul->values.v_x[0][6], pMessmodul->values.v_x[0][7]);
        printf("\nv_x: %ld", buffer2signed(pMessmodul->values.v_x[0],8));        
        
        printf("\ncurrent: %ld | %ld | %ld",  pMessmodul->values.current[0], pMessmodul->values.current[1], pMessmodul->values.current[2]);
        //printf("\ncurrent A: 0x%ld, 0x%ld | 0x%ld,  0x%lx | 0x%lx,  0x%lx", *(dword *)pMessmodul->values.current[0], *((dword *)pMessmodul->values.current[0]+1),*(dword *)pMessmodul->values.current[1], *((dword *)pMessmodul->values.current[1]+1),*(dword *)pMessmodul->values.current[2], *((dword *)pMessmodul->values.current[2]+1));
        sMm[0].rest_flag = 0;
    }                            
}

byte Messmodul_getCountVoltage(){
    byte i,aux_count = 0;  
    tMESSMODUL *pMessmodul = &sMm[0];
    
    for(i=0; i<3; i++)
        if(pMessmodul->values.voltage[i])
            aux_count++;
        
    return aux_count;
}
byte Messmodul_getCountCurrent(){
    byte i,aux_count = 0;
    tMESSMODUL *pMessmodul = &sMm[0];
    
    for(i=0; i<3; i++)
        if(pMessmodul->values.current[i])
            aux_count++;
            
    return aux_count;
}

signed int buffer2signed(byte *pBuffer, byte length){

     //most significant bit is the sign 
     byte my_sign = *(pBuffer + (length-1)) & 0x80 ? 1 : 0;
     return  my_sign ? -*(long *)pBuffer : *(long *)pBuffer;   
}
