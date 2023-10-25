/**----------------------------------------------------------------------------
             \file Monitor.cpp
--                                                                           --
--              ECEN 5003 Mastering Embedded System Architecture             --
--                  Project 1 Module 4                                       --
--                Microcontroller Firmware                                   --
--                      Monitor.cpp                                            --
--                                                                           --
-------------------------------------------------------------------------------
--
--  Designed for:  University of Colorado at Boulder
--               
--                
--  Designed by:  Tim Scherr
--  Revised by:  Student's name 
-- 
-- Version: 2.0
-- Date of current revision:  2022-06-20   
-- Target Microcontroller: ST STM32F401RE 
-- Tools used:  ARM mbed compiler
--              ARM mbed SDK
--              ST Nucleo STM32F401RE Board
--               
-- 
   Functional Description: See below 
--
--      Copyright (c) 2015, 2022 Tim Scherr All rights reserved.
--
*/              

#include <stdio.h>
#include "shared.h"
#include "memory.h"

//extern bool redLEDFlag;


/*******************************************************************************
* Set Display Mode Function
* Function determines the correct display mode.  The 3 display modes operate as 
*   follows:
*
*  NORMAL MODE       Outputs only mode and state information changes   
*                     and calculated outputs
*
*  QUIET MODE        No Outputs
*
*  DEBUG MODE        Outputs mode and state information, error counts,
*                    register displays, sensor states, and calculated output
*                  (currently not all features are operation, could be enhanced)
*
* There is deliberate delay in switching between modes to allow the RS-232 cable 
* to be plugged into the header without causing problems. 
*******************************************************************************/


//*****************************************************************************/
/// \fn void set_display_mode(void)
///
/// \brief Displays a selection menu over UART.
///
/// This function sends a series of messages over UART to display a menu 
/// allowing the user to choose between different modes. Each mode is 
/// highlighted with a different color.
//*****************************************************************************/

void set_display_mode(void)   
{
    UART_direct_msg_put("\033[37m\r\n+------------------------+\033[0m");    
    UART_direct_msg_put("\r\n\033[37m|  Select Mode           |\033[0m");    
    UART_direct_msg_put("\033[37m\r\n|------------------------|\033[0m");    
    UART_direct_msg_put("\r\n\033[32m|  NOR - Normal          |\033[0m");    
    UART_direct_msg_put("\r\n\033[33m|  QUI - Quiet           |\033[0m");    
    UART_direct_msg_put("\r\n\033[35m|  DEB - Debug           |\033[0m");    
    //UART_direct_msg_put("\r\n\033[31m|  RED - Red Led(1s)     |\033[0m");  
    UART_direct_msg_put("\r\n\033[34m|  REG - Registers Dump  |\033[0m");    
    UART_direct_msg_put("\r\n\033[31m|  MEM - Memory Dump     |\033[0m");    
    UART_direct_msg_put("\r\n\033[36m|  STK - Stack Dump      |\033[0m");    
    UART_direct_msg_put("\r\n\033[97m|  V   - Version#        |\033[0m");    
    UART_direct_msg_put("\033[37m\r\n+------------------------+\033[0m");    
    UART_direct_msg_put("\033[0m\r\nSelect:  ");                        
}




//*****************************************************************************/
/// \fn void chk_UART_msg(void) 
///
///  \brief - fills a message buffer until return is encountered, then calls
///           message processing
//*****************************************************************************/
/****************      ECEN 5803 add code as indicated   **********************/
  // Improve behavior of this function
void chk_UART_msg(void)    
{
   uchar8_t j;
   while( UART_input() )      // becomes true only when a byte has been received
   {                                    // skip if no characters pending
      j = UART_get();                 // get next character

      if( j == '\r' )          // on a enter (return) key press
      {                // complete message (all messages end in carriage return)
				 //UART_msg_put("");
         UART_direct_msg_put("->");
         UART_msg_process();
      }
      else 
      {
         if ((j != 0x02) )         // if not ^B
         {                             // if not command, then   
            UART_put(j);              // echo the character   
         }
         else
         {
           ;
         }
         if( j == '\b' ) 
         {                             // backspace editor
            if( msg_buf_idx != 0) 
            {                       // if not 1st character then destructive 
               UART_msg_put(" \b");// backspace
               msg_buf_idx--;
            }
         }
         else if( msg_buf_idx >= MSG_BUF_SIZE )  
         {                                // check message length too large
            UART_msg_put("\r\nToo Long!");
            msg_buf_idx = 0;
         }
         else if ((display_mode == QUIET) && (msg_buf[0] != 0x02) && 
                  (msg_buf[0] != 'D') && (msg_buf[0] != 'N') && 
                  (msg_buf[0] != 'V') && (msg_buf[0] != 'R') &&
									(msg_buf[0] != 'M') && (msg_buf[0] != 'S') &&
                  (msg_buf_idx != 0))
         {                          // if first character is bad in Quiet mode
            msg_buf_idx = 0;        // then start over
         }
         else {                        // not complete message, store character
 
            msg_buf[msg_buf_idx] = j;
            msg_buf_idx++;
            if (msg_buf_idx > 3)
            {
               UART_msg_process();
            }
         }
      }
   }
}


