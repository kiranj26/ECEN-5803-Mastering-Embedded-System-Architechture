/*----------------------------------------------------------------------------
LAB EXERCISE 11.4- SPI and I2C interface
SERIAL COMMUNICATION
 ----------------------------------------
 Display the temperature from the virtual DS1631 temperature sensor on the 
      virtual LCD
 
 Input: virtual DS1631 temperature sensor
 Output: virtual LCD display
	
	GOOD LUCK!
 *----------------------------------------------------------------------------*/

#include "NHD_0216HZ.h"
#include "DS1631.h"
#include "pindef.h"

//Define the LCD and the temperature sensor

//Write your code here
NHD_0216HZ lcd(SPI_CS, SPI_MOSI, SPI_SCLK);  // Initialize the LCD display.
DS1631 temp_sensor(I2C_SDA, I2C_SCL, 0x90);  // Initialize the temperature sensor with I2C address 0x90.
Serial pc(UART_TX, UART_RX);								 // Initialize UART


//Define a variable to store temperature measurement
float temp;

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main() {
	//Initialise the LCD
	
	//Write your code here
	lcd.init_lcd();
	
	while(1){
		/*
		Read the temperature from the DS1631
		Update the LCD with new temperature measurement
		*/
		
		//Write your code here
		// Read the temperature from the DS1631 sensor.
		temp = temp_sensor.read();
		
		// Set the baud rate for serial communication
		pc.baud(9600);
		
		// Clear the LCD screen.
		lcd.clr_lcd();
		
		// Set the cursor to the beginning of the first line of the LCD.
		lcd.set_cursor(0,0);
		
		// Print the temperature reading on the LCD screen.
		lcd.printf("Temp: %.2f C", temp);
		
		// Printing Temperature on UART as well
		pc.printf("Temperature: %.2f Celsius\r\n", temp);
		
		// Delay to avoid overwhelming the LCD screen with updates.
		wait_ms(1000);
		
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
