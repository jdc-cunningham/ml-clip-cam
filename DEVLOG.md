- [x] get basic understanding of demo code wrt:
  - how to draw something
  - how to get touch input
  - how to access imu values
- [ ] talk to RPi
  - basic is just high/low GPIO out
  - serial/i2c is more desirable
- [ ] bridge touchscreen with python

### 04/03/2024

11:34 AM

Alright I have some sleep today, not terrible but not great

I want to get this done becuase I have to start another project

Today's my last day off too sucks

I used to only work 4 days (4x10) but can't afford it, need to work overtime

11:40 AM

Engaging the Kornholio now

Had a scare this morning, thought my SSD died, had to pull the power on desktop for it to recognize my drive

11:48 AM

Had to fix this inotify fs watches thing

1:12 PM

Back from brief break

I was making good progress but when trying to display time my int to string conversion is having problems, crashes display

1:35 PM

The code is getting nasty already, haven't even touched ESP32 to RPi yet

2:10 PM

Screwing around with this weird string print shifting related to truncated float

2:21 PM

Dumb, delayed by moving videos from Pi this is a bottle neck even with OTG cable moving, it takes time

I have to get one of those cables at some point

---

### 04/02/2024

11:51 AM

I slept in today, I worked 5, 10 hr days

So I'm pretty beat, just slowly going through this

I want to "wrap" this project up hardware wise where I can then just fly/record footage and start doing the ML stuff

11:59 AM

I'm still distracted

Today's goals:

- [ ] get basic understanding of demo code wrt:
  - how to draw something
  - how to get touch input
  - how to access imu values
- [ ] talk to RPi
  - basic is just high/low GPIO out
  - serial/i2c is more desirable
- [ ] bridge touchscreen with python

12:22 PM

I'm still distracted, dumb monke scrolling

Free yourself boy, remember what awaits you in 2 days

So when the demo runs it:

- flashes different colors
- some different drawings/font
- then shows live output of accel with "longpress" to quit interesting
- then a touch thing

I feel like I'm cheating using my ultrawide monitor to read code vs. the laptop in front of me

I'm just used to looking forward/bigger display vs. down/smaller

I say "cheating" because I want to develop from a laptop but I don't, I use a desktop

This is the "main" equivalent `esp32-s3-touch-lcd-1.28-demo.ino`

it uses integers for state handling interesting eg. `#if 1`

oh no they're just switches I guess, they're all if 1 but if 0 would be turn off

lol

https://cplusplus.com/forum/beginner/284804/

noob!

12:32 PM

the code has everything in setup

12:37 PM

man flashing this is not great

Had to restart arduino, do permission again

seems I have to do the permission every time it is connected

the `sudo chmod a+rw /dev/ttyACM0`

Probably makes sense regarding random peripherals having same path

I see the serial monitor though baud rate of 115200

1:08 PM

Distracted by life (poor)

1:20 PM

Alright what do I want to do...

1:23 PM

Here's an interface

<img src="basic-video-recording-ui.JPG"/>

I feel bad that this is all this UI will do... but more happens underneath eg. storing IMU values as the video records

1:36 PM

Setting up git on the laptop

2:50 PM

Back from brief break

I did realize that serial is probably easy, assuming it works like other "arduino" platforms eg. bring in the serial library and specify pins then it works... have to see

I'm thinking I may still have dedicated button pins just because

I could have separate threads and not block a primary communication line

3:03 PM

Holy f

Jacob please focus

3:06 PM

Need to do brief workout, I want to get more sculpted since I've dropped enough weight to be noticeable again, still have like 15 lbs to go

I will engage the Kornholio soon

3:21 PM

Alright weak-ass 5 min workout is done, not Kornholio yet but I forgot the Tom Tom Holy F song used in Invincible S1 damn that's a good workout song

Unleash the power, see the future

3:28 PM

So hardware serial seems related to IMU and touch control

So I'll try software serial which usually is not as reliable but will see

3:40 PM

First thing I have to check is if the software serial is detected by the RPi

3:49 PM

Ugh... I got used to the mac keyboard, keep pushing wrong buttons particularly for ctrl

4:30 PM

Making progress, flashed first code but it's wrong

Need to test software serial interface with RPi next

4:40 PM

Damn I gotta eat, my stomach hurts

Will be back

5:11 PM

That was a waste almost... Shin ramen is too spicy/hot, burns my mouth

The weather is great right now, it is supposed to be rainy

I need redemption for failing to save images last week

So I'll go to the park for a bit, hopefully no flat this time lol