//*****************************************************************************/
///  \fn void UART_msg_process(void) 
///UART Input Message Processing
//*****************************************************************************/
void UART_msg_process(void)
{
   uchar8_t chr,err=0;
//   unsigned char  data;

   // Check if the first character of the message buffer is an uppercase letter
   if( (chr = msg_buf[0]) <= 0x60 ) 
   {      // Upper Case
      switch( chr ) 
      {
         // DEBUG Mode
         case 'D':
            if((msg_buf[1] == 'E') && (msg_buf[2] == 'B') && (msg_buf_idx == 3)) 
            {
               display_mode = DEBUG;
               UART_direct_msg_put("\r\n\033[35mMode=DEBUG\033[0m\n");
               display_timer = 0;
            }
            else
               err = 1;
            break;
						
         // NORMAL Mode
         case 'N':
            if((msg_buf[1] == 'O') && (msg_buf[2] == 'R') && (msg_buf_idx == 3)) 
            {
               display_mode = NORMAL;
               UART_direct_msg_put("\r\n\033[32mMode=NORMAL\033[0m\n");
               //display_timer = 0;
            }
            else
               err = 1;
            break;
						
         // QUIET Mode
         case 'Q':
            if((msg_buf[1] == 'U') && (msg_buf[2] == 'I') && (msg_buf_idx == 3)) 
            {
               display_mode = QUIET;
               UART_direct_msg_put("\r\n\033[33mMode=QUIET\033[0m\n");
               display_timer = 0;
            }
            else
               err = 1;
            break;
						
         // VERSION Info
         case 'V':
            display_mode = VERSION;
            UART_direct_msg_put("\033[97m\r\n");
            UART_direct_msg_put(CODE_VERSION); 
				    UART_direct_msg_put("\033[0m\r\nSelect:  ");
            display_timer = 0;
            break;
/****************      ECEN 5803 add code as indicated   **********************/
//  Add other message types here
				 /* For Red Led Flag Mode
				 case 'R':
					 if((msg_buf[1] == 'E') && (msg_buf[2] == 'D') && (msg_buf_idx == 3)) 
            {
               display_mode = RED;
               UART_msg_put("\r\n\033[31mMode=RED LED(1s)\033[0m\n");
               display_timer = 0;
            }
            else
               err = 1;
						break;
				 */
         // Register Dump
				 case 'R':
					 if((msg_buf[1] == 'E') && (msg_buf[2] == 'G') && (msg_buf_idx == 3)) 
            {
               display_mode = REGISTERS;
               UART_msg_put("\r\n\033[34mMode=Registers Dump\033[0m\n");
               display_timer = 0;
            }
            else
               err = 1;
						break;
						
         // Memory Dump
					case 'M':
					 if((msg_buf[1] == 'E') && (msg_buf[2] == 'M') && (msg_buf_idx == 3)) 
            {
               display_mode = MEMORY;
               UART_msg_put("\r\n\033[31mMode=Memory Dump\033[0m\n");
               display_timer = 0;
            }
            else
               err = 1;
						break;
         
					// Stack Dump
					case 'S':
					 if((msg_buf[1] == 'T') && (msg_buf[2] == 'K') && (msg_buf_idx == 3)) 
            {
               display_mode = STACK;
               UART_msg_put("\r\n\033[36mMode=Stack Dump\033[0m\n");
               display_timer = 0;
            }
            else
               err = 1;
						break;
						
         // DEFAULT 
         default:
            err = 1;
      }
   }
   // Display error messages based on the error code
   else 
   {    		 // Lower Case
      switch( chr ) 
      {
        default:
         err = 1;
      }
   }

   if( err == 1 )
   {
      UART_direct_msg_put("\n\rEntry Error!");
   }   
   else if( err == 2 )
   {
      UART_direct_msg_put("\n\rNot in DEBUG Mode!");
   }   
   else
   {
    msg_buf_idx = 0;          // put index to start of buffer for next message
      ;
   }
   msg_buf_idx = 0;          // put index to start of buffer for next message


}


