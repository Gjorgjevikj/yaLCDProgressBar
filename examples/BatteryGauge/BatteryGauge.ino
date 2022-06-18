/*
    Name:       BatteryGauge.ino
    Created:	18.6.2022 11:31:51
    Author:     DESKTOP-I9\Dejan
*/


#include <LiquidCrystal_I2C.h>     // if you don't have I2C version of the display, use LiquidCrystal.h library instead
//#include <yaLCDProgressBar.h>     
//#include <yaLCDProgressThinBar.h>     
#include <yaLCDGauge.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x3f,16,2);    // set the LCD address to 0x3f for a 16 chars and 2 line display
// if you don't know the I2C address of the display, use I2C scanner first (https://playground.arduino.cc/Main/I2cScanner/)

//LCDProgressBar pb1(lcd, 12, 1, 0);
//LCDProgressBar pb2(lcd, 8, 0, 8, true);
LCDGauge bat(lcd, 6, 0, 0);

unsigned int gauge = 35;
char buffer[10];         // helper buffer to store C-style strings (generated with sprintf function)

void setup()
{
    lcd.init();                       // initialize the 16x2 lcd module
    lcd.backlight();                  // enable backlight for the LCD module
    lcd.print("Battery gauge...");
    delay(1000);
    bat.init();
    lcd.clear();
    
}

void loop()
{
    bat.showGauge(gauge);
    sprintf(buffer, "%3d", gauge);
    lcd.setCursor(12, 1);
    lcd.print(buffer);                            // print the string on the display

    gauge++;
    if (gauge > bat.size()+2) { gauge = 0; }

    delay(500);  // wait for a while 
}
