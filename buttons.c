//**********************************************************************************************
// buttons.c 
// (C)2010 Knuerr s.r.o, Ing. Lubos Melichar
//**********************************************************************************************
// - funkce a makra pro praci az s 10 vstupy
// - porty se nastavuji jako vstupni s pullupy
// - kazdy vstup muze mit rozdilny DDR, PORT a zejmena MASK(=>LED existuje)
//**********************************************************************************************

#include <hw_def.h>
#include <types.h>
#include <buttons.h>


//*****************************************************************
// Buttons_init - init portu
//*****************************************************************
void Buttons_init(void){
    BUTTONS_INIT;
}


//*****************************************************************
// Buttons_get_x - vrati stav X-teho tlacitka
//*****************************************************************
signed char Buttons_get_x(byte button_position){
    signed char aux_button = -1;

    switch (button_position) {
        case 1 : aux_button = GET_BUTTON_1_STATE; break;
        case 2 : aux_button = GET_BUTTON_2_STATE; break;
        case 3 : aux_button = GET_BUTTON_3_STATE; break;
        case 4 : aux_button = GET_BUTTON_4_STATE; break;
        case 5 : aux_button = GET_BUTTON_5_STATE; break;
        case 6 : aux_button = GET_BUTTON_6_STATE; break;
        case 7 : aux_button = GET_BUTTON_7_STATE; break;
        case 8 : aux_button = GET_BUTTON_8_STATE; break;
        case 9 : aux_button = GET_BUTTON_9_STATE; break;
        case 10 : aux_button = GET_BUTTON_10_STATE; break;
        default: aux_button = -1; break;
  }
  return aux_button;
}

/* END OF SPI FUNCTIONS */