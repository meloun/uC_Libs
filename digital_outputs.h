//**********************************************************************************************
// digital_outputs.h
// (C)2010 Knuerr s.r.o, Ing. Lubos Melichar
//**********************************************************************************************
// - funkce a makra pro pro praci az s 10 vystupy
// - porty se nastavuji jako vystupni
// - kazdy vystup muze mit rozdilny DDR, PORT a zejmena MASK(=>LED existuje) a DEFAULT STATE
//**********************************************************************************************

#ifndef DIGITAL_OUTPUTS_H_
#define DIGITAL_OUTPUTS_H_

#include <hw_def.h>
#include <digital_outputs_user.h>  

//DIGITAL OUTPUT nr.1
#ifdef DIG_OUT_1_MASK   
    //#define DIG_OUT_1_INIT				DIG_OUT_1_DDR |= DIG_OUT_1_MASK; DIG_OUT_1_PORT |= DIG_OUT_1_MASK
    #define DIG_OUT_1_INIT				DIG_OUT_1_DDR |= DIG_OUT_1_MASK; DIG_OUT_1_PORT.DIG_OUT_1_NR_PIN = DIG_OUT_1_DEFAULT_STATE 
    #define DIG_OUT_1_OFF				(DIG_OUT_1_PORT &= ~DIG_OUT_1_MASK)
    #define DIG_OUT_1_ON    			(DIG_OUT_1_PORT |= DIG_OUT_1_MASK)
    #define DIG_OUT_1_CHANGE			(DIG_OUT_1_PORT ^= DIG_OUT_1_MASK)
#else
    //prazdna makra 
    #define DIG_OUT_1_INIT
    #define DIG_OUT_1_ON
    #define DIG_OUT_1_OFF
    #define DIG_OUT_1_CHANGE
#endif

//DIGITAL OUTPUT nr.2
#ifdef DIG_OUT_2_MASK
    #define DIG_OUT_2_INIT				DIG_OUT_2_DDR |= DIG_OUT_2_MASK; DIG_OUT_2_PORT.DIG_OUT_2_NR_PIN = DIG_OUT_2_DEFAULT_STATE 
    #define DIG_OUT_2_OFF				(DIG_OUT_2_PORT &= ~DIG_OUT_2_MASK)
    #define DIG_OUT_2_ON				(DIG_OUT_2_PORT |= DIG_OUT_2_MASK)
    #define DIG_OUT_2_CHANGE			(DIG_OUT_2_PORT ^= DIG_OUT_2_MASK)
#else
    //prazdna makra
    #define DIG_OUT_2_INIT
    #define DIG_OUT_2_ON
    #define DIG_OUT_2_OFF
    #define DIG_OUT_2_CHANGE
#endif

//DIGITAL OUTPUT nr.3
#ifdef DIG_OUT_3_MASK
    #define DIG_OUT_3_INIT				DIG_OUT_3_DDR |= DIG_OUT_3_MASK; DIG_OUT_3_PORT.DIG_OUT_3_NR_PIN = DIG_OUT_3_DEFAULT_STATE
    #define DIG_OUT_3_OFF				(DIG_OUT_3_PORT &= ~DIG_OUT_3_MASK)
    #define DIG_OUT_3_ON				(DIG_OUT_3_PORT |= DIG_OUT_3_MASK)
    #define DIG_OUT_3_CHANGE			(DIG_OUT_3_PORT ^= DIG_OUT_3_MASK)
#else
    //prazdna makra
    #define DIG_OUT_3_INIT
    #define DIG_OUT_3_ON
    #define DIG_OUT_3_OFF
    #define DIG_OUT_3_CHANGE
#endif

//DIGITAL OUTPUT nr.4
#ifdef DIG_OUT_4_MASK
    #define DIG_OUT_4_INIT				DIG_OUT_4_DDR |= DIG_OUT_4_MASK; DIG_OUT_4_PORT.DIG_OUT_4_NR_PIN = DIG_OUT_4_DEFAULT_STATE
    #define DIG_OUT_4_OFF				(DIG_OUT_4_PORT &= ~DIG_OUT_4_MASK)
    #define DIG_OUT_4_ON				(DIG_OUT_4_PORT |= DIG_OUT_4_MASK)
    #define DIG_OUT_4_CHANGE			(DIG_OUT_4_PORT ^= DIG_OUT_4_MASK)
#else
    //prazdna makra
    #define DIG_OUT_4_INIT
    #define DIG_OUT_4_ON
    #define DIG_OUT_4_OFF
    #define DIG_OUT_4_CHANGE
#endif

//DIGITAL OUTPUT nr.5
#ifdef DIG_OUT_5_MASK
    #define DIG_OUT_5_INIT				DIG_OUT_5_DDR |= DIG_OUT_5_MASK; DIG_OUT_5_PORT.DIG_OUT_5_NR_PIN = DIG_OUT_5_DEFAULT_STATE
    //#define DIG_OUT_5_INIT				DIG_OUT_5_DDR |= DIG_OUT_5_MASK; DIG_OUT_5_PORT |= DIG_OUT_5_MASK 
    #define DIG_OUT_5_OFF				(DIG_OUT_5_PORT &= ~DIG_OUT_5_MASK)
    #define DIG_OUT_5_ON				(DIG_OUT_5_PORT |= DIG_OUT_5_MASK)
    #define DIG_OUT_5_CHANGE			(DIG_OUT_5_PORT ^= DIG_OUT_5_MASK)
