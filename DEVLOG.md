### 04/15/2024

11:43 AM

- [ ] slow down sampling/refresh time
- [ ] see if "turning off" display reduces power consumption

Can verify with desk power supply

12:44 PM

Was suggested I reduce the CPU speed, was able to do that

Getting some power consumption figures

I will go from 240mhz to 10mhz

12:52 PM

So I did a power draw test and it peaks around 500mA but idle is 210mA at 5V

Oh I should sample it while it's recording

12:55 PM

Recording pulls a lot no surprise, somewhere around 470ma peaks beyond 500 and goes down to 455ma too

2:58 PM

Damn... today is wasted oh well

Make that video at least

3:31 PM

Had to write new function in header file too to be defined

3:36 PM

The dim works but I can see a flashing

Also the touch is laggy where it can retrigger the record after you push stop.

Not a huge deal... once the new design is out and swappable batteries is a thing then this won't be such a big deal

There are many more worries to reduce power consumption but it's attached to an rpi zero 2 which kind of defeats power saving attempts
