// Data type definitions

#ifndef _TYPES_H
#define _TYPES_H

typedef unsigned char   byte;
typedef unsigned char   u08;

typedef unsigned int	  word;
typedef unsigned int	  u16;

typedef unsigned long	  dword;
typedef unsigned long	  u32;


typedef signed long     s32;

typedef unsigned char   BYTE;
typedef unsigned int	  WORD;
typedef unsigned long	  DWORD;


#ifndef NULL
#define NULL 0
#endif

// Symbolicke definice typu
#define T_BYTE          1
#define T_CHAR          2
#define T_WORD          3
#define T_INT           4
#define T_DWORD         5
#define T_LONG          6  
#define T_STRING        10
#define T_FIELD         11
#define T_RFID          12
#define T_DATETIME      13     
#define T_DATE          14
#define T_ADDR32        15
#define T_BIT8          20
#define T_BIT16         21
#define T_BIT32         22



#endif
