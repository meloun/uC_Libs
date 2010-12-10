//**********************************************************************************************
// messmodules.c - 
// (C)2010 Knuerr s.r.o., Ing. Lubos Melichar
//**********************************************************************************************

#include <hw_def.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <delay.h>
#include <math.h>
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
    
    //tMESSMODUL *pMessmodul = &sMm[0];
  
    
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
    tMAXQ_REGISTERS sMaxq_registers;
    tMAXQ_REGISTERS *pMaxq_registers = &sMaxq_registers; 

    
    /*******************************************/
    // GET VALUES FROM MAXIM
    /*******************************************/                                  
   
    //1F values
    maxq_read( AFE_LINEFR,      (byte *)&pMaxq_registers->linefr,  eTWO_BYTES);     
    maxq_read( AFE_RAWTEMP,     (byte *)&(pMaxq_registers->rawtemp), eTWO_BYTES);    

    //CONVERION CONSTANT    
    //maxq_read( AFE_VOLT_CC,     (byte *)&pMessmodul->values.volt_cc,    eTWO_BYTES);                                            
    //maxq_read( AFE_AMP_CC,      (byte *)&pMessmodul->values.amp_cc,     eTWO_BYTES);
    //maxq_read( AFE_PWR_CC,      (byte *)&pMessmodul->values.pwr_cc,     eTWO_BYTES);
    //maxq_read( AFE_ENR_CC,      (byte *)&pMessmodul->values.enr_cc,     eTWO_BYTES);
        
    //VOLTAGE
    //vrms
    maxq_read( AFE_A_VRMS,      (byte *)&pMaxq_registers->vrms[0],    eFOUR_BYTES);                                     
    maxq_read( AFE_B_VRMS,      (byte *)&pMaxq_registers->vrms[1],    eFOUR_BYTES);
    maxq_read( AFE_C_VRMS,      (byte *)&pMaxq_registers->vrms[2],    eFOUR_BYTES);
    //V.X
    maxq_read( AFE_V_A, pMaxq_registers->v_x[0], eEIGHT_BYTES);                                     
    maxq_read( AFE_V_B, pMaxq_registers->v_x[1], eEIGHT_BYTES);
    maxq_read( AFE_V_C, pMaxq_registers->v_x[2], eEIGHT_BYTES);
    //memset(pMaxq_registers->v_x[3], 0, 8); //nulove
     
    
    //CURRENT 
    //irms
    maxq_read( AFE_A_IRMS,      (byte *)&pMaxq_registers->irms[0],    eFOUR_BYTES);                                     
    maxq_read( AFE_B_IRMS,      (byte *)&pMaxq_registers->irms[1],    eFOUR_BYTES);
    maxq_read( AFE_C_IRMS,      (byte *)&pMaxq_registers->irms[2],    eFOUR_BYTES);    
    //I.X
    maxq_read( AFE_I_A, pMaxq_registers->i_x[0], eEIGHT_BYTES);                                     
    maxq_read( AFE_I_B, pMaxq_registers->i_x[1], eEIGHT_BYTES);
    maxq_read( AFE_I_C, pMaxq_registers->i_x[2], eEIGHT_BYTES);    
    //maxq_read( AFE_I_N, pMaxq_registers->i_x[3], eEIGHT_BYTES);
    
    //POWER FACTOR
    maxq_read( AFE_A_PF,        (byte *)&pMaxq_registers->pf[0],      eTWO_BYTES);                                     
    maxq_read( AFE_B_PF,        (byte *)&pMaxq_registers->pf[1],      eTWO_BYTES);   
    maxq_read( AFE_C_PF,        (byte *)&pMaxq_registers->pf[2],      eTWO_BYTES); 
    //pMaxq_registers->pf[3] = 0; //nulove
    
    //POWER
    //active power
    maxq_read( AFE_A_ACT,     (byte *)&pMaxq_registers->act[0],   eFOUR_BYTES);                                     
    maxq_read( AFE_B_ACT,     (byte *)&pMaxq_registers->act[1],   eFOUR_BYTES);
    maxq_read( AFE_C_ACT,     (byte *)&pMaxq_registers->act[2],   eFOUR_BYTES);         
    //apparent power
    maxq_read( AFE_A_APP,     (byte *)&pMaxq_registers->app[0],   eFOUR_BYTES);                                     
    maxq_read( AFE_B_APP,     (byte *)&pMaxq_registers->app[1],   eFOUR_BYTES);
    maxq_read( AFE_C_APP,     (byte *)&pMaxq_registers->app[2],   eFOUR_BYTES);         
    //real power
    maxq_read( AFE_PWRP_A, pMaxq_registers->pwrp_x[0], eEIGHT_BYTES);                                     
    maxq_read( AFE_PWRP_B, pMaxq_registers->pwrp_x[1], eEIGHT_BYTES);
    maxq_read( AFE_PWRP_C, pMaxq_registers->pwrp_x[2], eEIGHT_BYTES); 
    //maxq_read( AFE_PWRP_T, pMaxq_registers->pwrp_x[3], eEIGHT_BYTES);
    //apparent power
    maxq_read( AFE_PWRS_A, pMaxq_registers->pwrs_x[0], eEIGHT_BYTES);                                     
    maxq_read( AFE_PWRS_B, pMaxq_registers->pwrs_x[1], eEIGHT_BYTES);
    maxq_read( AFE_PWRS_C, pMaxq_registers->pwrs_x[2], eEIGHT_BYTES);
    //maxq_read( AFE_PWRS_T, pMaxq_registers->pwrs_x[3], eEIGHT_BYTES);      
    
    //ENERGY       
    //real positive energy
    maxq_read( AFE_A_EAPOS,     (byte *)&pMaxq_registers->eapos[0],   eFOUR_BYTES);                                     
    maxq_read( AFE_B_EAPOS,     (byte *)&pMaxq_registers->eapos[1],   eFOUR_BYTES);
    maxq_read( AFE_C_EAPOS,     (byte *)&pMaxq_registers->eapos[2],   eFOUR_BYTES);    
    //real negative energy
    maxq_read( AFE_A_EANEG,     (byte *)&pMaxq_registers->eaneg[0], eFOUR_BYTES);                                     
    maxq_read( AFE_B_EANEG,     (byte *)&pMaxq_registers->eaneg[1], eFOUR_BYTES);
    maxq_read( AFE_C_EANEG,     (byte *)&pMaxq_registers->eaneg[2], eFOUR_BYTES);        
    //activ energy
    maxq_read( AFE_ENRP_A,     (byte *)&pMaxq_registers->enrp_x[0], eEIGHT_BYTES);                                     
    maxq_read( AFE_ENRP_B,     (byte *)&pMaxq_registers->enrp_x[1], eEIGHT_BYTES);
    maxq_read( AFE_ENRP_C,     (byte *)&pMaxq_registers->enrp_x[2], eEIGHT_BYTES);    
    //maxq_read( AFE_ENRP_T,     (byte *)&pMaxq_registers->enrp_x[3], eEIGHT_BYTES);     
    //apparent energy
    maxq_read( AFE_ENRS_A,     (byte *)&pMaxq_registers->enrs_x[0], eEIGHT_BYTES);                                     
    maxq_read( AFE_ENRS_B,     (byte *)&pMaxq_registers->enrs_x[1], eEIGHT_BYTES);
    maxq_read( AFE_ENRS_C,     (byte *)&pMaxq_registers->enrs_x[2], eEIGHT_BYTES);    
    //maxq_read( AFE_ENRS_T,     (byte *)&pMaxq_registers->enrs_x[3], eEIGHT_BYTES);
                 

    /*******************************************/
    // CONVERT & RESTRICT & STORE THE VALUES
    /*******************************************/
    pMessmodul->values.frequence =  pMaxq_registers->linefr;
    pMessmodul->values.temperature =  pMaxq_registers->rawtemp / 76;                        
    
    for(i=0; i<4; i++){
        dword unsigned_value;
        signed long signed_value;                        
       
        //******************************************
        // CONVERT
        //*******************************************
        
        //VOLTAGE
        unsigned_value = (*(dword *)pMaxq_registers->v_x[i]) >> 8; 
        pMessmodul->values.voltage[i] = (unsigned_value * VOLTAGE_CONVERSION) / 100000;  
        
        //CURRENT                      
        unsigned_value = (*(dword *)pMaxq_registers->i_x[i]) >> 8;       
        pMessmodul->values.current[i] =  (unsigned_value * CURRENT_CONVERSION) / 10000;

        //POWER
        //activ power
        signed_value = buffer2signed(pMaxq_registers->pwrp_x[i], 8); 
        pMessmodul->values.power_act[i] = (signed_value * POWER_ACT_CONVERSION) / 100000;

        //apparent power        
        //signed_value = buffer2signed(pMessmodul->values.pwrs_x[i], 8) 
        //pMessmodul->values.energy[i]  = (signed_value * POWER_APP_CONVERSION) / 100000;
        
        //POWER FACTOR    
        pMessmodul->values.power_factor[i] = pMaxq_registers->pf[i];                
        
        //ENERGY
        //activ energy
        signed_value = buffer2signed(pMaxq_registers->enrp_x[i], 8); 
        pMessmodul->values.energy_act[i]  = (signed_value * ENERGY_ACT_CONVERSION) / 100000;
        
        //apparent energy
        //signed_value = buffer2signed(pMessmodul->values.enrs_x[i], 8) 
        //pMessmodul->values.energy_app[i]  = (signed_value * ENERGY_APP_CONVERSION) / 100000;
                 
        //******************************************
        // RESTRICTIONS
        //*******************************************
        
        //VOLTAGE
        if(pMessmodul->values.voltage[i] < VOLTAGE_MIN)
            pMessmodul->values.voltage[i] = 0;
            
        //CURRENT
        if(pMessmodul->values.current[i] < CURRENT_MIN)
            pMessmodul->values.current[i] = 0;
            
        //POWER
        if(pMessmodul->values.power_act[i] < POWER_ACT_MIN)
            pMessmodul->values.power_act[i] = 0;        
        if(pMessmodul->values.power_app[i] < POWER_APP_MIN)
            pMessmodul->values.power_app[i] = 0;   
            
        //ENERGY
        if(pMessmodul->values.energy_act[i] < ENERGY_ACT_MIN)
            pMessmodul->values.energy_act[i] = 0;        
        if(pMessmodul->values.energy_app[i] < ENERGY_APP_MIN)
            pMessmodul->values.energy_app[i] = 0;            
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
        printf("\nfrequence: %u.%u Hz", pMessmodul->values.frequence/1000, pMessmodul->values.frequence%1000);                                                   
        printf("\ntemperature: %d.%d°C", pMessmodul->values.temperature / 10, abs(pMessmodul->values.temperature % 10));        
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
        //printf("\nvrms: %ld",  pMessmodul->values.vrms[0]);
        //printf("\nv_x: %ld | %ld",  *(dword *)&(pMessmodul->values.v_x[0][0]), *(dword *)&(pMessmodul->values.v_x[0][4]));
        //printf("\nv_x: %x,%x,%x,%x,%x,%x,%x,%x", pMessmodul->values.v_x[0][0], pMessmodul->values.v_x[0][1], pMessmodul->values.v_x[0][2], pMessmodul->values.v_x[0][3], pMessmodul->values.v_x[0][4], pMessmodul->values.v_x[0][5], pMessmodul->values.v_x[0][6], pMessmodul->values.v_x[0][7]);
        //printf("\nv_x: %ld", buffer2signed(pMessmodul->values.v_x[0],8));        
        
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
     return  (signed int)(my_sign ? -*(long *)pBuffer : *(long *)pBuffer);   
}
