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


signed long buffer2signed(byte *pBuffer, byte length);
byte Messmodul_countAvailable();

//MESSMODULES structure
tMESSMODULES  sMm; 

void Messmodul_Init(){          
    
    //init max, spi etc.
    maxq_Init();    

    //reset all values of all messmodules    
    memset(&sMm, 0, sizeof(sMm)); 

    //CS AS OUTPUT
    SPI_INIT_ALL_CS    
    MESSMODULE_DESELECT
 
}

/*******************************************/
// MESSMODUL_SPI()
/*******************************************/
// receive values of registers to temporarily structure
// calibrate to electrical quantity, restrict
// and save to permanent structure 
/*******************************************/
void Messmodule_spi(byte nr_module){
    byte i;    
    
    //REGISTER Sturcture, temporarily
    tMAXQ_REGISTERS sMaxq_registers;
    tMAXQ_REGISTERS *pMaxq_registers = &sMaxq_registers;
 
    //ELECTRICAL QUANTITY, pointer to global structure          
    tMESSMODULE *pModule = &sMm.sModule[nr_module];
    
    //reset register structure
    memset(&sMaxq_registers, 0, sizeof(tMAXQ_REGISTERS));                   
    
    /*******************************************/
    // GET VALUES FROM MAXIM
    /*******************************************/                                  
   
    //1F values
    //read first values and get availibility(status)
    pModule->status = maxq_read( AFE_LINEFR,      (byte *)&pMaxq_registers->linefr,  eTWO_BYTES);
    
    printf("w:%d",pModule->status);
    
     
    //module not availible -> exit
    if(pModule->status == -1){
        //sMm.rest_flag = 1; 
        return;
    }                        
            
    //RAWTEMP
    maxq_read( AFE_RAWTEMP,     (byte *)&(pMaxq_registers->rawtemp), eTWO_BYTES);
     
    
    
       
        
    //V.X
    maxq_read( AFE_V_A, pMaxq_registers->v_x[0], eEIGHT_BYTES);                                     
    maxq_read( AFE_V_B, pMaxq_registers->v_x[1], eEIGHT_BYTES);
    maxq_read( AFE_V_C, pMaxq_registers->v_x[2], eEIGHT_BYTES);    
           
    //I.X
    maxq_read( AFE_I_A, pMaxq_registers->i_x[0], eEIGHT_BYTES);                                     
    maxq_read( AFE_I_B, pMaxq_registers->i_x[1], eEIGHT_BYTES);
    maxq_read( AFE_I_C, pMaxq_registers->i_x[2], eEIGHT_BYTES);    
    //maxq_read( AFE_I_N, pMaxq_registers->i_x[3], eEIGHT_BYTES);
    
    //POWER FACTOR
    maxq_read( AFE_A_PF,        (byte *)&pMaxq_registers->pf[0],      eTWO_BYTES);                                     
    maxq_read( AFE_B_PF,        (byte *)&pMaxq_registers->pf[1],      eTWO_BYTES);   
    maxq_read( AFE_C_PF,        (byte *)&pMaxq_registers->pf[2],      eTWO_BYTES);     
    
    //POWER        
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
    
    
    //POWER - real registers
    //active power
    //maxq_read( AFE_A_ACT,     (byte *)&pMaxq_registers->act[0],   eFOUR_BYTES);                                     
    //maxq_read( AFE_B_ACT,     (byte *)&pMaxq_registers->act[1],   eFOUR_BYTES);
    //maxq_read( AFE_C_ACT,     (byte *)&pMaxq_registers->act[2],   eFOUR_BYTES);         
    //apparent power
    //maxq_read( AFE_A_APP,     (byte *)&pMaxq_registers->app[0],   eFOUR_BYTES);                                     
    //maxq_read( AFE_B_APP,     (byte *)&pMaxq_registers->app[1],   eFOUR_BYTES);
    //maxq_read( AFE_C_APP,     (byte *)&pMaxq_registers->app[2],   eFOUR_BYTES); 
    
    //ENERGY - real registers
    //real positive energy
    //maxq_read( AFE_A_EAPOS,     (byte *)&pMaxq_registers->eapos[0],   eFOUR_BYTES);                                     
    //maxq_read( AFE_B_EAPOS,     (byte *)&pMaxq_registers->eapos[1],   eFOUR_BYTES);
    //maxq_read( AFE_C_EAPOS,     (byte *)&pMaxq_registers->eapos[2],   eFOUR_BYTES);    
    //real negative energy
    //maxq_read( AFE_A_EANEG,     (byte *)&pMaxq_registers->eaneg[0], eFOUR_BYTES);                                     
    //maxq_read( AFE_B_EANEG,     (byte *)&pMaxq_registers->eaneg[1], eFOUR_BYTES);
    //maxq_read( AFE_C_EANEG,     (byte *)&pMaxq_registers->eaneg[2], eFOUR_BYTES);    
                 

    /*******************************************/
    // CONVERT & RESTRICT & STORE THE VALUES
    /*******************************************/
    pModule->values.frequence =  pMaxq_registers->linefr;
    pModule->values.temperature =  pMaxq_registers->rawtemp / 76;                        
    
    //pres vsechny 3faze a nulak/total
    for(i=0; i<4; i++){
        dword unsigned_value;
        signed long signed_value; 
                
        
        #ifdef MM_CALIBRATION_MODE
            //these register have to be saved only for calibration
            pModule->registers.v_x[i] =  (* (dword *) pMaxq_registers->v_x[i]) >> 8;
            pModule->registers.i_x[i] =  (* (dword *) pMaxq_registers->i_x[i]) >> 8;
            pModule->registers.pwrp_x[i] =  buffer2signed(pMaxq_registers->pwrp_x[i], 8);
            pModule->registers.pwrs_x[i] =  buffer2signed(pMaxq_registers->pwrs_x[i], 8);  
            pModule->registers.enrp_x[i] =  buffer2signed(pMaxq_registers->enrp_x[i], 8)>>8;
            pModule->registers.enrs_x[i] =  buffer2signed(pMaxq_registers->enrs_x[i], 8)>>8; 
            pModule->registers.pf_x[i] = pMaxq_registers->pf[i];                
        #endif                       
       
        //******************************************
        // CONVERT
        //*******************************************
                
        //VOLTAGE
        unsigned_value = (*(dword *)pMaxq_registers->v_x[i]) >> 8; 
        pModule->values.voltage[i] = (unsigned_value * VOLTAGE_CONVERSION) / 10000;  
            
        //CURRENT                      
        unsigned_value = (*(dword *)pMaxq_registers->i_x[i]) >> 8;       
        pModule->values.current[i] =  (unsigned_value * CURRENT_CONVERSION) / 10000;

        //POWER
        //activ power
        signed_value = buffer2signed(pMaxq_registers->pwrp_x[i], 8); 
        pModule->values.power_act[i] = (signed_value * POWER_ACT_CONVERSION) / 100000;

        //apparent power        
        //signed_value = buffer2signed(pModule->values.pwrs_x[i], 8) 
        //pModule->values.energy[i]  = (signed_value * POWER_APP_CONVERSION) / 100000;
            
        //POWER FACTOR    
        pModule->values.power_factor[i] = pMaxq_registers->pf[i];                
            
        //ENERGY
        //activ energy
        signed_value = buffer2signed(pMaxq_registers->enrp_x[i], 8); 
        pModule->values.energy_act[i]  = (signed_value * ENERGY_ACT_CONVERSION) / 100000;            
        
        //apparent energy
        //signed_value = buffer2signed(pModule->values.enrs_x[i], 8) 
        //pModule->values.energy_app[i]  = (signed_value * ENERGY_APP_CONVERSION) / 100000;
                 
        //******************************************
        // RESTRICTIONS
        //*******************************************       
        
        //VOLTAGE
        if(pModule->values.voltage[i] < VOLTAGE_MIN)
            pModule->values.voltage[i] = 0;
                
        //CURRENT
        if(pModule->values.current[i] < CURRENT_MIN)
            pModule->values.current[i] = 0;
                
        //POWER
        if(pModule->values.power_act[i] < POWER_ACT_MIN)
            pModule->values.power_act[i] = 0;        
        if(pModule->values.power_app[i] < POWER_APP_MIN)
            pModule->values.power_app[i] = 0;   
                
        //ENERGY
        if(pModule->values.energy_act[i] < ENERGY_ACT_MIN)
            pModule->values.energy_act[i] = 0;        
        if(pModule->values.energy_app[i] < ENERGY_APP_MIN)
            pModule->values.energy_app[i] = 0;          
    }
    
    sMm.rest_flag = 1;                           
}

