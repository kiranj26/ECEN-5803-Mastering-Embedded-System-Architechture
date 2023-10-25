/*----------------------------------------------------------------------------
LAB EXERCISE 8.2 - INTERRUPT IN/OUT
PROGRAMMING USING MBED API
 ----------------------------------------
 In this exercise you need to use the mbed API functions to:
 
	1) Define InterruptIn and ISR for the button press
	2) In the interrupt service routine, the LED is used to indicate when a
	button was pressed:
			+ USER_BUTTON - LED1

	3) Put the processor into sleep mode upon exiting from the ISR
			
	GOOD LUCK!
 *----------------------------------------------------------------------------*/
 
/*****************************************************************************
* Copyright (C) 2023 by Kiran Jojare & Viraj Patel
* 
* Redistribution, modification or use of this software in source or binary 
* forms is permitted as long as the files maintain this copyright. Users are  
* permitted to modify this and use it to learn about the field of embedded 
* software. Kiran Jojare & Viraj Patel and the University of Colorado are not liable for  
* any misuse of this material.  
* 
*****************************************************************************/

/**
* @file_name    main.cpp
* @introduction This file demonstrates the use of the mbed API for handling 
*               digital inputs and outputs using interrupts in an ARM-based 
*               microcontroller, focusing on controlling LEDs with button presses.
*               -- Note -- : This implementation is using rising interrupt 
*                            Falling edge based interrupt implementation is commented out
*
* @author       Kiran Jojare & Viraj Patel
* @date         Sep 30 2023 
* @version      1.0 
*/

#include "mbed.h"

// Define BusOut for LEDs to control them as per button interrupts
BusOut leds(LED2, PA_9);

// Define InterruptIn objects for each button to handle interrupts
InterruptIn btnInternalOn(PA_10);  // Internal ON button
InterruptIn btnInternalOff(PB_3);  // Internal OFF button
InterruptIn btnExternalOn(PB_5);   // External ON button
InterruptIn btnExternalOff(PB_4);  // External OFF button


// Define ISRs for the interrupts
// ISR to handle Internal LED On button press
/**
 * @brief Handle Internal LED On button press.
 * @details This ISR sets the bit corresponding to the internal LED to 1 (ON) 
 * when the button is pressed.
 */
void handleInternalOn() {
    leds = leds | 0b00000001; // Turn internal LED ON
}

/**
 * @brief Handle Internal LED Off button press.
 * @details This ISR resets all bits to 0 (OFF) when the button is pressed.
 */
void handleInternalOff() {
    leds = leds & 0b00000000; // Turn internal LED OFF
}

/**
 * @brief Handle External LED On button press.
 * @details This ISR sets the bit corresponding to the external LED to 1 (ON) 
 * when the button is pressed.
 */
void handleExternalOn() {
    leds = leds | 0b00000010; // Turn external LED ON
}

/**
 * @brief Handle External LED Off button press.
 * @details This ISR resets all bits to 0 (OFF) when the button is pressed.
 */
void handleExternalOff() {
    leds = leds & 0x00; // Turn external LED OFF
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
/**
 * @brief Main Function.
 * @details The main function initializes the LEDs, enables global interrupts,
 *          and attaches the address of the ISR to the rising edge of the button's signal.
 *          It then enters an infinite while loop where the processor is put to sleep
 *          and waits for an interrupt to occur.
 */

int main(){
	
	__enable_irq();			//enable interrupts
	
	//initially turn off  LED
	//Write your code here
	leds = 0x00; // Initialize LEDs to OFF

	//Interrupt handlers
	//Attach the address of the ISR to the rising edge

	// Attach the address of the ISR to the rising edge of the button's signal
	btnInternalOn.rise(&handleInternalOn);
	btnInternalOff.rise(&handleInternalOff);
	btnExternalOn.rise(&handleExternalOn);
	btnExternalOff.rise(&handleExternalOff);
	
	// Commented out the falling edge interrupt calls ans was also tested
	
  // btnInternalOn.fall(&handleInternalOn);
	// btnInternalOff.fall(&handleInternalOff);
	// btnExternalOn.fall(&handleExternalOn);
	// btnExternalOff.fall(&handleExternalOff);
	
	//Sleep on exit
	// The main thread remains in sleep mode, waiting for interrupts to wake it up
	while(1) {
			__wfi();  // Enter sleep mode and wait for an interrupt to occur
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
