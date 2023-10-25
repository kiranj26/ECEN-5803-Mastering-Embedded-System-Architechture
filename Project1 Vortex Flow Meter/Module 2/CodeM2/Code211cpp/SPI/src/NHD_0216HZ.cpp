/*----------------------------------------------------------------------------
 Newhaven NHD0216HZ LCD C/C++ file
 *----------------------------------------------------------------------------*/

#include "mbed.h"
#include "NHD_0216HZ.h"
#include "pindef.h"

DigitalOut SS(SPI_CS);     //slave select a.k.a. cs or latch for shift reg
SPI spi(SPI_MOSI, NC, SPI_SCLK);

//Initialise SPI
void init_spi(void) {
    SS = 1;
    
    spi.format(8, 3);         //8bit spi mode 2
    spi.frequency(100000);    //100 kHz spi clock
}

//Initialise LCD
void init_lcd(void) {
    // Wait for 45 milliseconds: Ensures that the LCD has finished its internal initialization.
    wait_ms(45); 
    
    // 0x30 - Function Set: This is part of the wake-up command and initializing the LCD in 8-bit mode
    write_cmd(0x30);
    wait_us(40); // Wait for 40 microseconds before sending the next command.
    
    // 0x20 - Function Set: This command sets the LCD to use a 4-bit data length for subsequent commands.
    write_cmd(0x20);
    wait_us(40); // Wait for 40 microseconds before sending the next command.
    
    // 0x20 - Function Set: Repeating the command required as per the initialization sequence.
    write_cmd(0x20);
    wait_us(40); // Wait for 40 microseconds before sending the next command.
    
    // 0x0C - Display ON/OFF Control: Turns on the display with the cursor off and no blinking.
    write_cmd(0x0C);
    wait_us(40); // Wait for 40 microseconds before sending the next command.
    
    // 0x01 - Clear Display: Clears the display.
    write_cmd(0x01); 
    wait_us(1525); // Longer delay, as clearing the display takes more time.
    
    // 0x06 - Entry Mode Set: Sets the cursor move direction to increment, and no display shift.
    write_cmd(0x06);
    wait_us(40); // Wait for 40 microseconds before sending the next command.
    
    // 0x28 - Function Set: Configures the LCD in 4-bit mode, 2 lines, and 5x8 dots format font.
    write_cmd(0x28);
    wait_ms(40); // Wait for 40 milliseconds before sending the next command.
    
    // Set the cursor to the initial position (0,0).
    set_cursor(0, 0);
}

//Write 4bits to the LCD
void write_4bit(int nibble, int mode) {
    SS = 0;
    spi.write(nibble | ENABLE | mode);
    SS = 1;
    wait_us(1);
    SS = 0;
    spi.write(nibble & ~ENABLE);
    SS = 1;
}

//Write a command to the LCD
void write_cmd(int data) {
    int hi_n;
    int lo_n;
    
    hi_n = hi_n = (data & 0xF0);
    lo_n = ((data << 4) &0xF0);
    
    write_4bit(hi_n, COMMAND_MODE);
    write_4bit(lo_n, COMMAND_MODE);
}

//Write data to the LCD
void write_data(char c) {
    int hi_n;
    int lo_n;
    
    hi_n = hi_n = (c & 0xF0);
    lo_n = ((c << 4) &0xF0);
    
    write_4bit(hi_n, DATA_MODE);
    write_4bit(lo_n, DATA_MODE);
}

//Set cursor position
void set_cursor(int column, int row) {
    int addr;
    
    addr = (row * LINE_LENGTH) + column;
    addr |= TOT_LENGTH;
    write_cmd(addr);
}

//Print strings to the LCD
void print_lcd(const char *string) {
    while(*string){
        write_data(*string++);
    }
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
