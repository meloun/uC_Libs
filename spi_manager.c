
/*
 *  SPI MANAGER v1_0
 *
 *  Created on: 24.9.2008
 *      Author: Luboš Melichar
 */


#include <hw_def.h>
#include <types.h>
#include <my_spi.h>

#include "system.h"
#include <spi_manager.h>
#include <spi_manager_user.h>
#include <spi_manager_funktions.h>



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * spi_manager.c 	        - z kernelu volat SPI_Manager(), postupne vybira jednotlive slavy a vola jejich obsluzne funkce
 * spi_manager_user.h 		- definice SS pinu a obsluznych funkci slavu, nutne spravne definovat
 * spi_slave_funktions.c 	- obsluzne funkce slavu, je mozno definovat vlastni,  treba i z jinych souboru
 * * * * * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ** * * * */

//global variables
byte actual_slave; // zero -> none slave selected

/* LOCAL FUNCTIONS */

//
void SPI_Init_IO(void)
{
  //nastaveni vsech SS jako vystupy
  SPI_CS1_PORT_DIR |= SPI_CS1_PIN;
  SPI_CS2_PORT_DIR |= SPI_CS2_PIN;
  SPI_CS3_PORT_DIR |= SPI_CS3_PIN;
  SPI_CS4_PORT_DIR |= SPI_CS4_PIN;
  SPI_CS5_PORT_DIR |= SPI_CS5_PIN;
  SPI_CS6_PORT_DIR |= SPI_CS6_PIN;
  SPI_CS7_PORT_DIR |= SPI_CS7_PIN;
  SPI_CS8_PORT_DIR |= SPI_CS8_PIN;

  SPI_CLEAR_ALL_CS; //all Slaves inactive (logic '1')
 
}

void SPI_Manager_Init(void){
	
	//HW
    SPI_Init_IO();
	SPI_MasterInit();
    
    //SW
    actual_slave=0;		
}


void SPI_Manager(void){

	actual_slave++;
	SPI_CLEAR_ALL_CS; //all slaves inactive

	SPI_SET_CS(actual_slave); //select next slave
	spi_funktions[actual_slave-1](actual_slave); //obsluzna funkce
	SPI_CLEAR_ALL_CS; //all slaves inactive

	if(actual_slave == SLAVES_NR)
		actual_slave=0;
}

void Spi_MasterReceive(byte *pBuffer, byte lenght){
	byte i;
	for(i=0;i<lenght;i++){
		*pBuffer = SPI_MasterTransmit(0xff);
		pBuffer++;
	}
}




