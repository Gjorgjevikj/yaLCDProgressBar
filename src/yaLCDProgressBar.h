#ifndef LCDPROGRESSBAR_H
#define LCDPROGRESSBAR_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>     // if you don't have I2C version of the display, use LiquidCrystal.h library instead

class LCDProgressBar
{
public:
    enum PixelMatrix : byte { charRows = 8, charCols = 5 };
    enum CustomChar : byte { pbBlank, pbLeft, pbMiddle, pbRight, pbLeft2, pbMiddle2, pbRight2, pbFull = 255 };

    LCDProgressBar(LiquidCrystal_I2C& _display, byte _width, byte _row = 0, byte _col = 0, bool _alt = false);
    void init();
    int size() const;
    void setWidth(int w);
    void setPosition(byte, byte);
    void showProgress(int val);
    void showProgressPct(int pct);

protected:
    void showProgressAlt(int val, bool alt = false);
    static uint8_t createFillMask(uint8_t mask);
    void CreateCustomCharacter(uint8_t chpos, uint8_t mask, uint8_t vframe, uint8_t hframe);
    void CreateCustomChars(int val, bool alt = false);

    LiquidCrystal_I2C& display; // refference to the display object
    byte width; // progress bar width in characters
    byte row; // row position of the progress bar
    byte col; // column position of the progress bar
    bool alt; // first or second progress bar
};

#endif