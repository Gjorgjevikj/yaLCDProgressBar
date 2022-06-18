# yaLCDProgressBar
Yet another LCD progress bar (gauge)

Relies on the LiquidCrystal_I2C.h library (and should work on any platform that supports this library). Uses the user definable characters of the LCD display and can dispalay up to 2 smoot gauges simultaneously.

Three libraries 
- yaLCDProgressBar.h : Progress bar drawn using the whole hiht of the character (8 pixels). The width of the progress bar can be configured and the postion on the LCD display. The state of the progress bar cen be set as a percentage or absolute value (pixels).
- yaLCDProgressThinBar.h : Same as previous, just draws thiner progess bar that is only 6 pixels high. Also it has square edges contrary to the previous one that ... rounded corners


So here it is, hopefully someone else can find a use of it (or make a comment).
