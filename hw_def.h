/*
 * hw_def.h
 *
 *  Created on: 28.8.2009
 *      Author: Lubos Melichar
 */

#ifndef _hw_def_h
#define _hw_def_h

/** DEFINOVANO V PROJEKTU ** PROJECT/PRJ_DEF_HW.H **    **/
#include "project/prj_def.h"

//*************************************************************************************
// Include knihoven pro ATmega podle typu pouziteho hardwaru
//*************************************************************************************

#ifdef HW_RMII_COMM_MODUL
  #include <mega324a.h>
  #include <mega324_bits.h>
  
  //general
  #define RXCIE	RXCIE0
  #define TXCIE	TXCIE0
  #define UDRIE	UDRIE0
  #define RXEN	RXEN0
  #define TXEN	TXEN0
  #define CHR9	CHR90
  #define RXB8	RXB80
  #define TXB8	TXB80
  #define UDRE	UDRE0      	
#endif

#include <types.h>
#include <system.h>


#endif
