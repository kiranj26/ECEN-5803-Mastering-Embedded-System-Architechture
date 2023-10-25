/**
 * \file flow.cpp
 * \author Kiran Jojare, Viraj Patel
 * \brief Implements flow calculation based on temperature and ADC readings for STM32F401xE.
 */

#include "flow.h"
#include <math.h>
#include "adc.h"

float velocity = 10;          ///< Initial velocity value.
float flow;                   ///< Calculated flow value.
float temperature;            ///< Temperature in Celsius.
extern float Frequency;       ///< External reference to frequency calculated from ADC readings.

/**
 * \brief Calculates the fluid flow based on temperature, density, and viscosity.
 *
 * The function reads the temperature and based on it calculates the fluid's density 
 * and viscosity. Using these values and the Reynold's number, it computes the 
 * Strouhal number and uses it to adjust the velocity. Finally, it calculates 
 * and sets the flow rate.
 */
void calculate_flow(void) {
    temperature = readTemperature();  // Read the temperature in Celsius.

    // Compute the fluid density, rho, based on temperature.
    float rho = 1000 * (1 - ((temperature + 288.9414) / (508929.2 * (temperature + 68.12963))) 
                * pow((temperature - 3.9863), 2));

    // Compute the fluid's viscosity using the Sutherland formula.
    float T_kelvin = temperature + 273.15;
    float viscosity = 2.4e-5 * pow(10, (247.8 / (T_kelvin - 140.0)));

    // Compute the Reynold's number.
    float Re = (rho * velocity * PID_METER) / viscosity;

    // Compute the Strouhal number based on Reynold's number.
    float St = 0.2684 - 1.0356 / sqrt(Re);

    // Adjust velocity based on Strouhal number and frequency.
    velocity = (Frequency * D) / St;

    // Calculate the flow rate.
    flow = 2.45 * pow(PID_INCH, 2) * (velocity / 12.0);
}
