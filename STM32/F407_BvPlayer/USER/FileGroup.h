#ifndef __FILEGROUP_H
#define	__FILEGROUP_H

/** 
  *@Illustrate: A Cross-platform migration Project | Arduino for STM32F4xx 
  *@Author: FASTSHIFT
  *@Website: https://github.com/FASTSHIFT/Arduino-For-Keil
  */

//************* Arduino Library **************//
#include "Arduino.h"
#include "HardwareSerial.h"
#include "Stream.h"
//#include "SPI.h"
#include "Tone.h"
#include "WString.h"
#include "Wire.h"
#include "WMath.h"

//************* STM32 Core Library **************//
#include "adc.h"
#include "delay.h"
#include "exti.h"
#include "gpio.h"
#include "pwm.h"
#include "timer.h"

#define SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

//**************** User Library *****************//

#define Key_Pin PA0
#define InfoLED_Pin PA1

#define FLASH_SCK_Pin PB3
#define FLASH_MISO_Pin PB4
#define FLASH_MOSI_Pin PB5
#define FLASH_CS_Pin PA15

#define SDIO_D0_Pin PC8
#define SDIO_D1_Pin PC9
#define SDIO_D2_Pin PC10
#define SDIO_D3_Pin PC11
#define SDIO_SCK_Pin PC12
#define SDIO_CMD_Pin PD2

#define SD_CS_Pin   SDIO_D3_Pin
#define SD_SCK_Pin  SDIO_SCK_Pin
#define SD_MOSI_Pin SDIO_CMD_Pin
#define SD_MISO_Pin SDIO_D0_Pin

#define TFT_DC PA3
#define TFT_CS PA2
#define TFT_MOSI PA7
#define TFT_CLK PA5
#define TFT_RST PA4
#define TFT_BLK PA1

//***************** Extern *********************//

//***************** Functions *****************//
bool Init_SD();
void Init_TFT();
void Init_OLED();
float TFT_PlayVideo(char* path);
float OLED_PlayVideo(char* path);

#endif
