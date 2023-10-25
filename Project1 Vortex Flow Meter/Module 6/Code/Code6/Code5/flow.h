/**
 * \file flow.h
 * \author Kiran Jojare, Viraj Patel
 * \brief Header file for flow calculations related constants and functions for STM32F401xE.
 */

#ifndef FLOW_H
#define FLOW_H

#define D 0.5              ///< Bluff body width in inches.
#define PID_INCH 2.900     ///< Pipe inner diameter in inches.
#define PID_METER 0.07366  ///< Pipe inner diameter in meters (Equivalent of 2.900 inches in meters).

/**
 * \brief Calculates the fluid flow.
 * 
 * Computes the fluid flow based on various parameters including temperature, 
 * density, and viscosity. Uses predefined constants for bluff body width and 
 * pipe inner diameter.
 */
void calculate_flow(void);

#endif // FLOW_H
