//*****************************************************************************/
/// 
/// \file memory.h
/// 
/// \brief Header file to interact with memory, registers, and the UART interface.
/// 
/// \author Kiran Jojare, Viraj Patel
/// 
//*****************************************************************************/
#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

//*****************************************************************************/
/// \brief Reads serial input into a buffer.
///
/// \param buffer The buffer to store the read data.
/// \param length The maximum number of characters to read.
void read_serial_input(char *buffer, int length);

//*****************************************************************************/
/// \brief Prints the values of the core registers to the UART interface.
void print_registers();

//*****************************************************************************/
/// \brief Dumps the memory contents in hex format.
void dump_memory(void);

//*****************************************************************************/
/// \brief Displays the last 16 words of the stack.
void display_last_16_stack_words();

#endif // MEMORY_H
