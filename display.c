//**********************************************************************************************
// display.c 
// (C)2010 Knuerr s.r.o, Ing. Lubos Melichar
//**********************************************************************************************
// Display_Manager()
// - bere obrazovky z display_screens.c a zobrazuje je na display
//**********************************************************************************************

#include <hw_def.h>
#include <types.h>
#include <stdio.h>

#include <NT7534.h>
#include <display.h>
#include <utils.h>
#include "display_screens.h"

tDISPLAY sDisplay;

void rot_inc(byte *var, byte max);
void rot_dec(byte *var, byte max);
void Disp_next_screen();
void Disp_previous_screen();

void Display_Init(){
    
//    for(i=0; i<NR_ROWS; i++)
//        sDisplay.pRows[i] = sDisplay.rows_text[i];
    
    sDisplay.screen_index = 0;      
    //sDisplay.current_screen_function = sSCREEN_GROUP[0].function;
    
    
    //init display    
    NT7534_Init();


}

void Display_Manager(){    
    byte* pRows[NR_ROWS] = {    "                      ", //21
                                "                      ",
                                "                      ",
                                "                      ",
                                "                      ",
                                "                      ",
                                "                      ",                                            
                                "                      "};             
    
//    sprintf(sDisplay.rows_text[0], "nulovy");
//    sprintf(sDisplay.rows_text[1], "prvy");
//    sprintf(sDisplay.rows_text[2], "treti");
//    sprintf(sDisplay.rows_text[3], "ctvrty"); 
    
    //sDisplay.current_screen_function(sDisplay.pRows);
    
    //sSCREEN_GROUP[sDisplay.screen_index].function(pRows);
    
    //funkce z indexu naplni stringy
    Display_screens_setStrings(sDisplay.screen_index, pRows);
    
    //incrementy screen
    //Disp_next_screen();
    //rot_inc(&sDisplay.screen_index, NR_SCREEN-1);
    
    //set screen    
    NT7534_set_screen(pRows);
    //NT7534_set_paging(sDisplay.screen_index+1, NR_SCREEN);
        
//    printf("\n screen");
//    for(i=0; i<NR_ROWS; i++){
//        printf("%s", sDisplay.rows_text[i]);        
//    }   

}


void Disp_next_screen(){        
    rot_inc(&sDisplay.screen_index, NR_SCREEN-1);    
}

void Disp_previous_screen(){        
    rot_dec(&sDisplay.screen_index, NR_SCREEN-1);    
}



