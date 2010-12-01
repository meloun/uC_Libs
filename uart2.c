/*! \file uart2.c \brief Dual UART driver with buffer support. */
//*****************************************************************************
//
// File Name	: 'uart2.c'
// Title		: Dual UART driver with buffer support
// Author		: Pascal Stang - Copyright (C) 2000-2004
// Created		: 11/20/2000
// Revised		: 07/04/2004
// Version		: 1.0
// Target MCU	: ATMEL AVR Series
// Editor Tabs	: 4
//
// Description	: This is a UART driver for AVR-series processors with two
//		hardware UARTs such as the mega161 and mega128
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************


#include <hw_def.h>
#include <buffer.h>
#include <uart2.h>
#include <digital_outputs.h>


// UART global variables
// flag variables
volatile byte uartReadyTx[2];
volatile byte uartBufferedTx[2];
//transmit buffers
cBuffer uartTxBuffer[2];
unsigned short uartRxOverflow[2];

// automatically allocate space in ram for each buffer

static char uart0TxData[UART0_TX_BUFFER_SIZE];
static char uart1TxData[UART1_TX_BUFFER_SIZE];


typedef void (*voidFuncPtrbyte)(unsigned char);
volatile static voidFuncPtrbyte UartRxFunc[2];

void uartInit(byte nUart)
{
	// initialize uarts
    if(nUart)
        uart1Init();
    else    
	    uart0Init();
	
}

void uart0Init(void)
{
	// initialize the buffers
	uart0InitBuffers();
    
	// initialize user receive handlers
	UartRxFunc[0] = 0;
    
	// enable RxD/TxD and interrupts
	UCSR0B = (1<<RXCIE) | (1<<TXCIE) | (1<<RXEN) | (1<<TXEN);
    
	// set default baud rate
    // uartSetBaudRate(0, UART0_DEFAULT_BAUD_RATE);
    
	// initialize states
	uartReadyTx[0] = 1;
	uartBufferedTx[0] = 0;
    
	// clear overflow count
	uartRxOverflow[0] = 0;
    
	// enable interrupts
	//#asm("sei")
}

void uart1Init(void)
{
	// initialize the buffers
	uart1InitBuffers();
	// initialize user receive handlers
	UartRxFunc[1] = 0;
	// enable RxD/TxD and interrupts
	UCSR1B = (1<<RXCIE) | (1<<TXCIE) | (1<<RXEN) | (1<<TXEN);
	// set default baud rate
//	uartSetBaudRate(1, UART1_DEFAULT_BAUD_RATE);
	// initialize states
	uartReadyTx[1] = 1;
	uartBufferedTx[1] = 0;
	// clear overflow count
	uartRxOverflow[1] = 0;
	// enable interrupts
	//#asm("sei")
}

void uart0InitBuffers(void)
{
    // initialize the UART0 buffers
	bufferInit(&uartTxBuffer[0], uart0TxData, UART0_TX_BUFFER_SIZE);
}

void uart1InitBuffers(void)
{
	// initialize the UART1 buffers
	bufferInit(&uartTxBuffer[1], uart1TxData, UART1_TX_BUFFER_SIZE);
}

void uartSetRxHandler(byte nUart, void (*rx_func)(unsigned char c))
{
	if(nUart < 2) // make sure the uart number is within bounds
	{
		UartRxFunc[nUart] = rx_func; // set the receive interrupt to run the supplied user function
	}
}

void uartSetBaudRate(byte nUart, dword baudrate, byte double_speed_mode)
{
	word bauddiv;
	byte u2x_flag;

	if(double_speed_mode){
		bauddiv = ((F_CPU+(baudrate*4L))/(baudrate*8L)-1); // calculate division factor for requested baud rate, and set it
		u2x_flag = 1;
	}
	else{
		bauddiv = ((F_CPU+(baudrate*8L))/(baudrate*16L)-1); // calculate division factor for requested baud rate, and set it
		u2x_flag = 0;
	}

	if(nUart)
	{
		UBRR1L = bauddiv;
		#ifdef UBRR1H
		UBRR1H = (bauddiv>>8);
		#endif
		UCSR0A &= ~(1 << U2X0); 			//clear
		UCSR0A |= (u2x_flag << U2X0);		//set (if u2x_flag is set)
	}
	else
	{
		UBRR0L = bauddiv;
		#ifdef UBRR0H
		UBRR0H = (bauddiv>>8);
		#endif
		UCSR1A &= ~(1 << U2X0); 			//clear
		UCSR1A |= (u2x_flag << U2X0);		//set (if u2x_flag is set)
	}
}

