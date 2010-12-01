//**********************************************************************************************
// display.h
// (C)2010 Knuerr s.r.o, Ing. Lubos Melichar
//**********************************************************************************************

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <types.h>
#include <display.h>
#include "display_screens.h"

typedef struct{
    byte screen_index;
    //pDISPLAY_SCREEN_FUNCTION current_screen_function;
    //byte rows_text[NR_ROWS][40];
    //byte* pRows[NR_ROWS];        
    byte first_enter;
    byte inactive_cnt;
    byte screensaver_flag;
}tDISPLAY;

void Display_Init();
void Display_Manager();
void Disp_next_screen();
void Disp_previous_screen();
  
#endif /* DISPLAY_H_ */
