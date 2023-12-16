/**
 * \file adc.cpp
 * \author Kiran Jojare, Viraj Patel
 * \brief ADC and temperature measurement for STM32F401xE.
 */

#include "adc.h"
#include <math.h>
#include "stm32f401xe.h"
#include "mbed.h"

/// Global variable to store the calculated frequency
float Frequency = 0;

/// ADC channel for internal voltage reference
AnalogIn VREFINT(PA_0);
/// ADC channel for measuring vortex frequency
AnalogIn Vortex_Frequency(PA_1);
/// ADC channel for the on-chip temperature sensor
AnalogIn TempSensor(PA_4);

/// Hardcoded statically allocated array of ADC samples obtained from professor
/// Mirrors the data from ECEN5803Data14.txt
unsigned short ADC_SAMPLES[] = {
	0x7FFF, 0x8404, 0x8808, 0x8C0B, 0x900A, 0x9405, 0x97FB, 0x9BEB, 0x9FD4, 0xA3B5, 0xA78D, 0xAB5B, 0xAF1E, 0xB2D5, 0xB67F, 0xBA1B, 0xBDA9, 0xC127, 0xC495, 0xC7F1, 0xCB3B, 0xCE72, 0xD196, 0xD4A5, 0xD79E, 0xDA81, 0xDD4D, 0xE002, 0xE29F, 0xE522, 0xE78C, 0xE9DC, 0xEC12, 0xEE2B, 0xF029, 0xF20B, 0xF3D0, 0xF578, 0xF701, 0xF86D, 0xF9BB, 0xFAE9, 0xFBF9, 0xFCE9, 0xFDBA, 0xFE6B, 0xFEFC, 0xFF6D, 0xFFBE, 0xFFEE, 0xFFFF, 0xFFEE, 0xFFBE, 0xFF6D, 0xFEFC, 0xFE6B, 0xFDBA, 0xFCE9, 0xFBF9, 0xFAE9, 0xF9BB, 0xF86D, 0xF701, 0xF578, 0xF3D0, 0xF20B, 0xF029, 0xEE2B, 0xEC12, 0xE9DC, 0xE78C, 0xE522, 0xE29F, 0xE002, 0xDD4D, 0xDA81, 0xD79E, 0xD4A5, 0xD196, 0xCE72, 0xCB3B, 0xC7F1, 0xC495, 0xC127, 0xBDA9, 0xBA1B, 0xB67F, 0xB2D5, 0xAF1E, 0xAB5B, 0xA78D, 0xA3B5, 0x9FD4, 0x9BEB, 0x97FB, 0x9405, 0x900A, 0x8C0B, 0x8808, 0x8404, 
	0x7FFF, 0x7BFA, 0x77F6, 0x73F3, 0x6FF4, 0x6BF9, 0x6803, 0x6413, 0x602A, 0x5C49, 0x5871, 0x54A3, 0x50E0, 0x4D29, 0x497F, 0x45E3, 0x4255, 0x3ED7, 0x3B69, 0x380D, 0x34C3, 0x318C, 0x2E68, 0x2B59, 0x2860, 0x257D, 0x22B1, 0x1FFC, 0x1D5F, 0x1ADC, 0x1872, 0x1622, 0x13EC, 0x11D3, 0x0FD5, 0x0DF3, 0x0C2E, 0x0A86, 0x08FD, 0x0791, 0x0643, 0x0515, 0x0405, 0x0315, 0x0244, 0x0193, 0x0102, 0x0091, 0x0040, 0x0010, 0x0000, 0x0010, 0x0040, 0x0091, 0x0102, 0x0193, 0x0244, 0x0315, 0x0405, 0x0515, 0x0643, 0x0791, 0x08FD, 0x0A86, 0x0C2E, 0x0DF3, 0x0FD5, 0x11D3, 0x13EC, 0x1622, 0x1872, 0x1ADC, 0x1D5F, 0x1FFC, 0x22B1, 0x257D, 0x2860, 0x2B59, 0x2E68, 0x318C, 0x34C3, 0x380D, 0x3B69, 0x3ED7, 0x4255, 0x45E3, 0x497F, 0x4D29, 0x50E0, 0x54A3, 0x5871, 0x5C49, 0x602A, 0x6413, 0x6803, 0x6BF9, 0x6FF4, 0x73F3, 0x77F6, 0x7BFA, 
	0x7FFF, 0x8404, 0x8808, 0x8C0B, 0x900A, 0x9405, 0x97FB, 0x9BEB, 0x9FD4, 0xA3B5, 0xA78D, 0xAB5B, 0xAF1E, 0xB2D5, 0xB67F, 0xBA1B, 0xBDA9, 0xC127, 0xC495, 0xC7F1, 0xCB3B, 0xCE72, 0xD196, 0xD4A5, 0xD79E, 0xDA81, 0xDD4D, 0xE002, 0xE29F, 0xE522, 0xE78C, 0xE9DC, 0xEC12, 0xEE2B, 0xF029, 0xF20B, 0xF3D0, 0xF578, 0xF701, 0xF86D, 0xF9BB, 0xFAE9, 0xFBF9, 0xFCE9, 0xFDBA, 0xFE6B, 0xFEFC, 0xFF6D, 0xFFBE, 0xFFEE, 0xFFFF, 0xFFEE, 0xFFBE, 0xFF6D, 0xFEFC, 0xFE6B, 0xFDBA, 0xFCE9, 0xFBF9, 0xFAE9, 0xF9BB, 0xF86D, 0xF701, 0xF578, 0xF3D0, 0xF20B, 0xF029, 0xEE2B, 0xEC12, 0xE9DC, 0xE78C, 0xE522, 0xE29F, 0xE002, 0xDD4D, 0xDA81, 0xD79E, 0xD4A5, 0xD196, 0xCE72, 0xCB3B, 0xC7F1, 0xC495, 0xC127, 0xBDA9, 0xBA1B, 0xB67F, 0xB2D5, 0xAF1E, 0xAB5B, 0xA78D, 0xA3B5, 0x9FD4, 0x9BEB, 0x97FB, 0x9405, 0x900A, 0x8C0B, 0x8808, 0x8404, 
	0x7FFF, 0x7BFA, 0x77F6, 0x73F3, 0x6FF4, 0x6BF9, 0x6803, 0x6413, 0x602A, 0x5C49, 0x5871, 0x54A3, 0x50E0, 0x4D29, 0x497F, 0x45E3, 0x4255, 0x3ED7, 0x3B69, 0x380D, 0x34C3, 0x318C, 0x2E68, 0x2B59, 0x2860, 0x257D, 0x22B1, 0x1FFC, 0x1D5F, 0x1ADC, 0x1872, 0x1622, 0x13EC, 0x11D3, 0x0FD5, 0x0DF3, 0x0C2E, 0x0A86, 0x08FD, 0x0791, 0x0643, 0x0515, 0x0405, 0x0315, 0x0244, 0x0193, 0x0102, 0x0091, 0x0040, 0x0010, 0x0000, 0x0010, 0x0040, 0x0091, 0x0102, 0x0193, 0x0244, 0x0315, 0x0405, 0x0515, 0x0643, 0x0791, 0x08FD, 0x0A86, 0x0C2E, 0x0DF3, 0x0FD5, 0x11D3, 0x13EC, 0x1622, 0x1872, 0x1ADC, 0x1D5F, 0x1FFC, 0x22B1, 0x257D, 0x2860, 0x2B59, 0x2E68, 0x318C, 0x34C3, 0x380D, 0x3B69, 0x3ED7, 0x4255, 0x45E3, 0x497F, 0x4D29, 0x50E0, 0x54A3, 0x5871, 0x5C49, 0x602A, 0x6413, 0x6803, 0x6BF9, 0x6FF4, 0x73F3, 0x77F6, 0x7BFA, 
	0x7FFF, 0x8404, 0x8808, 0x8C0B, 0x900A, 0x9405, 0x97FB, 0x9BEB, 0x9FD4, 0xA3B5, 0xA78D, 0xAB5B, 0xAF1E, 0xB2D5, 0xB67F, 0xBA1B, 0xBDA9, 0xC127, 0xC495, 0xC7F1, 0xCB3B, 0xCE72, 0xD196, 0xD4A5, 0xD79E, 0xDA81, 0xDD4D, 0xE002, 0xE29F, 0xE522, 0xE78C, 0xE9DC, 0xEC12, 0xEE2B, 0xF029, 0xF20B, 0xF3D0, 0xF578, 0xF701, 0xF86D, 0xF9BB, 0xFAE9, 0xFBF9, 0xFCE9, 0xFDBA, 0xFE6B, 0xFEFC, 0xFF6D, 0xFFBE, 0xFFEE, 0xFFFF, 0xFFEE, 0xFFBE, 0xFF6D, 0xFEFC, 0xFE6B, 0xFDBA, 0xFCE9, 0xFBF9, 0xFAE9, 0xF9BB, 0xF86D, 0xF701, 0xF578, 0xF3D0, 0xF20B, 0xF029, 0xEE2B, 0xEC12, 0xE9DC, 0xE78C, 0xE522, 0xE29F, 0xE002, 0xDD4D, 0xDA81, 0xD79E, 0xD4A5, 0xD196, 0xCE72, 0xCB3B, 0xC7F1, 0xC495, 0xC127, 0xBDA9, 0xBA1B, 0xB67F, 0xB2D5, 0xAF1E, 0xAB5B, 0xA78D, 0xA3B5, 0x9FD4, 0x9BEB, 0x97FB, 0x9405, 0x900A, 0x8C0B, 0x8808, 0x8404, 
	0x7FFF, 0x7BFA, 0x77F6, 0x73F3, 0x6FF4, 0x6BF9, 0x6803, 0x6413, 0x602A, 0x5C49, 0x5871, 0x54A3, 0x50E0, 0x4D29, 0x497F, 0x45E3, 0x4255, 0x3ED7, 0x3B69, 0x380D, 0x34C3, 0x318C, 0x2E68, 0x2B59, 0x2860, 0x257D, 0x22B1, 0x1FFC, 0x1D5F, 0x1ADC, 0x1872, 0x1622, 0x13EC, 0x11D3, 0x0FD5, 0x0DF3, 0x0C2E, 0x0A86, 0x08FD, 0x0791, 0x0643, 0x0515, 0x0405, 0x0315, 0x0244, 0x0193, 0x0102, 0x0091, 0x0040, 0x0010, 0x0000, 0x0010, 0x0040, 0x0091, 0x0102, 0x0193, 0x0244, 0x0315, 0x0405, 0x0515, 0x0643, 0x0791, 0x08FD, 0x0A86, 0x0C2E, 0x0DF3, 0x0FD5, 0x11D3, 0x13EC, 0x1622, 0x1872, 0x1ADC, 0x1D5F, 0x1FFC, 0x22B1, 0x257D, 0x2860, 0x2B59, 0x2E68, 0x318C, 0x34C3, 0x380D, 0x3B69, 0x3ED7, 0x4255, 0x45E3, 0x497F, 0x4D29, 0x50E0, 0x54A3, 0x5871, 0x5C49, 0x602A, 0x6413, 0x6803, 0x6BF9, 0x6FF4, 0x73F3, 0x77F6, 0x7BFA, 
	0x7FFF, 0x8404, 0x8808, 0x8C0B, 0x900A, 0x9405, 0x97FB, 0x9BEB, 0x9FD4, 0xA3B5, 0xA78D, 0xAB5B, 0xAF1E, 0xB2D5, 0xB67F, 0xBA1B, 0xBDA9, 0xC127, 0xC495, 0xC7F1, 0xCB3B, 0xCE72, 0xD196, 0xD4A5, 0xD79E, 0xDA81, 0xDD4D, 0xE002, 0xE29F, 0xE522, 0xE78C, 0xE9DC, 0xEC12, 0xEE2B, 0xF029, 0xF20B, 0xF3D0, 0xF578, 0xF701, 0xF86D, 0xF9BB, 0xFAE9, 0xFBF9, 0xFCE9, 0xFDBA, 0xFE6B, 0xFEFC, 0xFF6D, 0xFFBE, 0xFFEE, 0xFFFF, 0xFFEE, 0xFFBE, 0xFF6D, 0xFEFC, 0xFE6B, 0xFDBA, 0xFCE9, 0xFBF9, 0xFAE9, 0xF9BB, 0xF86D, 0xF701, 0xF578, 0xF3D0, 0xF20B, 0xF029, 0xEE2B, 0xEC12, 0xE9DC, 0xE78C, 0xE522, 0xE29F, 0xE002, 0xDD4D, 0xDA81, 0xD79E, 0xD4A5, 0xD196, 0xCE72, 0xCB3B, 0xC7F1, 0xC495, 0xC127, 0xBDA9, 0xBA1B, 0xB67F, 0xB2D5, 0xAF1E, 0xAB5B, 0xA78D, 0xA3B5, 0x9FD4, 0x9BEB, 0x97FB, 0x9405, 0x900A, 0x8C0B, 0x8808, 0x8404, 
	0x7FFF, 0x7BFA, 0x77F6, 0x73F3, 0x6FF4, 0x6BF9, 0x6803, 0x6413, 0x602A, 0x5C49, 0x5871, 0x54A3, 0x50E0, 0x4D29, 0x497F, 0x45E3, 0x4255, 0x3ED7, 0x3B69, 0x380D, 0x34C3, 0x318C, 0x2E68, 0x2B59, 0x2860, 0x257D, 0x22B1, 0x1FFC, 0x1D5F, 0x1ADC, 0x1872, 0x1622, 0x13EC, 0x11D3, 0x0FD5, 0x0DF3, 0x0C2E, 0x0A86, 0x08FD, 0x0791, 0x0643, 0x0515, 0x0405, 0x0315, 0x0244, 0x0193, 0x0102, 0x0091, 0x0040, 0x0010, 0x0000, 0x0010, 0x0040, 0x0091, 0x0102, 0x0193, 0x0244, 0x0315, 0x0405, 0x0515, 0x0643, 0x0791, 0x08FD, 0x0A86, 0x0C2E, 0x0DF3, 0x0FD5, 0x11D3, 0x13EC, 0x1622, 0x1872, 0x1ADC, 0x1D5F, 0x1FFC, 0x22B1, 0x257D, 0x2860, 0x2B59, 0x2E68, 0x318C, 0x34C3, 0x380D, 0x3B69, 0x3ED7, 0x4255, 0x45E3, 0x497F, 0x4D29, 0x50E0, 0x54A3, 0x5871, 0x5C49, 0x602A, 0x6413, 0x6803, 0x6BF9, 0x6FF4, 0x73F3, 0x77F6, 0x7BFA, 
	0x7FFF, 0x8404, 0x8808, 0x8C0B, 0x900A, 0x9405, 0x97FB, 0x9BEB, 0x9FD4, 0xA3B5, 0xA78D, 0xAB5B, 0xAF1E, 0xB2D5, 0xB67F, 0xBA1B, 0xBDA9, 0xC127, 0xC495, 0xC7F1, 0xCB3B, 0xCE72, 0xD196, 0xD4A5, 0xD79E, 0xDA81, 0xDD4D, 0xE002, 0xE29F, 0xE522, 0xE78C, 0xE9DC, 0xEC12, 0xEE2B, 0xF029, 0xF20B, 0xF3D0, 0xF578, 0xF701, 0xF86D, 0xF9BB, 0xFAE9, 0xFBF9, 0xFCE9, 0xFDBA, 0xFE6B, 0xFEFC, 0xFF6D, 0xFFBE, 0xFFEE, 0xFFFF, 0xFFEE, 0xFFBE, 0xFF6D, 0xFEFC, 0xFE6B, 0xFDBA, 0xFCE9, 0xFBF9, 0xFAE9, 0xF9BB, 0xF86D, 0xF701, 0xF578, 0xF3D0, 0xF20B, 0xF029, 0xEE2B, 0xEC12, 0xE9DC, 0xE78C, 0xE522, 0xE29F, 0xE002, 0xDD4D, 0xDA81, 0xD79E, 0xD4A5, 0xD196, 0xCE72, 0xCB3B, 0xC7F1, 0xC495, 0xC127, 0xBDA9, 0xBA1B, 0xB67F, 0xB2D5, 0xAF1E, 0xAB5B, 0xA78D, 0xA3B5, 0x9FD4, 0x9BEB, 0x97FB, 0x9405, 0x900A, 0x8C0B, 0x8808, 0x8404, 
	0x7FFF, 0x7BFA, 0x77F6, 0x73F3, 0x6FF4, 0x6BF9, 0x6803, 0x6413, 0x602A, 0x5C49, 0x5871, 0x54A3, 0x50E0, 0x4D29, 0x497F, 0x45E3, 0x4255, 0x3ED7, 0x3B69, 0x380D, 0x34C3, 0x318C, 0x2E68, 0x2B59, 0x2860, 0x257D, 0x22B1, 0x1FFC, 0x1D5F, 0x1ADC, 0x1872, 0x1622, 0x13EC, 0x11D3, 0x0FD5, 0x0DF3, 0x0C2E, 0x0A86, 0x08FD, 0x0791, 0x0643, 0x0515, 0x0405, 0x0315, 0x0244, 0x0193, 0x0102, 0x0091, 0x0040, 0x0010, 0x0000, 0x0010, 0x0040, 0x0091, 0x0102, 0x0193, 0x0244, 0x0315, 0x0405, 0x0515, 0x0643, 0x0791, 0x08FD, 0x0A86, 0x0C2E, 0x0DF3, 0x0FD5, 0x11D3, 0x13EC, 0x1622, 0x1872, 0x1ADC, 0x1D5F, 0x1FFC, 0x22B1, 0x257D, 0x2860, 0x2B59, 0x2E68, 0x318C, 0x34C3, 0x380D, 0x3B69, 0x3ED7, 0x4255, 0x45E3, 0x497F, 0x4D29, 0x50E0, 0x54A3, 0x5871, 0x5C49, 0x602A, 0x6413, 0x6803, 0x6BF9, 0x6FF4, 0x73F3, 0x77F6, 0x7BFA
};
/**
 * \brief Read ADC samples and compute the frequency based on zero crossing.
 *
 * The function counts the number of zero crossings in the provided samples and calculates 
 * the frequency based on the sample time and the number of samples.
 */