cBuffer* uartGetTxBuffer(byte nUart)
{
	return &uartTxBuffer[nUart]; // return tx buffer pointer
}

void uartSendByte(byte nUart, byte txData)
{
  // wait for the transmitter to be ready
  while(!uartReadyTx[nUart]);
  
  //L.M. - vysilam v preruseni od prijmu
  // vyvola se znova preruseni od prijmu ale neprobehlo preruseni od vysilani kde se shazuje flag
  //uartReadyTx[nUart] = 0; // set ready state to 0

	// send byte
	if(nUart)
	{
		while(!(UCSR1A & (1<<UDRE)));
			UDR1 = txData;
	}
	else
	{
		while(!(UCSR0A & (1<<UDRE)));
			UDR0 = txData;
	}
}

void uart0SendByte(u08 data)
{
	// send byte on UART0
	uartSendByte(0, data);
}

void uart1SendByte(u08 data)
{
	// send byte on UART1
	uartSendByte(1, data);
}

void uartAddToTxBuffer(byte nUart, byte data)
{
	// add data byte to the end of the tx buffer
	bufferAddToEnd(&uartTxBuffer[nUart], data);
}

void uartSendTxBuffer(byte nUart)
{
	// turn on buffered transmit
	uartBufferedTx[nUart] = 1;
	// send the first byte to get things going by interrupts
	uartSendByte(nUart, bufferGetFromFront(&uartTxBuffer[nUart]));
}

byte uartSendBuffer(byte nUart, char *buffer, word nBytes)
{
	register byte first;
	register word i;

	// check if there's space (and that we have any bytes to send at all)
	if((uartTxBuffer[nUart].datalength + nBytes < uartTxBuffer[nUart].size) && nBytes)
	{
		first = *buffer++; // grab first character
		// copy user buffer to uart transmit buffer
		for(i = 0; i < nBytes-1; i++)
		{
			bufferAddToEnd(&uartTxBuffer[nUart], *buffer++); // put data bytes at end of buffer
		}

		// send the first byte to get things going by interrupts
		uartBufferedTx[nUart] = 1;
		uartSendByte(nUart, first);
		return 1; // return success
	}
	else
	{
		return 0; // return failure
	}
}
void uartSendBufferf(byte nUart, char flash *text){
  while(*text)
  {
  	if(nUart){
    	while (!( UCSR1A & 0x20));
    	UDR1 = *text++;
  	}
  	else{
    	while (!( UCSR0A & 0x20));
    	UDR0 = *text++;
  	}
  }
}

// UART Transmit Complete Interrupt Function
void uartTransmitService(byte nUart)
{
	// check if buffered tx is enabled
	if(uartBufferedTx[nUart])
	{
		// check if there's data left in the buffer
		if(uartTxBuffer[nUart].datalength)
		{
			// send byte from top of buffer
			if(nUart)
				UDR1 =  bufferGetFromFront(&uartTxBuffer[1]);
			else
				UDR0 =  bufferGetFromFront(&uartTxBuffer[0]);
		}
		else
		{
			uartBufferedTx[nUart] = 0; // no data left
			uartReadyTx[nUart] = 1; // return to ready state

      // Comm LED off
      LED_COMM_OFF;
		}
	}
	else
	{
		// we're using single-byte tx mode
		// indicate transmit complete, back to ready
		uartReadyTx[nUart] = 1;

    // Comm LED off
    LED_COMM_OFF;
	}
}

// UART Receive Complete Interrupt Function
void uartReceiveService(byte nUart)
{
	byte c;
    
	// get received char
	if(nUart)
		c = UDR1;
	else
		c = UDR0;

	// if there's a user function to handle this receive event
	if(UartRxFunc[nUart])
	{
		// call it and pass the received data
		UartRxFunc[nUart](c);
	}

}


interrupt [USART0_TXC] void usart0_tx_isr(void)
{
	// service UART0 transmit interrupt
	uartTransmitService(0);
}

interrupt [USART1_TXC] void usart1_tx_isr(void)
{
	// service UART1 transmit interrupt
	uartTransmitService(1);
}

interrupt [USART0_RXC] void usart0_rx_isr(void)
{
	// service UART0 receive interrupt
	uartReceiveService(0);
}

interrupt [USART1_RXC] void usart1_rx_isr(void)
{
	// service UART1 receive interrupt
	uartReceiveService(1);
}
