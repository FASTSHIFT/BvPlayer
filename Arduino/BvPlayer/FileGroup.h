#ifndef __FILEGROUP_H
#define __FILEGROUP_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

/* GPIO Define */
#define OLED_DC     4
#define OLED_CS     9
#define OLED_RST    6

#define NRF_MOSI_Pin 16
#define NRF_MISO_Pin 14
#define NRF_SCK_Pin 15
#define NRF_CE_Pin 2
#define NRF_CSN_Pin 10
#define NRF_IRQ_Pin -1

#define Key_UP_Pin A0
#define Key_RIGHT_Pin A1
#define Key_DOWN_Pin A3
#define Key_LEFT_Pin A2
#define Key_A_Pin 7
#define Key_B_Pin 8
#define SD_CS_Pin 3
#define Buzz_Pin 5

/* Values & Objects & Structs*/
extern Adafruit_SSD1306 oled;

/* Others Define */
typedef enum {Off = 0, On = !Off} Switch_TypeDef;
template<class T> inline Print& operator << (Print &obj, T arg) {
  obj.print(arg);
  return obj;
}

#define Serial Serial1

/* Functions */
void Init_SD();
void Init_OLED();
float OLED_PlayVideo(char* path);

#endif

