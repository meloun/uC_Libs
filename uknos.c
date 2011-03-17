//**********************************************************************************************
// uKNOS - micro Knuerr operating system
// (C)2010 Knuerr s.r.o, Ing. Lubos Melichar
//**********************************************************************************************
// Version     :   1.0
//***************************************************************** 
// Description :  
//    uKnos slouzi k periodickemu volani uzivatelskych funci -> procesu.
//    Zakladni casova zakladna je 1 mS.     
//    Preruseni uvnitr procesu jsou zejmena kvuli komunikacim povolene.(default)
//*****************************************************************
// Memory Management  :
//    RAM    :   110 Bytes  
//    FLASH  :     X Bytes     
//*****************************************************************

#include <types.h>
#include <stdio.h>
#include <hw_def.h>
#include <uknos.h>


//GLOBAL VARIABLES
tKernel sKernel;
tProcess sProcess[PROCESS_MAX];    // tabulka procesu

//LOCAL VARIABLES 
typedef enum{
  PROCESS_FREE,     //prazdny proces bez prirazene funkce
  PROCESS_STANDBY,  //proces ceka na zavolani
  PROCESS_BUSSY     //proces se prave vykonava
}ePROCESS_STATE;


//*****************************************************************************
// INIT 10 MILISECOND INTERRUPT, CTC MODE
//*****************************************************************************
// 11,0592MHZ
void uKnos_Init(){
    byte i;
    // Timer/Counter 0 initialization
    // Clock source: System Clock
    // Clock value: 10,800 kHz
    // Mode: CTC top=OCR0A
    TCCR0A = 0x02;
    TCCR0B = 0x05;
    TCNT0  = 0x00;
    OCR0A  = 0x6C - 1;   // 0x6C=108; //prescaler timeru je 1024!
    OCR0B  = 0x00;
    
    // Timer/Counter 0 Interrupt(s) initialization
    TIMSK0=0x02;  //compare match  
    
    sKernel.delay_after_start = DELAY_AFTER_START / 10;
    
    for (i = 0; i < PROCESS_MAX; i++) {       
        sProcess[i].state = PROCESS_FREE;   //proces volny
    }
}

void uKnos_Start(){
    #asm("sei")
}

//*****************************************************************************
// Funkce pro vytvoreni periodicky volane funkce -> procesu
// dword period - perioda volani funkce v ms
// flash dword *function - adresa funkce, ktera ma byt volana
//*****************************************************************************
void Create_Process(dword period,  void (*function)(void)){
  byte i;
  tProcess *p_aux_process;

  for (i = 0; i < PROCESS_MAX; i++) {
    p_aux_process = &sProcess[i];
    if (p_aux_process->state == PROCESS_FREE) {   // pokud je proces volny
      p_aux_process->state = PROCESS_STANDBY;
      p_aux_process->function = function;
      if (period < 10)
        period = 10;
      p_aux_process->period = ((period<10)? 1 : period/10);
      p_aux_process->counter =((period<10)? 1 : period/10);
      printf("\ncreate process nr.%d ..",i); 
      return;
    }
  }
  // tady udelat dbg vypis nebo signalizaci chyby  
}

//*****************************************************************************
// 10 MILISECOND INTERRUPT, kde se periodicky vyvolavaji procesy
//*****************************************************************************
// Timer 0 output compare A interrupt service routine
interrupt [TIM0_COMPA] void timer0_compa_isr(void){
  byte i;
  tProcess *p_aux_process; 
  void (*called_funcion)(void);  
  
  // povolit vnorena preruseni
  #ifdef ENABLE_RECURSIVE_INTERRUPT
    ENABLE_INTERRUPT
  #endif      

     

  //delay after kernel start  
  if(sKernel.delay_after_start != 0){
    sKernel.delay_after_start--;     
    return;        
  }   
  
  #ifdef DISABLE_TIMER_DURING_PROCESS 
    TIMSK0=0x00;
  #endif    

  // spusteni procesu
  for (i = 0; i < PROCESS_MAX; i++) {   //pres vsechny procesy
    p_aux_process = &sProcess[i];
    if (p_aux_process->state == PROCESS_STANDBY) {

      if (--(p_aux_process->counter) == 0) {    // proces ma byt vyvolan
                
        p_aux_process->state = PROCESS_BUSSY;
                  
        // zavola se odpovidajici funkce
        //toDo: vyzkouset a zahodit pomocnou promennou, volat primo  
        //printf("\n%d s",i);                
        called_funcion = ( void (*)(void))p_aux_process->function;          
        called_funcion();
        //printf("\n%d e",i);              
                  
        // nastaveni periody u procesu
        p_aux_process->counter = p_aux_process->period;
                                      
        //uvolneni procesu pro dalsi volani 
        p_aux_process->state = PROCESS_STANDBY;     
      } // if (counter == 0) end
    } // if (process == PROCESS_STANDBY) end
  } // for cyklus end
  
  #ifdef DISABLE_TIMER_DURING_PROCESS
    TIMSK0=0x02;
  #endif  
}