void readADC(void){
	int count = 0; // Counter to track zero crossings
	for(int i=0; i<SAMPLES; i++) {
		if (ADC_SAMPLES[i] == ZERO_CROSSING_LEVEL) {
			count++; // Increment count on zero crossing
		}
	}
	Frequency = count / (SAMPLES * SAMPLE_TIME * 2);
}

/**
 * \brief Custom configuration for the ADC module.
 *
 * The function sets up the ADC for continuous conversion mode and configures it 
 * to measure from the on-chip temperature sensor. It also sets the sampling time 
 * and starts the ADC conversion.
 */
void ADC_Custom_Config(void) {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // Enable the ADC1 clock

    ADC1->CR1 = 0;                      
    ADC1->CR1 |= ADC_CR1_SCAN;          // Enable scan mode for multiple channels

    ADC1->CR2 = 0;                      
    ADC1->CR2 |= ADC_CR2_ADON |         // Turn the ADC on
                 ADC_CR2_CONT;          // Set to continuous conversion mode

    ADC1->SQR1 = 0;                     
    ADC1->SQR3 = ADC_CHANNEL_TEMPSENSOR; // Set to use the on-chip temperature sensor channel

    ADC1->SMPR1 |= ADC_SMPR1_SMP16_2 | ADC_SMPR1_SMP16_1; // Set sampling time to 144+12 cycles

    ADC->CCR |= ADC_CCR_TSVREFE;  // Enable the temperature sensor and voltage reference buffer

    ADC1->CR2 |= ADC_CR2_SWSTART; // Start the ADC conversion
}

/**
 * \brief Read the on-chip temperature sensor and return the temperature value.
 * 
 * \return The calculated temperature based on the ADC reading and the STM32 reference manual formula.
 */
float readTemperature(void) {
    ADC1->CR2 |= ADC_CR2_SWSTART;                  // Start ADC conversion
    while(!(ADC1->SR & ADC_SR_EOC));               // Wait until the conversion is complete
    uint16_t adcValue = ADC1->DR;                  // Get the ADC result

    float voltage = (adcValue * 3.3) / 4095.0;     // Convert the ADC reading to a voltage value
    float temperature = ((voltage - ADC_V25) / ADC_AVG_SLOPE) + 25.0; // Convert voltage to temperature
    return temperature;
}