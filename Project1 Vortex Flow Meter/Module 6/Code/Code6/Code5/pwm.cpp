/**
 * \file PWM.cpp
 * \author Kiran Jojare, Viraj Patel
 * \brief PWM output configurations and related functions for STM32F401xE.
 * 
 * This file provides functionality to generate PWM signals based on the flow and frequency 
 * calculations from the flow sensing system.
 */

#include "pwm.h"
#include "mbed.h"

PwmOut pulse_420(PC_8);  ///< PWM output pin for 4-20mA signaling.
PwmOut pulse_out(PC_9);  ///< Standard PWM output pin.

extern float flow, Frequency;  ///< Externally defined flow and frequency values.

/**
 * \brief Output a PWM signal based on the flow rate.
 * 
 * Generates a PWM signal with a frequency inversely proportional to the flow 
 * rate (in gallons per second). The duty cycle is set to 50%.
 */
void pulse_420_output(void) {
	if(flow) {
		pulse_420.period(1/(flow/60));    // Convert to Gallons Per Second
		pulse_420.write(0.5);    // Set to 50% Duty Cycle
	}
}

/**
 * \brief Output a PWM signal based on the measured frequency.
 * 
 * Generates a PWM signal with a frequency inversely proportional to the 
 * frequency from the flow sensing system. The duty cycle is set to 50%.
 */
void pulse_output(void) {
	if(Frequency) {
		pulse_out.period(1/Frequency);    // Set period based on the measured frequency
		pulse_out.write(0.5);    // Set to 50% Duty Cycle
	}
}
