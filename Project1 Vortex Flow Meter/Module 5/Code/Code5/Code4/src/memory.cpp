//*****************************************************************************/
/// 
/// \file memory.cpp
/// 
/// \brief Functions to interact with memory, registers, and the UART interface.
/// 
/// \author Kiran Jojare, Viraj Patel
/// 
//*****************************************************************************/

#include "memory.h"
#include "mbed.h"
#include "stdio.h"

extern Serial pc;

//*****************************************************************************/
/// \fn void read_serial_input(char *buffer, int length)
///
/// \brief Reads input from the serial interface.
///
/// This function captures characters from the UART until a newline or a carriage 
/// return character is detected. Additionally, it handles backspaces by erasing 
/// the previously entered character.
//*****************************************************************************/
void read_serial_input(char *buffer, int length) {
    int count = 0;
    while (count < length - 1) {
        while (!pc.readable());
        char c = pc.getc();
        
        if (c == '\r' || c == '\n') {
            break; 
        } else if (c == 0x08 || c == 0x7F) { // Backspace detected
            if (count > 0) {
                count--;
                pc.putc(0x08); // Move cursor one position back
                pc.putc(' ');  // Replace last character with space
                pc.putc(0x08); // Move cursor one position back again
            }
        } else {
            pc.putc(c); // Echo back to terminal for other characters
            buffer[count++] = c;
        }
    }
    buffer[count] = '\0';
}

/*
void read_serial_input(char *buffer, int length) {
    int count = 0;
    while (count < length - 1) {
        while (!pc.readable());
        char c = pc.getc();
        pc.putc(c); // Echo back to terminal
        if (c == '\r' || c == '\n') {
            break; 
        }
        buffer[count++] = c;
    }
    buffer[count] = '\0';
}
*/

//*****************************************************************************/
/// \brief Fetch value of R1 register.
__asm uint32_t get_r0() {
    MOV R0, R0
    BX LR
}
//*****************************************************************************/
/// \brief Fetch value of R2 register.
__asm uint32_t get_r1() {
    MOV R0, R1
    BX LR
}
//*****************************************************************************/
/// \brief Fetch value of R3 register.
__asm uint32_t get_r2() {
    MOV R0, R2
    BX LR
}
//*****************************************************************************/
/// \brief Fetch value of R4 register.
__asm uint32_t get_r3() {
    MOV R0, R3
    BX LR
}
//*****************************************************************************/
/// \brief Fetch value of R5 register.
__asm uint32_t get_r4() {
    MOV R0, R4
    BX LR
}
//*****************************************************************************/
/// \brief Fetch value of R6 register.
__asm uint32_t get_r5() {
    MOV R0, R5
    BX LR
}
//*****************************************************************************/
/// \brief Fetch value of R7 register.
__asm uint32_t get_r6() {
    MOV R0, R6
    BX LR
}
//*****************************************************************************/
/// \brief Fetch value of R8 register.
__asm uint32_t get_r7() {
    MOV R0, R7
    BX LR
}
//*****************************************************************************/
/// \brief Fetch value of R9 register.
__asm uint32_t get_r8() {
    MOV R0, R8
    BX LR
}
//*****************************************************************************/
/// \brief Fetch value of R10 register.
__asm uint32_t get_r9() {
    MOV R0, R9
    BX LR
}
//*****************************************************************************/
/// \brief Fetch value of R11 register.
__asm uint32_t get_r10() {
    MOV R0, R10
    BX LR
}
//*****************************************************************************/
/// \brief Fetch value of R12 register.
__asm uint32_t get_r11() {
    MOV R0, R11
    BX LR
}
//*****************************************************************************/
/// \brief Fetch value of R13 register.
__asm uint32_t get_r12() {
    MOV R0, R12
    BX LR
}

//*****************************************************************************/
/// \brief Fetch value of Stack Pointer register.
__asm uint32_t get_sp() {
    MOV R0, SP
    BX LR
}

//*****************************************************************************/
/// \brief Fetch value of Link Register.
__asm uint32_t get_lr() {
    MOV R0, LR
    BX LR
}

