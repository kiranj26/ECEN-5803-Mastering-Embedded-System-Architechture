/*----------------------------------------------------------------------------
LAB EXERCISE 11.1 - SPI interface
SERIAL COMMUNICATION
 ----------------------------------------
 Interface the LCD display using SPI protocol: display four checks (size 10x10
 pixels) at four corners of the LCD.
 
 Input: None
 Output: LCD display
	
	GOOD LUCK!
 *----------------------------------------------------------------------------*/
/*****************************************************************************
* Copyright (C) 2023 by Kiran Jojare & Viraj Patel
* 
* This code snippet is provided with permission for redistribution, modification, 
* or use in source or binary forms, with the condition that all the files maintain 
* this copyright notice. This is primarily intended for educational purposes,
* allowing users to learn about embedded software development.
* Kiran Jojare, Viraj Patel, and the University of Colorado disclaim liability 
* for any misuse of this material.
* 
*****************************************************************************/

/**
* @file_name    main.cpp
* @introduction This file serves as the main entry point for the program and contains 
*               the logic to initialize SPI and LCD and print messages on the LCD.
*
* @author       Kiran Jojare & Viraj Patel
* @date         Oct 1 2023
* @version      1.0
*/
#include "NHD_0216HZ.h"

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main() {
	// Initializes the SPI interface.
  init_spi(); 
  
  // Initializes the LCD display.
  init_lcd(); 
    
  // Printing the string "Do you even" to the LCD.
  print_lcd("Do you even"); 
  
  // Moving the cursor to the second line of the LCD.
	set_cursor(0,1); 
	
  // Printing another string "mbed, bro?" to the LCD.
	print_lcd("mbed, bro?");
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
