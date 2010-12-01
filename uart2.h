/*! \file uart2.h \brief Dual UART driver with buffer support. */
//*****************************************************************************
//
// File Name	: 'uart2.h'
// Title		: Dual UART driver with buffer support
// Author		: Pascal Stang - Copyright (C) 2000-2002
// Created		: 11/20/2000
// Revised		: 07/04/2004
// Version		: 1.0
// Target MCU	: ATMEL AVR Series
// Editor Tabs	: 4
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
///	\ingroup driver_avr
/// \defgroup uart2 UART Driver/Function Library for dual-UART processors (uart2.c)
/// \code #include "uart2.h" \endcode
/// \par Overview
///		This is a UART driver for AVR-series processors with two hardware
///		UARTs such as the mega161 and mega128. This library provides both
///		buffered and unbuffered transmit and receive functions for the AVR
///		processor UART. Buffered access means that the UART can transmit
///		and receive data in the "background", while your code continues
///		executing.  Also included are functions to initialize the UARTs,
///		set the baud rate, flush the buffers, and check buffer status.
///
/// \note	For full text output functionality, you may wish to use the rprintf
///		functions along with this driver.
///
/// \par About UART operations
///		Most Atmel AVR-series processors contain one or more hardware UARTs
///		(aka, serial ports).  UART serial ports can communicate with other
///		serial ports of the same type, like those used on PCs.  In general,
///		UARTs are used to communicate with devices that are RS-232 compatible
///		(RS-232 is a certain kind of serial port).
///	\par
///		By far, the most common use for serial communications on AVR processors
///		is for sending information and data to a PC running a terminal program.
///		Here is an exmaple:
///	\code
/// uartInit();					// initialize UARTs (serial ports)
/// uartSetBaudRate(0, 9600);	// set UART0 speed to 9600 baud
/// uartSetBaudRate(1, 115200);	// set UART1 speed to 115200 baud
///
/// rprintfInit(uart0SendByte);	// configure rprintf to use UART0 for output
/// rprintf("Hello UART0\r\n");	// send "hello world" message via UART0
///
/// rprintfInit(uart1SendByte);	// configure rprintf to use UART1 for output
/// rprintf("Hello UART1\r\n");	// send "hello world" message via UART1
/// \endcode
///
/// \warning The CPU frequency (F_CPU) must be set correctly in \c global.h
///		for the UART library to calculate correct baud rates.  Furthermore,
///		certain CPU frequencies will not produce exact baud rates due to
///		integer frequency division round-off.  See your AVR processor's
///		 datasheet for full details.
//
//*****************************************************************************

#ifndef UART2_H
#define UART2_H

#include <types.h>
#include <buffer.h>

//! Default uart baud rate.
/// This is the default speed after a uartInit() command,
/// and can be changed by using uartSetBaudRate().
#define UART0_DEFAULT_BAUD_RATE		9600	///< default baud rate for UART0
#define UART1_DEFAULT_BAUD_RATE		9600	///< default baud rate for UART1

// buffer memory allocation defines
// buffer sizes
#define UART0_TX_BUFFER_SIZE		0x0030	///< number of bytes for uart0 transmit buffer
#define UART1_TX_BUFFER_SIZE		0x0030	///< number of bytes for uart1 transmit buffer

// functions

//! Initializes UARTs.
/// \note	After running this init function, the processor
/// I/O pins that used for uart communications (RXD, TXD)
/// are no long available for general purpose I/O.
//void uartInit(void);
void uartInit(byte nUart);

//! Initializes UART0 only.
void uart0Init(void);

//! Initializes UART1 only.
void uart1Init(void);

//! Initializes transmit and receive buffers.
/// Automatically called from uartInit()
void uart0InitBuffers(void);
void uart1InitBuffers(void);

//! Redirects received data to a user function.
///
void uartSetRxHandler(byte nUart, void (*rx_func)(unsigned char c));

//! Sets the uart baud rate.
/// Argument should be in bits-per-second, like \c uartSetBaudRate(9600);
void uartSetBaudRate(byte nUart, dword baudrate, byte double_speed_mode);


//! Returns pointer to the transmit buffer structure.
///
cBuffer* uartGetTxBuffer(byte nUart);

//! Sends a single byte over the uart.
///
void uartSendByte(byte nUart, byte txData);

//! SendByte commands with the UART number hardcoded
/// Use these with printfInit() - example: \c printfInit(uart0SendByte);
void uart0SendByte(byte data);
void uart1SendByte(byte data);


//! Add byte to end of uart Tx buffer.
///
void uartAddToTxBuffer(byte nUart, byte data);

//! AddToTxBuffer commands with the UART number hardcoded
/// Use this with printfInit() - example: \c printfInit(uart0AddToTxBuffer);
//void uart0AddToTxBuffer(byte data);
//void uart1AddToTxBuffer(byte data);

//! Begins transmission of the transmit buffer under interrupt control.
///
void uartSendTxBuffer(byte nUart);

//! sends a buffer of length nBytes via the uart using interrupt control.
///
byte uartSendBuffer(byte nUart, char *buffer, word nBytes);
void uartSendBufferf(byte nUart, char flash *text);

//! interrupt service handlers
void uartTransmitService(byte nUart);
void uartReceiveService(byte nUart);

#endif

