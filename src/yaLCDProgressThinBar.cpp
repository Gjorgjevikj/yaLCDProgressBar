
#include <Arduino.h>
#include "yaLCDProgressThinBar.h"     

LCDProgressThinBar::LCDProgressThinBar(LiquidCrystal_I2C& _display, byte _width, byte _row, byte _col, bool _alt)
        : display(_display), width(_width), row(_row), col(_col), alt(_alt)
{
}

void LCDProgressThinBar::init()
{
    uint8_t t[charRows] = { 0b00000, 0b11111, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b00000 };    // empty middle piece
    display.createChar(pbBlank, t);
    for (byte j = 2; j < charRows - 2; j++)
        t[j] = 0b11111;
    display.createChar(pbFull, t);
}

void LCDProgressThinBar::setPosition(byte r, byte c)
{
    row = r;
    col = c;
}

void LCDProgressThinBar::showProgress(int val)
{
    showProgressAlt(val, alt);
}

void LCDProgressThinBar::showProgressAlt(int val, bool alt)
{
    CreateCustomChars(val, alt);
    uint8_t full, blank, partial;
    full = min(max(0, val / charCols - 1), width - 2);
    partial = (val > charCols && val < (width - 1)* charCols);
    blank = max(0, width - full - 2 - partial);

    display.setCursor(col, row);
    display.write(alt ? pbLeft2 : pbLeft);
    while (full--)
        display.write(pbFull);
    if (partial)
        display.write(alt ? pbMiddle2 : pbMiddle);
    while (blank--)
        display.write(byte(pbBlank));
    display.write(alt ? pbRight2 : pbRight);
}

void LCDProgressThinBar::showProgressPct(int val)
{
    showProgressAlt(val * (width * charCols) / 100, alt);
}

static uint8_t LCDProgressThinBar::createFillMask(uint8_t val)
{
    uint8_t bitmask = 1 << charCols; // 0b100000;
    uint8_t mask = 0;

    while (val--)
        mask |= (bitmask >>= 1);
    return mask;
}

void LCDProgressThinBar::CreateCustomCharacter(uint8_t chpos, uint8_t mask, uint8_t vframe, uint8_t hframe)
{
    byte t[charRows];
    for (byte j = 2; j < charRows - 2; j++)
        t[j] = mask | vframe;
    t[0] = t[charRows - 1] = 0;
    t[1] = t[charRows - 2] = hframe;
    display.createChar(chpos, t);
}

void LCDProgressThinBar::CreateCustomChars(int val, bool alt = false)
{
    uint8_t mask;
    mask = (val < charCols) ? createFillMask(val) : 0xff;
//    CreateCustomCharacter(alt ? pbLeft2 : pbLeft, mask, 0b10000, 0b01111);
    CreateCustomCharacter(alt ? pbLeft2 : pbLeft, mask, 0b10000, 0b11111);
    mask = createFillMask(val % charCols);
    CreateCustomCharacter(alt ? pbMiddle2 : pbMiddle, mask, 0, 0b11111);
    mask = (val > (width - 1) * charCols) ? createFillMask(val % charCols) : 0;
//    CreateCustomCharacter(alt ? pbRight2 : pbRight, mask, 0b00001, 0b11110);
    CreateCustomCharacter(alt ? pbRight2 : pbRight, mask, 0b00001, 0b11111);
}

