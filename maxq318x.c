//**********************************************************************************************
// MAXQ318X.c
// (C)2010 Knuerr s.r.o., Ing. Lubos Melichar
//**********************************************************************************************
// 1.BYTE  7:6 - command mode: 0x00 -> read; 0x10 -> write
//         5:4 - datalength: 0x00 -> 1bytes; 0x01 -> 2bytes; 0x10 -> 4bytes; 0x11 -> 8 bytes
//         3:0 - MSB portion of data address
// 2.BYTE  - LSB portion of data address 
//**********************************************************************************************

#include <hw_def.h>
#include <stdio.h>
#include <my_spi.h>
#include <delay.h>
#include <uart2.h>
#include <maxq318x.h>


//GLOBAL VARIABLES
//tMM_FRAME sFrame;

//DEFINES
#define MAXQ_FIRST_BYTE_ACK  0xC1
#define MAXQ_SECOND_BYTE_ACK 0xC2

#define MAXQ_DELAY           50
#define MAXQ_DELAY_2         100

/* SPI FUNCTIONS */


void maxq_Init(){

    SPI_MasterInit(); 
}

/*******************************************/
// MAXQ_READ_WRITE()
/*******************************************/
// - read/write data from/to maxim
// - see page 23 in MAXIM datasheet
// - expect CS active already
/*******************************************/
signed char maxq_read_write(byte read_write, word address, char* pData, byte datalength){
    byte aux_data = 0x00;
    byte aux_datalength = 0;    
    byte i, address1, address2;        
    
    //MSB and LSB portion of address
    address1 = (byte)(address>>8) & 0x0F;
    address2 = (byte) (address & 0xFF);                                    
    
    //1.BYTE
    aux_data = SPI_MasterTransmit(read_write<<7 | datalength<<4 | address1); //0x1 ->read&datalength=2, 0x1 - MSB address -> A line                     
    delay_us(MAXQ_DELAY); 

    
    if(aux_data == MAXQ_FIRST_BYTE_ACK){              
                
        //2.BYTE
        aux_data = SPI_MasterTransmit(address2); //LSB address                   
        
        if(aux_data == MAXQ_SECOND_BYTE_ACK){                 

            if(read_write ==  eREAD){
            
                //maxim ready?
                for(i=0; i<30; i++){         
                    delay_us(MAXQ_DELAY_2);         
                    aux_data = SPI_MasterTransmit(0x00); //
                    if(aux_data == 0x41)
                        break;
                    //printf("\nE: Maxim is not ready, once again..");                
                }
            }
            else
                aux_data = 0x41;  
            
            // READ / WRITE DATA
            if(aux_data == 0x41){                                
                
                for(i=0; i<(1<<datalength); i++){
                
                    delay_us(MAXQ_DELAY);
                    
                    //read     
                    if(read_write ==  eREAD){   
                        aux_data = SPI_MasterTransmit(0x00); // 
                        *(byte *)(pData+aux_datalength) = aux_data; 
                        aux_datalength++;
                        //printf("\nI: read succesfull: 0x%x", aux_data);
                    }
                    
                    //write
                    else if(read_write == eWRITE){ 
                        byte aux_answer;
                        aux_data = *(byte *)(pData+aux_datalength);
                        aux_answer = SPI_MasterTransmit(aux_data); //                          
                        aux_datalength++;
                        if(aux_answer != 0x41){
                            printf("\nE: write wasnt succesfull");
                            return -1;
                        }
                        //else
                            //printf("\nI: write succesfull: 0x%x", aux_data);
                            
                        
                    }        
                    else
                        printf("\nE: wrong operation (read/write)");
                        
                }
                
                // check write operation
                if(read_write == eWRITE){
                    for(i=0; i<30; i++){         
                        delay_us(MAXQ_DELAY); 
                        aux_data = SPI_MasterTransmit(0x00);
                        if(aux_data != 0x4E){ 
                            printf("\nE:good, next step 0x%x", aux_data);
                            break;
                        }
                        else
                            printf("\nE:wrong, once again");   
                    }
                    if(aux_data != 0x41){
                        printf("\nE: write failed!");
                        return -1;
                    }
                    //else
                        //printf("\nWRITE COPLETE!!\n\n");                     
                 }
                                                               
            }
            else
                printf("\nE: SYNC(3.byte) : %x", aux_data);
                //uartSendBufferf(0,"\nE: SYNC (3.byte)");
        }
        else{
            uartSendBufferf(0,"\nE: ADDRESS (2.byte)");
            return -1;
        }             
    }
    else{
        //printf("\nE: CMD 1.B: %x", aux_data);
        return -1;                
    }
    
                	       
    delay_us(MAXQ_DELAY); 
    return 0;

}

signed char maxq_read(word address, char* pData, byte datalength){
    return maxq_read_write(eREAD, address, pData, datalength);
}

signed char maxq_write(word address, char* pData, byte datalength){
    return maxq_read_write(eWRITE, address, pData, datalength);
}

/* END OF SPI FUNCTIONS */