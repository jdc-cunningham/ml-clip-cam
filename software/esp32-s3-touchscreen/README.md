### About

Please note that this code is based on the demo code provided by waveshare here:

https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-1.28#Arduino_IDE_Sample

click on sample demo takes you to:

https://files.waveshare.com/wiki/ESP32-S3-Touch-LCD-1.28/Esp32-s3-touch-lcd-1.28-code.zip

Since this demo has a lot of dependencies and at a quick glance it looks like they are used eg. `esp32-s3-touch-lcd-1.28-demo.ino` is the main equivalent and it brings in `LCD_Test.h`which pulls in `CST816S.h` which is from the `LVGL_Arduino` folder.

The only part I modified is the main file eg. `esp32-s3-touch-lcd-1.28-demo.ino`

### Dependencies

I followed their guide above and I did install `lvgl` and `TFT_eSPI` on my machine by browsing libraries within the Arduino IDE.

