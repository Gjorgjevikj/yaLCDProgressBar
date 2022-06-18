
#include <Arduino.h>
#include "yaLCDGauge.h"     

LCDGauge::LCDGauge(LiquidCrystal_I2C& _display, byte _width, byte _row, byte _col)
        : display(_display), width(_width), row(_row), col(_col)
{
}

void LCDGauge::init()
{
    uint8_t t[charRows] = { 0b11111, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111 };    // empty middle piece
    display.createChar(batBlank, t);
    for (byte i = 2; i < charRows - 2; i++)
        t[i] = 0b11111;
    display.createChar(batFull, t);

    for (byte i = 0; i < charRows; i++)
        t[i] = 0b00001;
    display.createChar(batLeft, t);
    for (byte i = 0; i < charRows; i++)
        t[i] = 0b10000;
    for (byte i = 2; i < charRows-2; i++)
        t[i] = 0b11100;
    display.createChar(batRight, t);
}

void LCDGauge::setPosition(byte r, byte c)
{
    row = r;
    col = c;
}

int LCDGauge::size() const
{
    return (width-2) * charCols;
}

void LCDGauge::showGauge(int val)
{
    CreateCustomChars(val);
    uint8_t full, blank, partial;
    full = min(max(0, val / charCols), width - 2);
    partial = (val < (width - 1)* charCols);
    blank = max(0, width - full - 2 - partial);

    display.setCursor(col, row);
    display.write(batLeft);
    while (full--)
        display.write(batFull);
    if (partial)
        display.write(batMid);
    while (blank--)
        display.write(byte(batBlank));
    display.write(batRight);
}

void LCDGauge::showGaugePct(int val)
{
    showGauge(val * (width * charCols) / 100);
}

static uint8_t LCDGauge::createFillMask(uint8_t val)
{
    uint8_t bitmask = 1 << charCols; // 0b100000;
    uint8_t mask = 0;

    while (val--)
        mask |= (bitmask >>= 1);
    return mask;
}

void LCDGauge::CreateCustomCharacter(uint8_t chpos, uint8_t mask, uint8_t vframe, uint8_t hframe)
{
    byte t[charRows];
    for (byte j = 2; j < charRows - 2; j++)
        t[j] = mask | vframe;
    t[0] = t[charRows - 1] = hframe;
    t[1] = t[charRows - 2] = 0;
    display.createChar(chpos, t);
}

void LCDGauge::CreateCustomChars(int val)
{
    uint8_t mask;
    mask = createFillMask(val % charCols);
    CreateCustomCharacter(batMid, mask, 0, 0b11111);
}

