//**********************************************************************************************
//
//*****************************************************************

#include <types.h>
#include <stdio.h>
#include <utils.h>

//rotacni incrementace, mozna udelat jako makro
void rot_inc(byte *var, byte max){
	if(*var < max)
		(*var)++;
	else
		*var = 0;
}

//rotacni incrementace, mozna udelat jako makro
void rot_dec(byte *var, byte max){
	if(*var == 0)
        *var = max;		
	else
        (*var)--;		
}