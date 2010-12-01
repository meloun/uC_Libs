//**********************************************************************************************
// digital_outputs.c 
// (C)2010 Knuerr s.r.o, Ing. Lubos Melichar
//**********************************************************************************************
// - funkce a makra pro praci az s 10 vystupy
// - porty se nastavuji jako vystupni s definovanou defaultni hodnotou
// - kazdy vystupu muze mit rozdilny DDR, PORT a zejmena MASK(=>OUTPUT existuje)
//**********************************************************************************************

#include <types.h>
#include <digital_outputs.h>


//*****************************************************************
// Leds_init - init portu
//*****************************************************************
void Digital_outputs_init(void){
	DIG_OUTS_INIT;
}


//*****************************************************************
// Leds_x_on - rozsviti urcenou LED diodu
//*****************************************************************
void Digital_outputs_x_on(byte output_position)
{
    switch (output_position) {
        case 1 : DIG_OUT_1_ON; break;
        case 2 : DIG_OUT_2_ON; break;
        case 3 : DIG_OUT_3_ON; break;
        case 4 : DIG_OUT_4_ON; break;
        case 5 : DIG_OUT_5_ON; break;
        case 6 : DIG_OUT_6_ON; break;
        case 7 : DIG_OUT_7_ON; break;
        case 8 : DIG_OUT_8_ON; break;
        case 9 : DIG_OUT_9_ON; break;
        case 10 : DIG_OUT_10_ON; break;
        default: break;
  }
}


//*****************************************************************
// Leds_X_Off - zhasne urcenou LED diodu
//*****************************************************************
void Digital_outputs_x_off(byte output_position)
{
	switch (output_position) {
        case 1 : DIG_OUT_1_OFF; break;
        case 2 : DIG_OUT_2_OFF; break;
        case 3 : DIG_OUT_3_OFF; break;
        case 4 : DIG_OUT_4_OFF; break;
        case 5 : DIG_OUT_5_OFF; break;
        case 6 : DIG_OUT_6_OFF; break;
        case 7 : DIG_OUT_7_OFF; break;
        case 8 : DIG_OUT_8_OFF; break;
        case 9 : DIG_OUT_9_OFF; break;
        case 10 : DIG_OUT_10_OFF; break;
        default: break;
  }
}


//*****************************************************************
// Leds_set - rozsviti/zhasne ledky podle zadane masky
//*****************************************************************
void Digital_outputs_set(word mask){
	byte i;
	for(i=0;i<16;i++){
		if((mask >> i) & 0x01)
			Digital_outputs_x_on(i+1);
		else
			Digital_outputs_x_off(i+1);
	}
}

