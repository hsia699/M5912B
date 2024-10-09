// Header file for COG(Chip on Glass) Display M5912B
// Author: Jeff Zhong
// Date: 10/01/2024

// Include guard.
#ifndef LCD_H
#define LCD_H

#include <8052.h>
#include <stdint.h>

typedef uint8_t uchar;
typedef uint16_t uint;

// Pins' usage.
#define LCD_CSB_PIN   P1_7
#define LCD_A0_PIN     P1_6
#define LCD_RST          P1_5
#define LCD_SCL_PIN   P3_2
#define SWITCH           P3_3
#define LCD_SDA_PIN  P3_4

// Functions
void Delayms(uint t);
void LCD_Init(void);  // Initialize the LCD.
void LCD_Write_CMD(uint8_t cmd);  // Send command to LCD.
void LCD_Write_DAT(uint8_t dat);  // Send data to the LCD.

void Set_Column_Address();  // Set the column address
void Set_Page_Address();      // Set the page address

#endif
