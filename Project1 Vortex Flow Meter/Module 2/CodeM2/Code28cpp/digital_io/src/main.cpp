/*----------------------------------------------------------------------------
LAB EXERCISE 8.1 - DIGITAL INPUTS AND OUTPUTS
PROGRAMMING USING MBED API
 ----------------------------------------
 In this exercise you need to use the mbed API functions to:
 
	1) Define BusIn, BusOut interfaces for inputs and outputs
	2) The LED is controlled by the button:
			+ USER_BUTTON - LED1
			
	GOOD LUCK!
 *----------------------------------------------------------------------------*/
/*****************************************************************************
* Copyright (C) 2023 by Kiran Jojare & Viraj Patel
* 
* Redistribution, modification or use of this software in source or binary 
* forms is permitted as long as the files maintain this copyright. Users are  
* permitted to modify this and use it to learn about the field of embedded 
* software. Kiran Jojare & Viraj Patel and the University of Colorado are not 
* liable for any misuse of this material.  
* 
*****************************************************************************/

/**
* @file_name    main.cpp
* @introduction This file illustrates the use of digital inputs and outputs 
*               using the mbed API in an ARM-based microcontroller, focusing 
*               on interfacing and controlling LEDs with buttons.
* 
* @author       Kiran Jojare, Viraj Patel
* @date         Sep 30 2023 
* @version      1.0 
*/

#include "mbed.h"

// Define input bus
BusIn buttons(PB_4, PB_5, PB_3, PA_10); // Define a bus of input pins connected to buttons.

// Define output bus for the LED
BusOut leds(LED2, PA_9); 								// Define a bus of output pins connected to LEDs.

/**
 * @brief Main function initializes LEDs and implements the main program loop.
 * @details In the infinite while loop, the program continuously checks the state of the buttons 
 *          and turns on/off corresponding LEDs based on the button pressed.
 */
int main(){
    leds = 0x00; // Initialize LEDs to OFF
    
    while(1) {
        // Check the state of buttons and actuate corresponding LEDs.
        
        // if PA_10 is pressed
        if(buttons == 0b00000111) {
            leds = leds | 0b00000001; // Turn internal LED ON
        }
        
        // if PB_3 is pressed
        if(buttons == 0b00001011) { 
            leds = leds & 0b00000000; // Turn internal LED OFF
        }
        
        // if PB_5 is pressed
        if(buttons == 0b00001101) {
            leds = leds | 0b00000010; // Turn external LED ON
        }
        
        // if PB_4 is pressed
        if(buttons == 0b00001110) {
            leds = leds & 0x00; 			// Turn internal LED OFF
        }
    }
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
