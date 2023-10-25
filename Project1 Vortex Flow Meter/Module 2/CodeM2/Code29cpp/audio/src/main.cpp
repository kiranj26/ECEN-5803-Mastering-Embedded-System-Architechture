/*----------------------------------------------------------------------------
LAB EXERCISE 9 - Analog input and PWM
 ----------------------------------------
	Use two potentiometers to adjust the volume and pitch of the output sound wave.
	
	Inputs: Virtual potentiometers 1 and 2
	Output: Virtual speaker,  Real PC

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
* @introduction This file demonstrates the use of the mbed API for handling
*               analog input and PWM in an ARM-based microcontroller, focusing on
*               adjusting the volume and pitch of the output sound wave using potentiometers.
*
* @author       Kiran Jojare & Viraj Patel
* @date         Oct 1 2023
* @version      1.0
*/
#include "mbed.h"
#include "pindef.h"

/*
Define the PWM speaker output
Define analog inputs
Define serial output
*/

//Write your code here
// Define PWM speaker output, analog inputs, and serial output
PwmOut speaker(PB_10);  		// PWM Speaker Output
AnalogIn potVolume(PA_0);  	// Analog Input for Volume
AnalogIn potPitch(PA_1);   	// Analog Input for Pitch
Serial pc(USBTX, USBRX);  	// Serial Output to PC

//Define variables
float i;

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
/**
 * @brief Main Function
 * @details The main function runs an infinite loop where it reads the values from potentiometers,
 *          adjusts the volume and pitch of the speaker output accordingly, and prints the values to
 *          the PC serial terminal. It generates a saw-tooth sound wave with adjustable period and volume.
 */
int main(){
	while(1){
		/*
		Print values of the potentiometers to the PC serial terminal
		Create a saw-tooth sound wave
		Make the period and volume adjustable using the potentiometers
		*/
		// Read the values from the potentiometers
		float volume = potVolume.read();  // Read Volume level
		float pitch = potPitch.read();    // Read Pitch level
		
		// Calculate frequency based on pitch
		float frequency = 320 + pitch * (8000 - 320);  // Frequency Range: 320Hz to 8000Hz
		
		// Set speaker period based on calculated frequency
		speaker.period(1.0f / frequency);  // Set the period of the PWM signal
		
		// Generate a saw-tooth wave and adjust volume
		for (float i = 0; i < 1; i += 0.05f) {
				speaker.write(i * volume);
		}
		
		// Print the values to the PC serial terminal
		pc.printf("Volume: %f, Pitch: %f, Frequency: %f Hz\r\n", volume, pitch, frequency);
 }
}
// *******************************ARM University Program Copyright © ARM Ltd 2014*************************************
