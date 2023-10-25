/**
 * \file adc.h
 * \author Kiran Jojare, Viraj Patel
 * \brief ADC configurations and function declarations for STM32F401xE.
 */

#ifndef ADC_H
#define ADC_H

/// Defined value for zero crossing level (mid of 16-bit ADC range)
#define ZERO_CROSSING_LEVEL 0x7FFF
/// Number of samples for the readADC function
#define SAMPLES (1000U)
/// Time interval between each ADC sample
#define SAMPLE_TIME (100E-06)
/// Voltage corresponding to ADC value at 25 degrees Celsius (refer to the specific MCU's datasheet)
#define ADC_V25 0.76  
/// Average slope value for temperature calculation based on the ADC reading
#define ADC_AVG_SLOPE 0.0025  

/**
 * \brief Read ADC samples and compute the frequency based on zero crossing.
 *
 * The function counts the number of zero crossings in the provided samples and calculates 
 * the frequency based on the sample time and the number of samples.
 */
void readADC(void);

/**
 * \brief Custom configuration for the ADC module.
 *
 * The function sets up the ADC for continuous conversion mode and configures it 
 * to measure from the on-chip temperature sensor. It also sets the sampling time 
 * and starts the ADC conversion.
 */
void ADC_Custom_Config(void);

/**
 * \brief Read the on-chip temperature sensor and return the temperature value.
 * 
 * \return The calculated temperature based on the ADC reading and the STM32 reference manual formula.
 */
float readTemperature(void);

#endif // ADC_H