/*******************************************/
// MESSMODUL_MANAGER()
/*******************************************/
// process function
/*******************************************/
void Messmodul_Manager(){
    
    //next module
    sMm.nr_current_module++;
    
    //NEW ROUND, set first messmodule    
    if(sMm.nr_current_module == NR_MESSMODULES){
            
        //set first module   
        sMm.nr_current_module = 0;                 
        
        //nr of available modules
        sMm.nr_available_modules = Messmodul_countAvailable(); 
        //printf("ca:%d",Messmodul_countAvailable());
        
    }                                          
          
    printf("\n%d - ",sMm.nr_current_module);
    //printf("\na:%d; %d,%d,%d,%d",Messmodul_countAvailable(),sMm.sModule[0].status, sMm.sModule[1].status, sMm.sModule[2].status, sMm.sModule[3].status);
    
    
    //set CS           
    MESSMODULE_DESELECT 
    delay_us(100); 
    MESSMODULE_SELECT(sMm.nr_current_module)
    
    delay_us(100);    
    //MESSMODULE_SELECT(0)
     
    SET_SPI_SPEED_128   
    
    //PORTB.3 = 0;
        
    
    //receive, convert and store data from module
    Messmodule_spi(sMm.nr_current_module);  
    
    //PORTB.3 = 1;
    
    //clear CS
    
          
}


