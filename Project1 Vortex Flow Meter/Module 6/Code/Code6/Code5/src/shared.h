/**-----------------------------------------------------------------------------
      \file shared.h
--                                                                           --
--              ECEN 5803 Mastering Embedded System Architecture             --
--                  Project 1 Module 4                                       --
--                Microcontroller Firmware                                   --
--                      shared.h                                            --
--                                                                           --
-------------------------------------------------------------------------------
--
--  Designed for:  University of Colorado at Boulder
--               
--                
--  Designed by:  Tim Scherr
--  Revised by:  Student's name 
-- 
-- Version: 3.0
-- Date of current revision:  2022-06-20  
-- Target Microcontroller: ST STM32F401RE 
-- Tools used:  ARM mbed compiler
--              ARM mbed SDK
--              ST Nucleo STM32F401RE Board
--               
-- 
-- Functional Description:  Header file for all globals
--
--      Copyright (c) 2015, 2022 Tim Scherr  All rights reserved.
--
*/              
                          
 #include "mbed.h"  
 
 /*****************************************************************************
* #defines available to all modules included here
******************************************************************************/ 
#define OFF 0                       /* used for readability */
#define ON 1                        /* used for readability */
#define NO 0                        /* used for readability */
#define YES 1                       /* used for readability */
#define TEN 10

#define TIMER0 TMR0
#define SEC 10000           /* 10000 timer0 interrupts per second (100 usec.) */
                   
#define T100MS 0.1*SEC
#define T2S    2*SEC
                              
#define LED_FLASH_PERIOD .5   /* in seconds */
 
#define CLOCK_FREQUENCY_MHZ 8
#define CODE_VERSION "2.0 2016/09/29"   /*   YYYY/MM/DD  */
#define COPYRIGHT "Copyright (c) University of Colorado" 

 enum boolean { FALSE, TRUE };           /// \enum boolean  
 enum dmode {QUIET, NORMAL, DEBUG, VERSION, REGISTERS, MEMORY, STACK};
 
 typedef unsigned char uchar8_t;       
 typedef unsigned char bit;
 typedef unsigned int uint32_t;
 typedef unsigned short uint16_t;
 
#ifdef __cplusplus 
extern "C" {
#endif
 
/************************************************************************/
/*             Global Variable declarations                             */
/************************************************************************/
 
 extern unsigned char Error_status;          // Variable for debugging use
 extern uchar8_t  display_timer;  // \var 1 second software timer for display   
 extern uchar8_t  display_flag;   // flag between timer interrupt and monitor.c, 
                        // like a binary semaphore
 extern uchar8_t tx_in_progress;                        
 extern uchar8_t *rx_in_ptr; /* pointer to the receive in data */
 extern uchar8_t *rx_out_ptr; /* pointer to the receive out data*/
 extern uchar8_t *tx_in_ptr; /* pointer to the transmit in data*/
 extern uchar8_t *tx_out_ptr; /*pointer to the transmit out */                       
#define RX_BUF_SIZE 10            /* size of receive buffer in bytes */
#define TX_BUF_SIZE 40           /* size of transmit buffer in bytes */
                                                                    
/******************************************************************************
* Some variable definitions are done in the module main.c and are externed in 
* all other modules.  The following section is visible to main.c only.
******************************************************************************/
#ifdef MAIN

 enum dmode display_mode = QUIET;
 
 uchar8_t serial_flag = 0;
 
 uchar8_t tx_in_progress; 
 uchar8_t *rx_in_ptr; /* pointer to the receive in data */
 uchar8_t *rx_out_ptr; /* pointer to the receive out data*/
 uchar8_t *tx_in_ptr; /* pointer to the transmit in data*/
 uchar8_t *tx_out_ptr; /*pointer to the transmit out */        
    
 uchar8_t  rx_buf[RX_BUF_SIZE];      /* define the storage */
 uchar8_t  tx_buf[TX_BUF_SIZE];      /* define the storage */

#define MSG_BUF_SIZE 10
 uchar8_t msg_buf[MSG_BUF_SIZE]; // define the storage for UART received messages
 uchar8_t msg_buf_idx = 0;    // index into the received message buffer       

/******************************************************************************
* Some variable definitions are done in the module main.c and are externed in 
* all other modules.  The following section is visible to all modules EXCEPT 
* main.c.
*******************************************************************************/
#else

/**********************/   
/*   Declarations     */
/**********************/

   extern volatile     uchar8_t swtimer0;
   extern volatile     uchar8_t swtimer1;
   extern volatile     uchar8_t swtimer2;
   extern volatile     uchar8_t swtimer3; 
   extern volatile     uchar8_t swtimer4;    
   extern volatile     uchar8_t swtimer5;    
   extern volatile     uchar8_t swtimer6;    
   extern volatile     uchar8_t swtimer7;    
  
  extern uchar8_t serial_flag;
    
  extern enum dmode display_mode;
  
  
  extern uchar8_t  rx_buf[];      /* declare the storage */
  extern uchar8_t  tx_buf[];      /* declare the storage */

#define MSG_BUF_SIZE 10    
  extern  uchar8_t msg_buf[MSG_BUF_SIZE]; // declare the storage for UART received messages
  extern  uchar8_t msg_buf_idx;         // index into the received message buffer

#endif

/*******************************************************************************
* All function prototypes are externed in all the modules.
*******************************************************************************/
extern void monitor(void);  /* located in module monitor.c */
extern void timer0(void);   /* located in module timer0.c */
extern void serial(void);   /* located in module UART_poll.c */

extern void UART_put(uchar8_t);                 /* located in module UART_poll.c */
extern uchar8_t UART_get(void);                 /* located in module UART_poll.c */
extern uchar8_t UART_input(void);               /* located in module UART_poll.c */
extern void UART_direct_msg_put(const char *);
                                             /* located in module UART_poll.c */
extern void UART_msg_put(const char *); 
                                             /* located in module UART_poll.c */
extern void UART_direct_hex_put(uchar8_t);      /* located in module UART_poll.c */
extern void UART_direct_put(uchar8_t);          /* located in module UART_poll.c */
extern void UART_hex_put(uchar8_t);             /* located in module UART_poll.c */
extern void UART_low_nibble_put(uchar8_t);      /* located in module UART_poll.c */
extern void UART_high_nibble_put(uchar8_t);     /* located in module UART_poll.c */
extern void chk_UART_msg(void);              /* located in module monitor.c */
extern void UART_msg_process(void);          /* located in module monitors.c */
extern void status_report(void);             /* located in module monitor.c */  
extern void set_display_mode(void);          /* located in module monitor.c */

#ifdef __cplusplus
}
#endif