//*****************************************************************************
///   \fn   is_hex
/// Function takes 
///  @param a single ASCII character and returns 
///  @return 1 if hex digit, 0 otherwise.
///    
//*****************************************************************************
uchar8_t is_hex(uchar8_t c)
{
   if( (((c |= 0x20) >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'f'))  )
      return 1;
   return 0;
}

/*******************************************************************************
*   \fn  DEBUG and DIAGNOSTIC Mode UART Operation
*******************************************************************************/
void monitor(void)
{

/**********************************/
/*     Spew outputs               */
/**********************************/

   switch(display_mode)
   {
      case(QUIET):
         {
						 //redLEDFlag = false;
             UART_msg_put("\r\n ");
             display_flag = 0;
         }  
         break;
      case(VERSION):
         {
					   //redLEDFlag = false;
             display_flag = 0;
         }  
         break;         
      case(NORMAL):
         {
					  //redLEDFlag = false;
            if (display_flag == 1)
            {
               UART_msg_put("\r\n\033[32mNORMAL ");
               UART_msg_put(" Flow: ");
               // ECEN 5803 add code as indicated
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               UART_msg_put(" Temp: ");
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               UART_msg_put(" Freq: \033[0m");
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               display_flag = 0;
					     //wait_ms(500);
            }
         }  
         break;
      case(DEBUG):
         {
					  //redLEDFlag = false;
            if (display_flag == 1)
            {
               UART_msg_put("\r\n\033[35mDEBUG ");
               UART_msg_put(" Flow: ");
               // ECEN 5803 add code as indicated               
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               UART_msg_put(" Temp: ");
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               UART_msg_put(" Freq: \033[0m");
               //  add flow data output here, use UART_hex_put or similar for 
               // numbers
               
               
/****************      ECEN 5803 add code as indicated   **********************/          
               //  Create a display of  error counts, sensor states, and
               //  ARM Registers R0-R15
							 //print_registers();
               
               //  Create a command to read a section of Memory and display it
               //dump_memory();
               
               //  Create a command to read 16 words from the current stack 
               // and display it in reverse chronological order.
							 //display_last_16_stack_words();
              
              
               // clear flag to ISR      
               display_flag = 0;
							 //wait_ms(500);
             }   
         }  
         break;
			/* Red Led Flag Mode
			case(RED):
			{
				redLEDFlag = true;
				if (display_flag == 1) {
					UART_msg_put("\r\n\033[31mRed LED(1s)\033[0m ");
					display_flag = 0;
				}
			}
			break;
			*/
			// Check if the current mode is REGISTERS
			case(REGISTERS):
			{
				 // The following line is commented out, but if active, it would turn off a red LED flag
				 //redLEDFlag = false;

				 // Check if the display_flag is set
				 if (display_flag == 1) {
						// Send a new line and set the text color to blue
						UART_direct_msg_put("\n\r\033[34m");
						
						// Print the register values
						print_registers();
						
						// Reset the text color to default and send a new line
						UART_direct_msg_put("\033[0m\n\r");
						
						// Reset the display_flag
						display_flag = 0;
				 }
			}
			break;  // End of REGISTERS case

			// Check if the current mode is MEMORY
			case(MEMORY):
			{
				 // The following line is commented out, but if active, it would turn off a red LED flag
				 //redLEDFlag = false;

				 // Check if the display_flag is set
				 if (display_flag == 1) {
						// Send a new line and set the text color to red
						UART_direct_msg_put("\n\r\033[31m");
						
						// Dump the memory values
						dump_memory();
						
						// Reset the text color to default and send a new line
						UART_direct_msg_put("\033[0m\n\r");
						
						// Reset the display_flag
						display_flag = 0;
				 }
			}
			break;  // End of MEMORY case

			// Check if the current mode is STACK
			case(STACK):
			{
				 // The following line is commented out, but if active, it would turn off a red LED flag
				 //redLEDFlag = false;

				 // Check if the display_flag is set
				 if (display_flag == 1) {
						// Send a new line and set the text color to cyan
						UART_direct_msg_put("\n\r\033[36m");
						
						// Display the last 16 words of the stack
						display_last_16_stack_words();
						
						// Reset the text color to default and send a new line
						UART_direct_msg_put("\033[0m\n\r");
						
						// Reset the display_flag
						display_flag = 0;
				 }
			}
			break;  // End of STACK case


      default:
      {
         UART_msg_put("Mode Error");
      }  
   }
}  
