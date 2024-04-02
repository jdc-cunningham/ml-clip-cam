#include <Arduino.h>
#include "LCD_Test.h"
#include <SoftwareSerial.h>

UWORD Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
UWORD *BlackImage;
CST816S touch(6, 7, 13, 5);	// sda, scl, rst, irq

// software serial
#define SS_PORT_TX 15
#define SS_PORT_RX 16
#define ACTION_BTN 17 // eg. start/stop recording

// resolution 240x240

bool recording = false;
int recording_time_ms = 0; // ms increment
int action_btn_touch_area[2][2] = {{40, 200}, {100, 240}};

bool action_btn_touched(int touch_x, int touch_y) {
  if (touch_x >= 40 and touch_x <= 100) {
    if (touch_y >= 200 and touch_y <= 240) {
      return true;
    }
  }

  return false;
}

void clear_screen() {
  Paint_Clear(WHITE);
}

int get_recording_time_s() {
  return recording_time_ms > 1000 ? floor(recording_time_ms / 1000) : 0;
}

void draw_recording_circle() {
  bool on = recording_time_ms % 2 == 0;

  if (on) {
    Paint_DrawCircle(250, 220, 15, RED, DOT_PIXEL_2X2, DRAW_FILL_FULL);
  } else {
    Paint_DrawCircle(250, 220, 15, WHITE, DOT_PIXEL_2X2, DRAW_FILL_FULL);
  }
}

void draw_main_btn() {
  String which = "";

  if (!recording) which = "Start";
  if (recording) which = "Stop";

  Paint_DrawLine(40, 200, 100, 240, GRAY, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

  if (which == "Start") {
    Paint_DrawString_EN(100, 220, "Start", &Font20, BLACK, GRAY);
  }else {
    Paint_DrawString_EN(100, 220, "Stop", &Font20, BLACK, GRAY);
  }
}

void toggle_recording() {
  recording = !recording;

  if (recording) Serial.println("recording");
  if (!recording) Serial.println("stopped recording");
}

void setup() {
  Serial.begin(115200);
  touch.begin();
  
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
    if (recording) {
      recording_time_ms += 16;
    } else {
      if (recording_time_ms != 0) {
        recording_time_ms = 0;
      }
    }

    clear_screen();
    draw_main_btn();
    draw_recording_circle();

    LCD_1IN28_Display(BlackImage);
    
    if (touch.available()) {
      if (action_btn_touched(touch.data.x, touch.data.y)) {
        toggle_recording();
      }
    }

    delay(16); // 60 fps
  }
}

void loop()
{
  delay(2); // I don't think this is reached
}

