/**----------------------------------------------------------------------------
 
   \file main.cpp

--                                                                           --
--              ECEN 5803 Mastering Embedded System Architecture             --
--                  Project 1 Module 4                                       --
--                Microcontroller Firmware                                   --
--                      main.cpp                                            --
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
-- Functional Description:  Main code file generated by mbed, and then
--                           modified to implement a super loop bare metal OS.
--
--      Copyright (c) 2015, 2016, 2022 Tim Scherr  All rights reserved.
--
*/

#define MAIN
#include "shared.h"
#undef MAIN

#include "NHD_0216HZ.h"
//#include "DS1631.h"
#include "pindef.h"

#include "adc.h"
#include "flow.h"
#include "pwm.h"

// Define green LED pin
DigitalOut greenLED(LED2);

// LCD setup using SPI communication.
NHD_0216HZ lcd(SPI_CS, SPI_MOSI, SPI_SCLK);

extern volatile uint16_t SwTimerIsrCounter; 
extern float Frequency, flow, temperature;

Ticker tick;          //  Creates a timer interrupt using mbed methods

 /****************      ECEN 5803 add code as indicated   ***************/
   // Add code to control LED LD2 here, 
   // including a function to flip the LED state on and off
	 
void flip(void) {
    greenLED = !greenLED;  // Toggle the state of the green LED
}


// Set up serial communication over USB
Serial pc(USBTX, USBRX);

// Create timer instance
//Timer custom_timer2; 

 


/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main() 
{
	//custom_timer2.start();
	pc.baud(9600);
	
	// Initialize the LCD
	lcd.init_lcd();    // Initialize the LCD display.
	lcd.clr_lcd();     // Clear the LCD.
	
	// ADC channels are initialized using AnalogIn
  // Custom config for ADC
  ADC_Custom_Config();
	
/****************      ECEN 5803 add code as indicated   **********************/
               //  Add code to call timer0 function every 100 uS
	tick.attach_us(&timer0, 100);

 // Print the initial banner
    pc.printf("\r\nHello World!\n\n\r");
    uint32_t  count = 0;   


// initialize serial buffer pointers
   rx_in_ptr =  rx_buf; /* pointer to the receive in data */
   rx_out_ptr = rx_buf; /* pointer to the receive out data*/
   tx_in_ptr =  tx_buf; /* pointer to the transmit in data*/
   tx_out_ptr = tx_buf; /* pointer to the transmit out */	
   

/****************      ECEN 5803 add code as indicated   **********************/
    // uncomment this section after adding monitor code.  
   /* send a starting message to the terminal  */                    
	 pc.printf("\n\r\n\r***** Project 1 Module 6 - Viraj_Kiran *****\n\r\n\r");
   UART_direct_msg_put("\r\nSystem Reset\r\nCode ver. ");
   UART_direct_msg_put( CODE_VERSION );
   UART_direct_msg_put("\r\n");
   UART_direct_msg_put( COPYRIGHT );
   UART_direct_msg_put("\r\n");

   set_display_mode();                                      
   
	 //custom_timer2.stop();
   	
    while(1)       /// Cyclical Executive Loop
    {

        count++;               // counts the number of times through the loop
//      __enable_interrupts();
//      __clear_watchdog_timer();

/****************      ECEN 5803 add code as indicated   **********************/
    // uncomment this section after you add the monitor code. 
    
        serial();            // Polls the serial port
        chk_UART_msg();     // checks for a serial port message received
        monitor();           // Sends serial port output messages depending
                         //     on commands received and display mode

   /****************      ECEN 5803 add code as indicated   ***************/
  // Read temperature sensor readings from internal temperature sensor
  readADC();
	//pc.printf("Freq: %f\n\r", Frequency);

	// Calculate flow from obtained internal temperature sensor readings
  calculate_flow();

//  4-20 output ()    // use PWM1 channel 1  proportional rate to flow
  pulse_420_output();

//  Pulse output()   // use PWM1 channel 2  propotional pulse rate to frequency
  pulse_output();

//  LCD_Display()   // use the SPI port to send flow number
	lcd.set_cursor(0, 0);
	lcd.printf("Flow: %.2f ", flow);
	//lcd.printf("T: %.1f ", temperature);
	//lcd.set_cursor(0, 1);
	//lcd.printf("Fr: %.1f ", Frequency);

//  Write your code here for any additional tasks
		//pc.printf("Temp::: %.f\n\r", readTemperature());


//  End ECEN 5803 code addition




        if ((SwTimerIsrCounter & 0x1FFF) > 0x0FFF)  
/****************      ECEN 5803 add code as indicated   **********************/
         /// Add comment explaining what the timer statement above does
        {
            flip();  // Toggle Green LED
        }

    }   /// End while(1) loop

}

  