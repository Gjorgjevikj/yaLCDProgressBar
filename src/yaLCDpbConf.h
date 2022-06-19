#include <LiquidCrystal_I2C.h>     // if you don't have I2C version of the display, use LiquidCrystal.h library instead
#define LCD_OBJ LiquidCrystal_I2C

//#include <LiquidCrystal.h>
//#define LCD_OBJ LiquidCrystal

// Progress bar type
// 0 - slightly rounded edges, full height (8 pixels)
// 1 - square edges, reduced hight (6 pixels, frame @6 pixels)
// 2 - experimental... filled part separated from frame

#define PB_TYPE 1