#else
    //prazdna makra
    #define DIG_OUT_5_INIT
    #define DIG_OUT_5_ON
    #define DIG_OUT_5_OFF
    #define DIG_OUT_5_CHANGE
#endif

//LED c.6
#ifdef DIG_OUT_6_MASK
    #define DIG_OUT_6_INIT				DIG_OUT_6_DDR |= DIG_OUT_6_MASK; DIG_OUT_6_PORT.DIG_OUT_6_NR_PIN = DIG_OUT_6_DEFAULT_STATE
    //#define DIG_OUT_6_INIT				DIG_OUT_6_DDR |= DIG_OUT_6_MASK; DIG_OUT_6_PORT |= DIG_OUT_6_MASK 
    #define DIG_OUT_6_OFF				(DIG_OUT_6_PORT &= ~DIG_OUT_6_MASK)
    #define DIG_OUT_6_ON				(DIG_OUT_6_PORT |= DIG_OUT_6_MASK)
    #define DIG_OUT_6_CHANGE			(DIG_OUT_6_PORT ^= DIG_OUT_6_MASK)
#else
    //prazdna makra
    #define DIG_OUT_6_INIT
    #define DIG_OUT_6_ON
    #define DIG_OUT_6_OFF
    #define DIG_OUT_6_CHANGE
#endif

//LED c.7
#ifdef DIG_OUT_7_MASK
    #define DIG_OUT_7_INIT				DIG_OUT_7_DDR |= DIG_OUT_7_MASK; DIG_OUT_7_PORT.DIG_OUT_7_NR_PIN = DIG_OUT_7_DEFAULT_STATE
    #define DIG_OUT_7_OFF				(DIG_OUT_7_PORT &= ~DIG_OUT_7_MASK)
    #define DIG_OUT_7_ON				(DIG_OUT_7_PORT |= DIG_OUT_7_MASK)
    #define DIG_OUT_7_CHANGE			(DIG_OUT_7_PORT ^= DIG_OUT_7_MASK)
#else
    //prazdna makra
    #define DIG_OUT_7_INIT
    #define DIG_OUT_7_ON
    #define DIG_OUT_7_OFF
    #define DIG_OUT_7_CHANGE
#endif

//LED c.8
#ifdef DIG_OUT_8_MASK
    #define DIG_OUT_8_INIT				DIG_OUT_8_DDR |= DIG_OUT_8_MASK; DIG_OUT_8_PORT.DIG_OUT_8_NR_PIN = DIG_OUT_8_DEFAULT_STATE
    #define DIG_OUT_8_OFF				(DIG_OUT_8_PORT &= ~DIG_OUT_8_MASK)
    #define DIG_OUT_8_ON				(DIG_OUT_8_PORT |= DIG_OUT_8_MASK)
    #define DIG_OUT_8_CHANGE			(DIG_OUT_8_PORT ^= DIG_OUT_8_MASK)
#else
    //prazdna makra
    #define DIG_OUT_8_INIT
    #define DIG_OUT_8_ON
    #define DIG_OUT_8_OFF
    #define DIG_OUT_8_CHANGE
#endif

//LED c.9
#ifdef DIG_OUT_9_MASK
    #define DIG_OUT_9_INIT				DIG_OUT_9_DDR |= DIG_OUT_9_MASK; DIG_OUT_9_PORT.DIG_OUT_9_NR_PIN = DIG_OUT_9_DEFAULT_STATE
    #define DIG_OUT_9_OFF				(DIG_OUT_9_PORT &= ~DIG_OUT_9_MASK)
    #define DIG_OUT_9_ON				(DIG_OUT_9_PORT |= DIG_OUT_9_MASK)
    #define DIG_OUT_9_CHANGE			(DIG_OUT_9_PORT ^= DIG_OUT_9_MASK)
#else
    //prazdna makra
    #define DIG_OUT_9_INIT
    #define DIG_OUT_9_ON
    #define DIG_OUT_9_OFF
    #define DIG_OUT_9_CHANGE
#endif

//LED c.10
#ifdef DIG_OUT_10_MASK
    #define DIG_OUT_10_INIT				DIG_OUT_10_DDR |= DIG_OUT_10_MASK; DIG_OUT_10_PORT.DIG_OUT_10_NR_PIN = DIG_OUT_10_DEFAULT_STATE
    #define DIG_OUT_10_OFF				(DIG_OUT_10_PORT &= ~DIG_OUT_10_MASK)
    #define DIG_OUT_10_ON				(DIG_OUT_10_PORT |= DIG_OUT_10_MASK)
    #define DIG_OUT_10_CHANGE			(DIG_OUT_10_PORT ^= DIG_OUT_10_MASK)
#else
    //prazdna makra
    #define DIG_OUT_10_INIT
    #define DIG_OUT_10_ON
    #define DIG_OUT_10_OFF
    #define DIG_OUT_10_CHANGE        
#endif

#define DIG_OUTS_INIT		DIG_OUT_1_INIT;DIG_OUT_2_INIT; DIG_OUT_3_INIT; DIG_OUT_4_INIT; DIG_OUT_5_INIT; DIG_OUT_6_INIT; DIG_OUT_7_INIT; DIG_OUT_8_INIT; DIG_OUT_9_INIT; DIG_OUT_10_INIT

//global functions
void Digital_outputs_init(void);
void Digital_outputs_x_on(byte output_position);
void Digital_outputs_x_off(byte output_position);
void Digital_outputs_set(word mask);

/* END OF LIBRARY SECTION */
#endif /* DIGITAL_OUTPUTS_H_ */
