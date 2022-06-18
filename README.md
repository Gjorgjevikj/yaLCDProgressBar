# yaLCDProgressBar

Yet another LCD progress bar (gauge) for the character based LCD displays for Arduino

Relies on the LiquidCrystal_I2C.h library (and should work on any platform that supports this library). Uses the user definable characters of the LCD display and can dispalay up to 2 smoot gauges simultaneously.

Three libraries 
- yaLCDProgressBar.h : Progress bar drawn using the whole hiht of the character (8 pixels). The width of the progress bar can be configured and the postion on the LCD display. The state of the progress bar cen be set as a percentage or absolute value (pixels).
- yaLCDProgressThinBar.h : Same as previous, just draws thiner progess bar that is only 6 pixels high. Also it has square edges contrary to the previous one that has rounded corners
- yaLCDGauge.h : Progress bar for battery charge status


Known minorities:
- no exast checking of the parameters (so the gauges can act unexpectedly if odd values are passed, like negative or very big numbers) for performance reasons.
- the borders drawn with the gauge are considered as part of the gauge (except for the battery gauge that is dwawn in a different way) 

So here it is, hopefully someone else can find a use of it (or make a comment).
