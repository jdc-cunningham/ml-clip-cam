#include <Arduino.h>
#include "LCD_Test.h"
#include <SoftwareSerial.h>
#include <Wire.h>

UWORD Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
UWORD *BlackImage;
CST816S touch(6, 7, 13, 5);	// sda, scl, rst, irq

// software serial
#define SS_PORT_TX 15
#define SS_PORT_RX 16

// EspSoftwareSerial::UART SoftSerial;
byte data_to_echo = 0;

// resolution 240x240

int delay_tick = 0; // use for splitting specific delays eg. 16ms 60fps
bool recording = false;
int recording_tick = 0; // increment every loop
int recording_time_ms = 0; // ms increment
int rec_start_time_ms = 0;
int action_btn_touch_area[2][2] = {{50, 170}, {190, 210}};
int last_touch = 0;
bool pi_ready = false; // set to true for dev
String file_count = "0 files";

bool action_btn_touched(int touch_x, int touch_y) {
  if (touch_x >= action_btn_touch_area[0][0] and touch_x <= action_btn_touch_area[1][0]) {
    if (touch_y >= action_btn_touch_area[0][1] and touch_y <= action_btn_touch_area[1][1]) {
      return true;
    }
  }

  return false;
}

void clear_screen() {
  Paint_Clear(WHITE);
}

int get_recording_time_s() {
  int elapsed_time = millis() - rec_start_time_ms;
  return elapsed_time > 1000 ? floor(elapsed_time / 1000) : 0;
}

String check_leading_zero(int sec) {
  if (sec < 10) {
    return "0" + String(sec);
  }

  return String(sec);
}

String format_recording_time() {
  int rec_time_s = get_recording_time_s();

  if (rec_time_s > 60) {
    int f_to_int = floor(rec_time_s / 60);

    return String(f_to_int) + ":" + String(check_leading_zero(rec_time_s % 60));
  } else {
    return "0:" + check_leading_zero(rec_time_s);
  }
}

void draw_recording_time() {
  if (recording) {
    int elapsed_ms = millis() - rec_start_time_ms; // this is a double process, done in fcn below
    String elapsed_time = format_recording_time();

    int x_offset = 0;

    // auto center
    if (elapsed_ms > 61000) {
      x_offset = 5;
    }

    // could go 3 digits but that would be nuts eg. 100 minutes
    // battery life currently around 2 hrs (700mAh) but unlikely to record that long

    // .c_str() https://stackoverflow.com/a/16810536
    Paint_DrawString_EN(85 - x_offset, 100, elapsed_time.c_str(), &Font24, WHITE, BLACK);
  }
}

void draw_recording_text() {
  if (recording) {
    Paint_DrawString_EN(40, 140, "recording", &Font20, WHITE, BLACK);
  }
}

void draw_recording_circle() {
  bool on = recording_tick > 0 && recording_tick % 2 == 0;

  if (on) {
    Paint_DrawCircle(190, 150, 8, RED, DOT_PIXEL_2X2, DRAW_FILL_FULL);
  } else {
    Paint_DrawCircle(190, 150, 8, WHITE, DOT_PIXEL_2X2, DRAW_FILL_FULL);
  }
}

void draw_waiting() {
  Paint_DrawString_EN(20, 110, "waiting for pi", &Font20, WHITE, BLACK);
}

void draw_main_btn() {
  String which = "";

  if (!recording) which = "start";
  if (recording) which = "stop";

  Paint_DrawRectangle(50, 170, 190, 210, GRAY, DOT_PIXEL_2X2, DRAW_FILL_FULL);

  if (which == "start") {
    Paint_DrawString_EN(70, 130, file_count.c_str(), &Font20, WHITE, BLACK);
    Paint_DrawString_EN(85, 180, "start", &Font20, GRAY, BLACK);
  }else {
    Paint_DrawString_EN(90, 180, "stop", &Font20, GRAY, BLACK);
  }
}

void toggle_recording() {
  recording = !recording;

  if (recording) Serial1.println("start");
  if (!recording) Serial1.println("stop"); Serial1.println("file count");
}

bool screen_idle() {
  if (last_touch > 0 && ((millis() - last_touch) > 5000)) {
    return true;
  } else {
    return false;
  }
}

void setup() {
  // 40 MHz crystal, 10 -> 1ms delay is roughly 1 sec, 2 sec slow in 10 sec sample
  setCpuFrequencyMhz(10);

  Serial.begin(115200);
  touch.begin();

  // software serial to pi
  Serial1.begin(115200, SERIAL_8N1, SS_PORT_RX, SS_PORT_TX);
  Serial1.setTimeout(1);

  if (!Serial1) {
    Serial.println("failed to start soft serial");
  }
  
  // PSRAM Initialize
  if(psramInit()) {
    Serial.println("\nPSRAM is correctly initialized");
  } else {
    Serial.println("PSRAM not available");
  }

  if ((BlackImage = (UWORD *)ps_malloc(Imagesize)) == NULL){
      Serial.println("Failed to apply for black memory...");
      exit(0);
  }
  
  // put your setup code here, to run once:
  if (DEV_Module_Init() != 0) {
    Serial.println("GPIO Init Fail!");
  } else {
    Serial.println("GPIO Init successful!");
    LCD_1IN28_Init(HORIZONTAL);
    LCD_1IN28_Clear(WHITE);  
    /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage((UBYTE *)BlackImage, LCD_1IN28.WIDTH, LCD_1IN28.HEIGHT, 0, WHITE);
    Paint_SetScale(65);
    Paint_SetRotate(ROTATE_0);
    Paint_Clear(WHITE);
  }

  // listen to touch inputs
  while (true) {
    delay_tick += 1;

    if (recording) {
      if (rec_start_time_ms == 0) {
        rec_start_time_ms = millis();
      }

      recording_tick += 1;
      recording_time_ms += 1; // used to be 16
    } else {
      if (recording_time_ms != 0) {
        rec_start_time_ms = 0;
        recording_tick = 0;
        recording_time_ms = 0;
      }
    }

    if (screen_idle()) {
      LCD_1IN28_TOGGLE_SCREEN(false);
    } else {
      LCD_1IN28_TOGGLE_SCREEN(true);
    }
    
    clear_screen();

    if (pi_ready) {
      draw_main_btn();
    } else {
      draw_waiting();
    }

    draw_recording_time();
    draw_recording_text();
    draw_recording_circle();

    LCD_1IN28_Display(BlackImage);
    
    // screen touched
    if (touch.available()) {
      int now = millis();

      if (last_touch > 0 && ((now - last_touch) < 1000)) {
        continue; // avoid too fast touch due to fast refresh rate
      }

      if (action_btn_touched(touch.data.x, touch.data.y)) {
        toggle_recording();
      }

      last_touch = now;
    }

    if (Serial1.available()) {
      String msg = Serial1.readString();

      if (msg == "ready") {
        pi_ready = true; 
        Serial1.println("file count");
      }

      if (msg.indexOf("files") > -1) {
        file_count = msg;
      }
    }

    delay(1);
  }
}

void loop()
{
  delay(2); // I don't think this is reached
}