/*******************************************/
// MESSMODUL_REST()
/*******************************************/
// "while fuction", print debug messages
/*******************************************/
void Messmodul_Rest(){
         
    if(sMm.rest_flag){
        tMESSMODULE *pModule = &sMm.sModule[sMm.nr_current_module];        
        //print values
        printf("\n============");
        printf("\nmessmodul nr.%u", sMm.nr_current_module+1);
        printf("\n============");
        //printf("\nfrequence: %u.%u Hz", pModule->values.frequence/1000, pModule->values.frequence%1000);                                                   
        printf("\ntemperature: %d.%d°C", pModule->values.temperature / 10, abs(pModule->values.temperature % 10));
                
        //printf("\ncurrent: %ld | %ld | %ld",  pModule->values.current[0], pModule->values.current[1], pModule->values.current[2]);
        //printf("\nvoltage: %ld | %ld | %ld",  pModule->values.voltage[0], pModule->values.voltage[1], pModule->values.voltage[2]);
        printf("\npf: %ld | %ld | %ld",  pModule->values.power_factor[0], pModule->values.power_factor[1], pModule->values.power_factor[2]);
                    
        //printf("\nCC: volt:%d, amp:%d", pModule->values.volt_cc, pModule->values.amp_cc);
        //printf("\nPF: %d, %d, %d", pModule->values.pf[0], pModule->values.pf[1], pModule->values.pf[2]);
        //printf("\nPF: %ld, %ld, %ld", pModule->values.pf[0], pModule->values.pf[1], pModule->values.pf[2]);
        //printf("\nVRMS: 0x%lx, 0x%lx, 0x%lx", pModule->values.vrms[0], pModule->values.vrms[1], pModule->values.vrms[2]);
        //printf("\nIRMS: 0x%lx, 0x%lx, 0x%lx", pModule->values.irms[0], pModule->values.irms[1], pModule->values.irms[2]);
        //printf("\nACT: %ld, %ld, %ld", pModule->values.act[0], pModule->values.act[1], pModule->values.act[2]);
        //printf("\nACT: %x, %x, %x", pModule->values.act[0], pModule->values.act[1], pModule->values.act[2]);    
        //printf("\nACT: %lx, %lx, %lx", pModule->values.act[0], pModule->values.act[1], pModule->values.act[2]);
        //printf("\nACT: %ld, %ld, %ld", pModule->values.act[0], pModule->values.act[1], pModule->values.act[2]);
        //printf("\nEAPOS: %lx, %lx, %lx", pModule->values.eapos[0], pModule->values.eapos[1], pModule->values.eapos[2]);
        //printf("\nEANEG: %lx, %lx, %lx", pModule->values.eaneg[0], pModule->values.eaneg[1], pModule->values.eaneg[2]);
        //printf("\nvoltage: %u, %u, %u", pModule->values.voltage[0], pModule->values.voltage[1], pModule->values.voltage[2]);
        //printf("\npwrp: 0x%ld, 0x%ld | 0x%ld,  0x%ld | 0x%ld,  0x%ld",  *(dword *)pModule->values.pwrp_x[0], *((dword *)pModule->values.pwrp_x[0]+1), *(dword *)pModule->values.pwrp_x[1], *((dword *)pModule->values.pwrp_x[1]+1), *(dword *)pModule->values.pwrp_x[2], *((dword *)pModule->values.pwrp_x[2]+1));        
        //printf("\nvrms: %ld | %ld | %ld",  pModule->values.vrms[0],  pModule->values.vrms[1], pModule->values.vrms[2]);
        //printf("\nirms: %ld | %ld | %ld",  pModule->values.irms[0],  pModule->values.irms[1], pModule->values.irms[2]);    
        //printf("\nvrms: %ld",  pModule->values.vrms[0]);
        //printf("\nv_x: %ld | %ld",  *(dword *)&(pModule->values.v_x[0][0]), *(dword *)&(pModule->values.v_x[0][4]));
        //printf("\nv_x: %x,%x,%x,%x,%x,%x,%x,%x", pModule->values.v_x[0][0], pModule->values.v_x[0][1], pModule->values.v_x[0][2], pModule->values.v_x[0][3], pModule->values.v_x[0][4], pModule->values.v_x[0][5], pModule->values.v_x[0][6], pModule->values.v_x[0][7]);
        //printf("\nv_x: %ld", buffer2signed(pModule->values.v_x[0],8));                        
        //printf("\ncurrent A: 0x%ld, 0x%ld | 0x%ld,  0x%lx | 0x%lx,  0x%lx", *(dword *)pModule->values.current[0], *((dword *)pModule->values.current[0]+1),*(dword *)pModule->values.current[1], *((dword *)pModule->values.current[1]+1),*(dword *)pModule->values.current[2], *((dword *)pModule->values.current[2]+1));
        
        sMm.rest_flag = 0;
    }                            
}

