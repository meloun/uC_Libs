//**********************************************************************************************
// buttons_users.c 
// (C)2010 Knuerr s.r.o, Ing. Lubos Melichar
//**********************************************************************************************
// - aliasy a hw prirazeni portu pro 10 vstupu, pro knihovnu buttons.c
//**********************************************************************************************

#ifndef BUTTONS_USER_H_
#define BUTTONS_USER_H_


/* USER ALIASES */

/* ************************************************************************
 * Button TOP - 
 * Button BOTTOM - 
 ************************************************************************/

#define GET_BUTTON_TOP_STATE       GET_BUTTON_2_STATE
#define GET_BUTTON_BOTTOM_STATE    GET_BUTTON_1_STATE


/* END OF USER ALIASES */


/* USER DEFINES */

#ifdef HW_RMII_COMM_MODUL
    #if HW_VERSION == 100  
        #define BUTTONS_DDR        DDRD
        #define BUTTONS_PORT       PORTD
        #define BUTTONS_PIN        PIND

        //definice ledek pro dany hw
        #define BUTTON_1_DDR          BUTTONS_DDR
        #define BUTTON_1_PORT         BUTTONS_PORT  
        #define BUTTON_1_MASK         0x40
        #define GET_BUTTON_1_STATE    BUTTONS_PIN.6

        #define BUTTON_2_DDR          BUTTONS_DDR
        #define BUTTON_2_PORT         BUTTONS_PORT  
        #define BUTTON_2_MASK         0x80
        #define GET_BUTTON_2_STATE    BUTTONS_PIN.7  
          
        /* NEPOUZITE VSTUPY */
        #define GET_BUTTON_3_STATE     -1
        #define GET_BUTTON_4_STATE     -1
        #define GET_BUTTON_5_STATE     -1
        #define GET_BUTTON_6_STATE     -1
        #define GET_BUTTON_7_STATE     -1
        #define GET_BUTTON_8_STATE     -1
        #define GET_BUTTON_9_STATE     -1
        #define GET_BUTTON_10_STATE    -1
    #endif //hw_version 100  
    
    #if HW_VERSION == 110
  
        #define BUTTONS_DDR        DDRC
        #define BUTTONS_PORT       PORTC
        #define BUTTONS_PIN        PINC

        //definice ledek pro dany hw
        #define BUTTON_1_DDR          BUTTONS_DDR
        #define BUTTON_1_PORT         BUTTONS_PORT  
        #define BUTTON_1_MASK         0x40
        #define GET_BUTTON_1_STATE    BUTTONS_PIN.6

        #define BUTTON_2_DDR          BUTTONS_DDR
        #define BUTTON_2_PORT         BUTTONS_PORT  
        #define BUTTON_2_MASK         0x80
        #define GET_BUTTON_2_STATE    BUTTONS_PIN.7  
          
        /* NEPOUZITE VSTUPY */
        #define GET_BUTTON_3_STATE     -1
        #define GET_BUTTON_4_STATE     -1
        #define GET_BUTTON_5_STATE     -1
        #define GET_BUTTON_6_STATE     -1
        #define GET_BUTTON_7_STATE     -1
        #define GET_BUTTON_8_STATE     -1
        #define GET_BUTTON_9_STATE     -1
        #define GET_BUTTON_10_STATE    -1
    #endif //hw_version 110
      
#endif
/* END OF USER DEFINES */

#endif /* BUTTONS_USER_H_ */
