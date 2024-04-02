#include <Arduino.h>
#include "LCD_Test.h"

UWORD Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
UWORD *BlackImage;
CST816S touch(6, 7, 13, 5);	// sda, scl, rst, irq

void setup()
{
    Serial.begin(115200);
    touch.begin();
    // PSRAM Initialize
    if(psramInit()){
      Serial.println("\nPSRAM is correctly initialized");
    }else{
      Serial.println("PSRAM not available");
    }
    if ((BlackImage = (UWORD *)ps_malloc(Imagesize)) == NULL){
        Serial.println("Failed to apply for black memory...");
        exit(0);
    }
    
    // put your setup code here, to run once:
    if (DEV_Module_Init() != 0)
      Serial.println("GPIO Init Fail!");
    else
      Serial.println("GPIO Init successful!");
      LCD_1IN28_Init(HORIZONTAL);
      LCD_1IN28_Clear(WHITE);  
      /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
      Paint_NewImage((UBYTE *)BlackImage, LCD_1IN28.WIDTH, LCD_1IN28.HEIGHT, 0, WHITE);
      Paint_SetScale(65);
      Paint_SetRotate(ROTATE_0);
      Paint_Clear(WHITE);
      // /* GUI */
      Serial.println("drawing...\r\n");
      delay(2000);
      LCD_1IN28_Clear(RED);
      delay(2000);
      LCD_1IN28_Clear(GREEN);
      delay(2000);
      LCD_1IN28_Clear(BLUE);
      delay(2000);

      // /*2.Drawing on the image*/
#if 1
      Paint_Clear(WHITE);
      Paint_DrawPoint(50, 41, BLACK, DOT_PIXEL_1X1, DOT_FILL_RIGHTUP); // 240 240
      Paint_DrawPoint(50, 46, BLACK, DOT_PIXEL_2X2, DOT_FILL_RIGHTUP);
      Paint_DrawPoint(50, 51, BLACK, DOT_PIXEL_3X3, DOT_FILL_RIGHTUP);
      Paint_DrawPoint(50, 56, BLACK, DOT_PIXEL_4X4, DOT_FILL_RIGHTUP);
      Paint_DrawPoint(50, 61, BLACK, DOT_PIXEL_5X5, DOT_FILL_RIGHTUP);

      Paint_DrawLine(60, 40, 90, 70, MAGENTA, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
      Paint_DrawLine(60, 70, 90, 40, MAGENTA, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

      Paint_DrawRectangle(60, 40, 90, 70, RED, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
      Paint_DrawRectangle(100, 40, 130, 70, BLUE, DOT_PIXEL_2X2, DRAW_FILL_FULL);

      Paint_DrawLine(135, 55, 165, 55, CYAN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
      Paint_DrawLine(150, 40, 150, 70, CYAN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);

      Paint_DrawCircle(150, 55, 15, GREEN, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
      Paint_DrawCircle(185, 55, 15, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);

      Paint_DrawNum(50, 80, 9.87654321, &Font20, 3, WHITE, BLACK);
      Paint_DrawString_EN(50, 100, "ABC", &Font20, 0x000f, 0xfff0);
      Paint_DrawString_EN(50, 161, "Waveshare", &Font16, RED, WHITE);

      // /*3.Refresh the picture in RAM to LCD*/
      LCD_1IN28_Display(BlackImage);
      DEV_Delay_ms(1000);
#endif

#if 1
      float acc[3], gyro[3];
      unsigned int tim_count = 0;
      uint16_t result;

      QMI8658_init();
      Serial.println("QMI8658_init\r\n");
      // DEV_SET_PWM(100);
      const float conversion_factor = 3.3f / (1 << 12) * 3;
      Paint_Clear(WHITE);
      Paint_DrawRectangle(0, 00, 240, 47, 0XF410, DOT_PIXEL_2X2, DRAW_FILL_FULL);
      Paint_DrawRectangle(0, 47, 240, 120, 0X4F30, DOT_PIXEL_2X2, DRAW_FILL_FULL);
      Paint_DrawRectangle(0, 120, 240, 195, 0XAD55, DOT_PIXEL_2X2, DRAW_FILL_FULL);
      Paint_DrawRectangle(0, 195, 240, 240, 0X2595, DOT_PIXEL_2X2, DRAW_FILL_FULL);

      Paint_DrawString_EN(45, 30, "LongPress Quit", &Font16, WHITE, BLACK);
      Paint_DrawString_EN(45, 50, "ACC_X = ", &Font16, WHITE, BLACK);
      Paint_DrawString_EN(45, 75, "ACC_Y = ", &Font16, WHITE, BLACK);
      Paint_DrawString_EN(45, 100, "ACC_Z = ", &Font16, WHITE, BLACK);
      Paint_DrawString_EN(45, 125, "GYR_X = ", &Font16, WHITE, BLACK);
      Paint_DrawString_EN(45, 150, "GYR_Y = ", &Font16, WHITE, BLACK);
      Paint_DrawString_EN(45, 175, "GYR_Z = ", &Font16, WHITE, BLACK);
      Paint_DrawString_EN(45, 200, "BAT(V)=", &Font16, WHITE, BLACK);
      LCD_1IN28_Display(BlackImage);
      while (true)
      {
          result = DEC_ADC_Read();
          QMI8658_read_xyz(acc, gyro, &tim_count);
          Paint_Clear(WHITE);
          Paint_DrawRectangle(120, 47,  220, 120, 0X4F30, DOT_PIXEL_2X2, DRAW_FILL_FULL);
          Paint_DrawRectangle(120, 120, 220, 195, 0XAD55, DOT_PIXEL_2X2, DRAW_FILL_FULL);
          Paint_DrawRectangle(120, 195, 220, 240, 0X2595, DOT_PIXEL_2X2, DRAW_FILL_FULL);
          Paint_DrawNum(120, 50, acc[0], &Font16, 2, BLACK, WHITE);
          Paint_DrawNum(120, 75, acc[1], &Font16, 2, BLACK, WHITE);
          Paint_DrawNum(120, 100, acc[2], &Font16, 2, BLACK, WHITE);
          Paint_DrawNum(120, 125, gyro[0], &Font16, 2, BLACK, WHITE);
          Paint_DrawNum(120, 150, gyro[1], &Font16, 2, BLACK, WHITE);
          Paint_DrawNum(120, 175, gyro[2], &Font16, 2, BLACK, WHITE);
          Paint_DrawNum(130, 200, result * conversion_factor, &Font16, 2, BLACK, WHITE);
          LCD_1IN28_DisplayWindows(120, 50, 210, 200, BlackImage);
          LCD_1IN28_DisplayWindows(130, 200, 220, 220, BlackImage);
          if (touch.available()){
            if(touch.data.y<45){
              break;
            }
          }
      }
#endif

    delay(2000);
#if 1
    Paint_Clear(WHITE);
    Paint_DrawRectangle(0, 00, 240, 47, 0x2595, DOT_PIXEL_2X2, DRAW_FILL_FULL);
    Paint_DrawString_EN(60, 30, "Touch test", &Font16, WHITE, BLACK);
    LCD_1IN28_Display(BlackImage);
    while (true)
    {
        if (touch.available()){
          Paint_DrawPoint(touch.data.x, touch.data.y, BLACK, DOT_PIXEL_3X3, DOT_FILL_RIGHTUP);
          LCD_1IN28_DisplayWindows(touch.data.x, touch.data.y, touch.data.x + 3, touch.data.y + 3, BlackImage);
        }

    }
#endif
}

void loop()
{
  delay(2);//allow the cpu to switch to other tasks
}