//GET COUNT OF AVAILABLE MODULES
byte Messmodul_countAvailable(){
    byte i, aux_nr = 0;

    //check available modules
    for(i=0; i<NR_MESSMODULES;i++)      //over all modules
        if(sMm.sModule[i].status != -1) //available? (variable status is managed in Messmodul_spi())
            aux_nr++;
    
    return aux_nr;
}

//GET COUNT OF AVAILABLE VOLTAGES FOR MESSMODUL
byte Messmodul_getCountVoltage(byte nr_messmodul){
    byte i,aux_count = 0;  
    tMESSMODULE *pModule = &sMm.sModule[nr_messmodul];
    
    for(i=0; i<3; i++)
        if(pModule->values.voltage[i])
            aux_count++;
        
    return aux_count;
}

//GET COUNT OF AVAILABLE CURRENTS FOR MESSMODUL
byte Messmodul_getCountCurrent(byte nr_messmodul){
    byte i,aux_count = 0;
    tMESSMODULE *pModule = &sMm.sModule[nr_messmodul];
    
    for(i=0; i<3; i++)
        if(pModule->values.current[i])
            aux_count++;
            
    return aux_count;
}

//bit 63 is the sign
//otherwise 4 most significat bytes are zero
signed long buffer2signed(byte *pBuffer, byte length){

     //most significant bit is the sign 
     byte my_sign = *(pBuffer + (length-1)) & 0x80 ? 1 : 0;
     return  (signed long)(my_sign ? -*(unsigned long *)pBuffer : *(unsigned long *)pBuffer);   
}
