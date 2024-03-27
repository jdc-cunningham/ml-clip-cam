### 03/27/2024

11:33 AM

Alright late sleep/wake time today

Had to wait for xcode to install on this newly flashed MBP

I have the Arduino IDE on there

I'm going to setup the deps for programming this ESP32 touchscreen

Ideally I would use serial for coms between the touchscreen and the RPi but simple buttons would work too

I only have about 2.5 hrs and then I'm going to go the park, then donate plasma after

I am hoping I can:

- [ ] program UI
- [ ] determine comm approach
- [ ] bridge RPi with ESP32

Then I'll have to come up with the new code that will run the setup

Also make a daughter board to pop onto the clip cam, that won't be too hard

11:46 AM

So I think I'm ready to program, I did not drag the lvgl, TFT_eSPI, ... folders that may be a problem

I'm looking at their demo code to see how it works

11:52 AM

It's so funny like I have no idea what to do

I just want a box that I can touch

11:58 AM

Okay I opened their demo in the Arduino IDE

I set the flash size, QSPI, installed LVGL and TFT_eSPI from Arduino IDE libraries

Let's see if I can flash the demo code

12:08 PM

Looks like it's this one

/dev/cu.usbmodem54E20335641

12:16 PM

So far not successful, stuck on this "result was 01070000: Operation timed out" error

Tried installing CH343P driver no help

1:00 PM

Damn... I'm still stuck on this problem... I guess I'll try another computer

I have programmed Arduino before with this mac even an ESP-01 device

1:09 PM

Trying it on Linux
