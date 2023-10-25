/**
 * \file PWM.h
 * \author Kiran Jojare, Viraj Patel
 * \brief PWM function declarations for STM32F401xE.
 * 
 * This header provides declarations for the PWM signal generation functions.
 */

#ifndef PWM_H
#define PWM_H

/**
 * \brief Output a PWM signal based on the flow rate.
 * 
 * Generates a PWM signal with a frequency inversely proportional to the flow rate 
 * (in gallons per second). The duty cycle is set to 50%.
 */
void pulse_420_output(void);

/**
 * \brief Output a PWM signal based on the measured frequency.
 * 
 * Generates a PWM signal with a frequency inversely proportional to the frequency 
 * from the flow sensing system. The duty cycle is set to 50%.
 */
void pulse_output(void);

#endif // PWM_H
