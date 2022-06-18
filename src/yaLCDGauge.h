#ifndef LCDGAUGE_H
#define LCDGAUGE_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>     // if you don't have I2C version of the display, use LiquidCrystal.h library instead

class LCDGauge
{
public:
    enum PixelMatrix : byte { charRows = 8, charCols = 5 };
    enum CustomChar : byte { batBlank, batLeft, batMid, batRight, batFull, pbBlank, bpMid, pbFull };

    LCDGauge(LiquidCrystal_I2C& _display, byte _width, byte _row = 0, byte _col = 0);
    void init();
    int size() const;
    void setPosition(byte, byte);
    void setWidth(int w);
    void showGauge(int val);
    void showGaugePct(int pct);

protected:
    //void showGaugeAlt(int val, bool alt = false);
    static uint8_t createFillMask(uint8_t mask);
    void CreateCustomCharacter(uint8_t chpos, uint8_t mask, uint8_t vframe, uint8_t hframe);
    void CreateCustomChars(int val);

    LiquidCrystal_I2C& display; // refference to the display object
    byte width; // progress bar width in characters
    byte row; // row position of the progress bar
    byte col; // column position of the progress bar
};

#endif