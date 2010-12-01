//**********************************************************************************************
// buttons.h
// (C)2010 Knuerr s.r.o, Ing. Lubos Melichar
//**********************************************************************************************
// - funkce a makra pro pro praci az s 10 vstupy
// - porty se nastavuji jako vstupni
// - kazda led muze mit rozdilny DDR, PORT a zejmena MASK(=>LED existuje)
//**********************************************************************************************

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <types.h>
#include <buttons_user.h>  

//BUTTON nr.1
#ifdef BUTTON_1_MASK
    #define BUTTON_1_INIT              BUTTON_1_DDR &= ~BUTTON_1_MASK; BUTTON_1_PORT |= BUTTON_1_MASK        
#else
    //prazdna makra
    #define BUTTON_1_INIT
#endif

//BUTTON nr.2
#ifdef BUTTON_2_MASK
    #define BUTTON_2_INIT              BUTTON_2_DDR &= ~BUTTON_2_MASK; BUTTON_2_PORT |= BUTTON_2_MASK        
#else
    //prazdna makra
    #define BUTTON_2_INIT
#endif


#define BUTTONS_INIT        BUTTON_1_INIT; BUTTON_2_INIT

//global functions
void Buttons_init(void);
signed char Buttons_get_x(byte button_position);


/* END OF LIBRARY SECTION */
#endif /* BUTTONS_H_ */
