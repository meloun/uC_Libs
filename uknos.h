//*****************************************************************************
// Ing. Lubos Melichar, 08/2010
// uKnos.h - header module
//*****************************************************************************

#ifndef _UKNOS_H
#define _UKNOS_H

/* USER PARAMETERS */
#define PROCESS_MAX                   10
//#define ENABLE_RECURSIVE_INTERRUPT        //
#define DISABLE_TIMER_DURING_PROCESS        //timer not counting when process is processing
#define DELAY_AFTER_START             500 //in mS, delay after uKnos_Start()
/* END OF USER PARAMETERS */  

//LIB
typedef struct {
  word delay_after_start;                   // Time counter, 10ms steps
} tKernel;

//11 Bytes
typedef struct {
  byte state;
  void (*function)(void);
  dword period;
  dword counter;
} tProcess;

//extern functions
void uKnos_Init();
void uKnos_Start();
void Create_Process(dword period, void (*function)(void));

#endif
