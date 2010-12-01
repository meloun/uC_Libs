/*
 * spi_manager_funktions.h
 *
 *  Created on: 4.11.2008
 *      Author: Luboš Melichar
 */

#ifndef SPI_MANAGER_FUNKTIONS_H_
#define SPI_MANAGER_FUNKTIONS_H_

//obsluzne funkce
//#include <lru\spi_f_default.h>
//#include <cards.h>

// DEFINICE OBSLUZNYCH FUNKCI PRO SLAVE

	pSPI_FUNCTION spi_funktions[SLAVES_NR] = {
		NULL,		//cards.c
		NULL,
		NULL,		//cards.c
		NULL
		//
	};


#endif /* SPI_MANAGER_FUNKTIONS_H_ */
