/*----------------------------------------------------------------------------
LAB EXERCISE 11.3 - I2C interface
SERIAL COMMUNICATION
 ----------------------------------------
	Access the virtual temperature sensor via I2C interface, print the current temperature
	to the PC via UART
	
	Input: temperature sensor
	Output: PC
	
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
* @description  This file contains the main code for integration of Project 2 Module 2  
*
* @author       Kiran Jojare & Viraj Patel
* @date         Oct 1 2023
* @version      1.0
*/
#include "mbed.h"
#include "pindef.h"

//I2C interface
I2C temp_sensor(I2C_SDA, I2C_SCL);

// UART interface
Serial pc(UART_TX, UART_RX);

//I2C address of temperature sensor DS1631
const int temp_addr = 0x90;

// Array storing the Start Convert T command and the Read Temperature command.
char cmd[] = {0x51, 0xAA};

// Array to store the 16-bit temperature data read from the sensor.
char read_temp[2];

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	// Set the baud rate for serial communication
	pc.baud(9600);
	
	while(1){
		/*
		Write the Start Convert T command to the sensor
		Write the Read Temperature command to the sensor
		Read the 16-bit temperature data
		*/
		
		//Write your code here
		// Send the Start Convert T command to the sensor.
		temp_sensor.write(temp_addr, &cmd[0], 1);

		// Short delay to give sensor time to process the command and start conversion
		wait_ms(10);

		// Send the Read Temperature command to the sensor.
		temp_sensor.write(temp_addr, &cmd[1], 1);

		// Read the 16-bit temperature data from the sensor
		temp_sensor.read(temp_addr, read_temp, 2);
		
		//Convert temperature to Celsius
		float temp = (float((read_temp[0] << 8) | read_temp[1]) / 256);
		
		//Print temperature to the serial monitor
		
		//Write your code here
		// Print the calculated temperature to the serial monitor.
		pc.printf("Temperature: %.2f Celsius\r\n", temp);

		// Delay to avoid overwhelming output.
		wait_ms(1000);
		
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
