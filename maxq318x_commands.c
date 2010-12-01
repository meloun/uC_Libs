//**********************************************************************************************
// maxq318x.c - 
// (C)2010 Knuerr s.r.o., Ing. Lubos Melichar
//**********************************************************************************************

#include <hw_def.h>
#include <stdio.h>
#include <my_spi.h>
#include <delay.h>
#include <uart2.h>
#include <maxq318x_commands.h>

/* COMMAND TABLES */

    
// | command | size |
flash tCOMMAND_DEF COMMAND_DEF[] = {
    {AFE_STATUS,    1,  eAFE_READ}, //eSTATUS
    {AFE_OP_MODE1,  1,  eAFE_READ},  //eOP_MODE1    
    {AFE_OP_MODE2,  1,  eAFE_READ},  //eOP_MODE2
    {AFE_OP_MODE3,  1,  eAFE_READ},  //eOP_MODE3
    {AFE_IRQ_FLAG,  2,  eAFE_READ},  //eIRQ_FLAG
    {AFE_IRQ_MASK,  2,  eAFE_READ},  //eIRQ_MASK
    {AFE_LINEFR,    2,  eAFE_READ},  //eLINEFR   
    {AFE_A_PF,      2,  eAFE_READ},  //eA_PF
    {AFE_A_VRMS,    4,  eAFE_READ},  //eA_VRMS
    {AFE_A_IRMS,    4,  eAFE_READ},  //eA_IRMS
    {AFE_B_PF,      2,  eAFE_READ},  //eB_PF
    {AFE_B_VRMS,    4,  eAFE_READ},  //eB_VRMS
    {AFE_B_IRMS,    4,  eAFE_READ},  //eB_IRMS
    {AFE_C_PF,      2,  eAFE_READ},  //eC_PF
    {AFE_C_VRMS,    4,  eAFE_READ},  //eC_VRMS
    {AFE_C_IRMS,    4,  eAFE_READ},  //eC_IRMS
    {AFE_RAWTEMP,   2,  eAFE_READ}   //eRAWTEMP
    
};
