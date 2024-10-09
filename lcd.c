// provides the implementation for initializing and controlling an LCD display via a 4-line SPI interface,
// including functions for sending commands, sending data, and writing text to the display.
// Author: Jeff Zhong
// Date: 10/01/2024

#include "lcd.h"
#include <stdint.h>

void Delayms(uint t) {
	volatile uint i, j;
    for (i = 0; i < t; i++) {
	    for (j = 0; j < 125; j++) {
			__asm nop __endasm;
			//while(SWITCH);
		}
	}
}

void LCD_Init(void){
	uchar n = 0x00;
	
	LCD_RST = 0;
	Delayms(20);
	LCD_RST = 1;
	Delayms(20);
	LCD_Write_CMD(0x31); 
	LCD_Write_CMD(0xD7); //Disable Auto Read
	LCD_Write_DAT(0x9F); 
	LCD_Write_CMD(0xE0); //Enable OTP Read
	LCD_Write_DAT(0x00);
	Delayms(10);
	LCD_Write_CMD(0xE1); //OTP Control Out

	LCD_Write_CMD(0x30); //
	LCD_Write_CMD(0x94); //sleep out
	LCD_Write_CMD(0xae); //display off
	Delayms(50);
	LCD_Write_CMD(0x20); //power control
	LCD_Write_DAT(0x0B);
	
	LCD_Write_CMD(0x81); //set vop
	LCD_Write_DAT(13);
	LCD_Write_DAT(0x03); //Set VOP = 16V
	
	LCD_Write_CMD(0x31); //
	LCD_Write_CMD(0x32); //analog circuit set 
	LCD_Write_DAT(0x00);
	LCD_Write_DAT(0x01);
	LCD_Write_DAT(0x05); // 1/12 bias
	LCD_Write_CMD(0x51); // Booster Level x10
	LCD_Write_DAT(0xfb);
	
	LCD_Write_CMD(0x30);
	LCD_Write_CMD(0xf0); // Set display mode 
	LCD_Write_DAT(0x10); // Mono ??
	LCD_Write_CMD(0xca); // Display Control
	LCD_Write_DAT(0x00); // CL Dividing Ratio? Not Divide
	LCD_Write_DAT(0x3f); // 1/128 duty
	LCD_Write_DAT(0x00);
	LCD_Write_CMD(0xbc); // Data Scan Direction
	LCD_Write_DAT(0x00);
	LCD_Write_CMD(0xa6); // Normal display
	
	LCD_Write_CMD(0x31);
	LCD_Write_CMD(0x40); // Internal Power Supply
	
	LCD_Write_CMD(0x30);
	LCD_Write_CMD(0x76); // Disable ICON RAM
	LCD_Write_CMD(0x15); // column address setting
	LCD_Write_DAT(32); // SEG16 - SEG143
	LCD_Write_DAT(0x9f);
	//LCD_Write_CMD(0x30);
	LCD_Write_CMD(0x75); // ROW Address setting
	LCD_Write_DAT(0x00); // COM0 - COM159
	LCD_Write_DAT(0x27);
	/*LCD_Write_CMD(0x30);
	LCD_Write_CMD(0x15);// 
	LCD_Write_DAT(0x10);
	LCD_Write_DAT(0x8f);
	LCD_Write_CMD(0x75);//
	LCD_Write_DAT(0x00);
	LCD_Write_DAT(0x27);*/
	
	LCD_Write_CMD(0xaf); // Display ON

	Delayms(50);
}

// Send command to the LCD.
void LCD_Write_CMD(uint8_t cmd) {
	uchar cmd_bit_position;

	// Pull the CSB to low to activate the LCD.
    LCD_CSB_PIN = 0;
	// Pull the A0 to low to indicate that the sending information is command.
	LCD_A0_PIN = 0;
	
	// Send the command byte bit by bit.
    for (cmd_bit_position = 0; cmd_bit_position < 8; cmd_bit_position++) {
	    LCD_SCL_PIN = 0;
		
		if (cmd & 0x80) {
		    LCD_SDA_PIN = 1;
		} else {
		    LCD_SDA_PIN = 0;
		}
		
		LCD_SCL_PIN = 1;
		cmd = cmd << 1;
	}
	LCD_CSB_PIN = 1;
}

// Send display content data to the LCD.
void LCD_Write_DAT(uint8_t dat) {
	uchar dat_bit_position;

    // Pull the CSB to low to activate the LCD.
    LCD_CSB_PIN = 0;
	// Pull the A0 to high to indicate that the sending information is the display content data.
	LCD_A0_PIN = 1;
	
	for (dat_bit_position = 0; dat_bit_position < 8; dat_bit_position++) {
	    LCD_SCL_PIN = 0;
		if (dat & 0x80) {
		    LCD_SDA_PIN = 1;
		} else {
		    LCD_SDA_PIN = 0;
		}
		LCD_SCL_PIN = 1;
		dat = dat << 1;
	}
	LCD_CSB_PIN = 1;
}

void Set_Page_Address() {
	// Page address setting command.
    LCD_Write_CMD(0x75);
	
	// Set starting page address.
    LCD_Write_DAT(0x00);
	
	// Set ending page address.
    LCD_Write_DAT(0x07);
}

void Set_Column_Address() {
	
	// Column addres setting command.
    LCD_Write_CMD(0x15);

	//Set starting column address.
    LCD_Write_DAT(0x20);

	//Set ending column address.
    LCD_Write_DAT(0x9F);
}
