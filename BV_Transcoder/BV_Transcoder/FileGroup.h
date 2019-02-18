#ifndef __FILEGROUP_H
#define __FILEGROUP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <Windows.h>
#include "BmpType.h"
#include "BvType.h"
#include "binary.h"

#define __BV_TRANSCODER_VERISON "v1.2"
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define SIZE(arr) (sizeof(arr)/sizeof(arr[0]))
#define FILENAME_LENGTH_MAX 50//默认文件名最大长度
#define FILENAME_DEFAULT "NewVID"//默认文件名
#define THRESHOLE_DEFAULT 0.5//默认二值化阈值

//#define __DEBUG_BL
//#define __DEBUG_BB
//#define __DEBUG_BVC
//#define __DEBUG_BVCP

/**************** Public Functions ****************/
/*** BmpLoader.cpp ***/
void BMP_PrintHeader(BitmapHeader_TypeDef *head);
bool BMP_LoadToBuffer_RGB565(uint32_t n, uint16_t *picture, uint32_t picsize);
bool BMP_LoadToBuffer_RGB888(uint32_t n, RGB888_TypeDef *picture, uint32_t picsize);
bool BMP_LoadHeader(uint32_t n, BitmapHeader_TypeDef *head);
uint32_t BMP_GetLastPictureNum();

/*** BmpVideoCreater.cpp ***/
uint32_t BMP_CreatVideo_RGB565(char* name, uint16_t width, uint16_t height, uint32_t num);
uint32_t BMP_CreatVideo_RGB888(char* name, uint16_t width, uint16_t height, uint32_t num);
uint32_t BMP_CreatVideo_RGB232(char* name, uint16_t width, uint16_t height, uint32_t num);

/*** BmpBinaryzation.cpp ***/
uint32_t BMP_CreatVideo_BIN(char *name, uint16_t width, uint16_t height, uint32_t num, float thresholeValue);
uint32_t BMP_CreatVideo_OLED(char *name, uint16_t width, uint16_t height, uint32_t num, float thresholeValue);

/*** Common.cpp ***/
uint32_t GetFileSize(char* filename);

/*** Interation.cpp ***/
uint32_t InitTranscoder(uint16_t *width, uint16_t *height);
void SetVideoFileName(char *FileName);
Bv_Type SetTranscodeMode();
float SetThresholeValue();

#endif
