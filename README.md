# M5912B
This program is used to control a COG(Chip on Glass) LCD display to let it show some ideal content.
1. lcd.h defines all functions will be used in the program. Also defines all GPIO port usage.
2. lcd.c gives specific functions.
3. main.c applied the functions define in lcd.c to display ideal content. Not only people can use the pixel data file to dosplay different image, but also people can simply use command to control the display IC to turn the each pixel ON & OFF to generate the display content.

Parts were using:
1. STC90LE516AD This is a 8051-based microcontroller, which can handle the display control logic efficiently.
2. ST75161-G2A This is a 4-level gray scale dot matrix LCD controller.
3. COG display M5912B
