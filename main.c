// Main function to control the M5912B display logic.
// Author: Jeff Zhong
// Date: 10/01/2024

#include "lcd.h"
#include "pic.c"

int main() {
	// Page is a horizontal strip of 8 pixels in height, going across the width of the screen (columns).
    uchar page;
	// Column is the horizontal position across the width of the display.
	uchar column;
	// Index number to go throgh each pixel data inside of the pic.c.
	uint index = 0;
	
    LCD_Init();

	while(1) {
		if (SWITCH == 0) {
		    Set_Page_Address();
		    Set_Column_Address();
			
			// Write data to DDRAM.
		    LCD_Write_CMD(0x5c);
		    for(page = 0; page < 8; page++) {
			    for (column = 0; column < 128; column++) {
					// To display a checkerboard
                    //LCD_Write_DAT(0x55);
                    //LCD_Write_DAT(0xaa);
					
					// To display the custimize picture.
					LCD_Write_DAT(gImage_pic[index++]);
                }
			}
			// No operation, to let the write data to DDRAM action stop.
            LCD_Write_CMD(0x25);
		}
		Delayms(1000);
	}

    return 0;
}
