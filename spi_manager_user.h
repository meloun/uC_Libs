//*******************************************************************
// spi_manager_user.h
// (C)2010 Knuerr s.r.o., Ing. Lubos Melichar
//*******************************************************************
// uzivatelska konfigurace pro knihovnu spi_manager
//*******************************************************************

#ifndef SPI_MANAGER_USER_H_
#define SPI_MANAGER_USER_H_


	#define SLAVES_NR		1

/* SLAVE SELECT PINS */

  //slave nr.1
	#define SPI_CS1_PORT			PORTA
	#define SPI_CS1_PORT_DIR		DDRA
	#define SPI_CS1_PIN				0x01
  
  //slave nr.2
	#define SPI_CS2_PORT			PORTA
	#define SPI_CS2_PORT_DIR		DDRA
	#define SPI_CS2_PIN				0x02
  
  //slave nr.3
	#define SPI_CS3_PORT			PORTA
	#define SPI_CS3_PORT_DIR		DDRA
	#define SPI_CS3_PIN				0x04
  
  //slave nr.4
	#define SPI_CS4_PORT			PORTA
	#define SPI_CS4_PORT_DIR		DDRA
	#define SPI_CS4_PIN				0x08
  
  //slave nr.5
	#define SPI_CS5_PORT			PORTA
	#define SPI_CS5_PORT_DIR		DDRA
	#define SPI_CS5_PIN				0x10
  
  //slave nr.6
	#define SPI_CS6_PORT			PORTA
	#define SPI_CS6_PORT_DIR		DDRA
	#define SPI_CS6_PIN				0x20
  
  //slave nr.7
	#define SPI_CS7_PORT			PORTA
	#define SPI_CS7_PORT_DIR		DDRA
	#define SPI_CS7_PIN				0x40
  
  //slave nr.8
	#define SPI_CS8_PORT			PORTA
	#define SPI_CS8_PORT_DIR		DDRA
	#define SPI_CS8_PIN				0x80  

#endif /* SPI_MANAGER_USER_H_ */
