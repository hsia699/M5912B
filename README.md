# M5912B
This program is used to control a COG(Chip on Glass) LCD display to let it show some ideal content.
lcd.h defines all functions will be used in the program. Also defines all GPIO port usage.
lcd.c gives specific functions.
main.c applied the functions define in lcd.c to display ideal content. Not only people can use the pixel data file to dosplay different image, but also people can simply use command to control the display IC to turn the each pixel ON & OFF to generate the display content.
