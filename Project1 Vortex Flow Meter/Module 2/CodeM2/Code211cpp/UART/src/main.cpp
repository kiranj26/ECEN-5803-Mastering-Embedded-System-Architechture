/*----------------------------------------------------------------------------
LAB EXERCISE 11.2 - UART interface
SERIAL COMMUNICATION
 ----------------------------------------
	Print text to the PC via UART protocol
	
	Input: None
	Output: PC

	GOOD LUCK!
 *----------------------------------------------------------------------------*/
/*****************************************************************************
* Copyright (C) 2023 by Kiran Jojare & Viraj Patel
* 
* Redistribution, modification, or use of this software in source or binary
* forms is permitted as long as the files maintain this copyright. Users are
* permitted to modify this and use it to learn about the field of embedded
* software. Kiran Jojare & Viraj Patel and the University of Colorado are not 
* liable for any misuse of this material.
* 
*****************************************************************************/

/**
* @file_name    main.cpp
* @introduction Describes the functionality of the software, which is to print
*               text to the PC via UART protocol for learning purposes.
*
* @author       Kiran Jojare & Viraj Patel
* @date         Oct 1 2023
* @version      1.0
*/
#include "mbed.h"
#include "pindef.h"

// Serial tx, rx connected to the PC via an USB cable
Serial device(UART_TX, UART_RX);

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
  /*
  Set the baudrate to 9600 bps
  Print "Hello mbed" to the PC serial monitor
  */
	
  //Write your code here
	// Configuring the Serial object with a baud rate of 9600 bps.
	device.baud(9600);
  
  // Sending the string "Hello mbed" 
  device.printf("Hello mbed\r\n");
  
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