//*****************************************************************************/
/// \brief Fetch value of Program Counter register.
__asm uint32_t get_pc() {
    MOV R0, PC
    BX LR
}
//*****************************************************************************/
/// \fn void print_registers(void)
///
/// \brief Prints the values of the registers.
///
/// This function sends the current values of the processor's registers over UART.
//*****************************************************************************/
void print_registers() {
		pc.printf("Printing Register Values\n\r");
    pc.printf("R0: 0x%08lX\r\n", get_r0());
    pc.printf("R1: 0x%08lX\r\n", get_r1());
    pc.printf("R2: 0x%08lX\r\n", get_r2());
    pc.printf("R3: 0x%08lX\r\n", get_r3());
    pc.printf("R4: 0x%08lX\r\n", get_r4());
    pc.printf("R5: 0x%08lX\r\n", get_r5());
    pc.printf("R6: 0x%08lX\r\n", get_r6());
    pc.printf("R7: 0x%08lX\r\n", get_r7());
    pc.printf("R8: 0x%08lX\r\n", get_r8());
    pc.printf("R9: 0x%08lX\r\n", get_r9());
    pc.printf("R10: 0x%08lX\r\n", get_r10());
    pc.printf("R11: 0x%08lX\r\n", get_r11());
    pc.printf("R12: 0x%08lX\r\n", get_r12());
    pc.printf("SP: 0x%08lX\r\n", get_sp());
    pc.printf("LR: 0x%08lX\r\n", get_lr());
    pc.printf("PC: 0x%08lX\r\n", get_pc());
}

//*****************************************************************************/
/// \fn void dump_memory(void)
///
/// \brief Dumps memory content from a given address for a given length.
///
/// This function sends the content of the memory from a specified address 
/// and for a given length over UART.
//*****************************************************************************/
void dump_memory(void) {
		/* Custom Input Code
		char input_buffer[32];
    uint32_t memory_location;
    uint32_t length;
		pc.printf("SP: 0x%08lX\r\n", get_sp());
    pc.printf("Enter memory location in hex format (e.g., 0x20010000): ");
    read_serial_input(input_buffer, sizeof(input_buffer));
    sscanf(input_buffer, "%lx", &memory_location);

    pc.printf("\r\nEnter length: ");
    read_serial_input(input_buffer, sizeof(input_buffer));
    sscanf(input_buffer, "%lu", &length);

    pc.printf("\r\nYou entered location: 0x%08lX and length: %lu\r\n", memory_location, length);
	  */
		uint32_t memory_location = 0x20010000;
    uint32_t length = 64;
    pc.printf("Dumping memory at Location 0X%08X %d Bytes:\r\n", memory_location, length);
	
		uint32_t start_address = memory_location ;
    const uint32_t bytes_per_line = 16;
    uint8_t *ptr = (uint8_t *)start_address;

    for (uint32_t i = 0; i < length; i += bytes_per_line) {
        // Print the memory address
        pc.printf("0x%08lX: ", (uint32_t)(ptr + i));

        // Print the hex values
        for (uint32_t j = 0; j < bytes_per_line; j++) {
            if (i + j < length) {
                pc.printf("%02X ", ptr[i + j]);
            } else {
                pc.printf("   "); // for alignment when length is not a multiple of bytes_per_line
            }
        }

        pc.printf(" ");

        // Print the ASCII values
        for (uint32_t j = 0; j < bytes_per_line; j++) {
            if (i + j < length) {
                char c = ptr[i + j];
                if (c < 32 || c > 126) { // non-printable chars
                    c = '.';
                }
                pc.printf("%c", c);
            }
        }

        pc.printf("\r\n");
    }
}
//*****************************************************************************/
/// \fn void display_last_16_stack_words(void)
///
/// \brief Displays the last 16 words in the stack.
///
/// This function sends the last 16 words of the current stack over UART.
//*****************************************************************************/
void display_last_16_stack_words() {
    uint32_t *stack_ptr = (uint32_t *)get_sp();
		pc.printf("Print Stack \n\r");
		pc.printf("Current Stack Pointer SP: 0x%08lX\r\n", stack_ptr);
    for (int i = 0; i < 16; i++) {
			pc.printf("Word %d: 0x%08X : %08X\r\n", 16 - i, stack_ptr - i,*(stack_ptr-i));
    }
}

