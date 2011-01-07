//**********************************************************************************************
// digital_outputs_users.h 
// (C)2010 Knuerr s.r.o, Ing. Lubos Melichar
//**********************************************************************************************
// - aliasy a hw prirazeni portu pro 10 vystupu, pro knihovnu digital_outputs.c
// - porty se nastavuji jako vystupni
// - kazdy vystup muze mit rozdilny DDR, PORT a zejmena MASK(=>vystup existuje) a DEFAULT STATE
//**********************************************************************************************


#ifndef DIGITAL_OUTPUTS_USER_H_
#define DIGITAL_OUTPUTS_USER_H_


#include <hw_def.h>

/* USER ALIASES */

/* ************************************************************************
 * 1.output - LED YELLOW 	    -> probiha komunikace
 * 2.output - LED RED     	    -> error
 * 3.output -
 * 4.output -
 * 5.output - TRANZISTOR 1      ->
 * 6.output - TRANZISTOR 2      ->
 ************************************************************************/

/* ALIASES */ 

//communikation led
#define LED_COMM_ON      ;
#define LED_COMM_OFF     ;


// hw 1.00 => yellow
// hw 1.10 => 
#define LED_1_ON        DIG_OUT_1_ON
#define LED_1_OFF       DIG_OUT_1_OFF
#define LED_1_CHANGE    DIG_OUT_1_CHANGE

// hw 1.00 => red
// hw 1.10 => 
#define LED_2_ON          DIG_OUT_2_ON
#define LED_2_OFF         DIG_OUT_2_OFF
#define LED_2_CHANGE      DIG_OUT_2_CHANGE


#define TRANZISTOR_1_ON          DIG_OUT_5_ON
#define TRANZISTOR_1_OFF         DIG_OUT_5_OFF
#define TRANZISTOR_1_CHANGE      DIG_OUT_5_CHANGE

#define TRANZISTOR_2_ON          DIG_OUT_6_ON
#define TRANZISTOR_2_OFF         DIG_OUT_6_OFF
#define TRANZISTOR_2_CHANGE      DIG_OUT_6_CHANGE

/* END OF USER ALIASES */


/* USER PARAMETERS */
#ifdef HW_RMII_COMM_MODUL
    #if HW_VERSION == 100
 
        //port for leds
        #define LEDS_DDR        DDRC
        #define LEDS_PORT       PORTC

        //port for tranzistor outputs
        #define TRANZISTOR_DDR        DDRA
        #define TRANZISTOR_PORT       PORTA

        /* USER PORT DEFINES */        
                
        // LEDS 
          
        #define DIG_OUT_1_DDR             LEDS_DDR
        #define DIG_OUT_1_PORT            LEDS_PORT
        #define DIG_OUT_1_NR_PIN          6  
        #define DIG_OUT_1_MASK            0x40
        #define DIG_OUT_1_DEFAULT_STATE   1
          

        #define DIG_OUT_2_DDR            LEDS_DDR
        #define DIG_OUT_2_PORT           LEDS_PORT        
        #define DIG_OUT_2_NR_PIN         7
        #define DIG_OUT_2_MASK           0x80   
        #define DIG_OUT_2_DEFAULT_STATE  1 
        
        
        // TRANZISTOR OUTPUTS
        
        #define DIG_OUT_5_DDR            TRANZISTOR_DDR
        #define DIG_OUT_5_PORT           TRANZISTOR_PORT
        #define DIG_OUT_5_NR_PIN         2 
        #define DIG_OUT_5_MASK           0x04
        #define DIG_OUT_5_DEFAULT_STATE  0    
          
        #define DIG_OUT_6_DDR            TRANZISTOR_DDR
        #define DIG_OUT_6_PORT           TRANZISTOR_PORT
        #define DIG_OUT_6_NR_PIN         3 
        #define DIG_OUT_6_MASK           0x08
        #define DIG_OUT_6_DEFAULT_STATE  0
    #endif //hw_version 100   
    
    #if HW_VERSION == 110
 
        //port for leds
        #define LEDS_DDR        DDRD
        #define LEDS_PORT       PORTD

        //port for tranzistor outputs
        #define TRANZISTOR_DDR        DDRA
        #define TRANZISTOR_PORT       PORTA

        /* USER PORT DEFINES */      
        
        
        // LEDS 
          
        #define DIG_OUT_1_DDR             DDRD
        #define DIG_OUT_1_PORT            PORTD
        #define DIG_OUT_1_NR_PIN          6  
        #define DIG_OUT_1_MASK            0x40
        #define DIG_OUT_1_DEFAULT_STATE   1
          

        #define DIG_OUT_2_DDR            DDRD
        #define DIG_OUT_2_PORT           PORTD
        #define DIG_OUT_2_NR_PIN         7
        #define DIG_OUT_2_MASK           0x80     
        #define DIG_OUT_2_DEFAULT_STATE  1

        
        // TRANZISTOR OUTPUTS 
        
        #define DIG_OUT_5_DDR            TRANZISTOR_DDR
        #define DIG_OUT_5_PORT           TRANZISTOR_PORT
        #define DIG_OUT_5_NR_PIN         2 
        #define DIG_OUT_5_MASK           0x04
        #define DIG_OUT_5_DEFAULT_STATE  0    
          
        #define DIG_OUT_6_DDR            TRANZISTOR_DDR
        #define DIG_OUT_6_PORT           TRANZISTOR_PORT
        #define DIG_OUT_6_NR_PIN         3 
        #define DIG_OUT_6_MASK           0x08
        #define DIG_OUT_6_DEFAULT_STATE  0
    #endif
#endif //RMII

/* END OF USER DEFINES */

#endif /* DIGITAL_OUTPUTS_USER_H_ */
