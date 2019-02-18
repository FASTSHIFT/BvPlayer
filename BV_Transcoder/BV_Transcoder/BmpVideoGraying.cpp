#include "FileGroup.h"

/*
 *2至20位精度灰度转换表：
 *Gray = (R*1 + G*2 + B*1) >> 2
 *Gray = (R*2 + G*5 + B*1) >> 3
 *Gray = (R*4 + G*10 + B*2) >> 4
 *Gray = (R*9 + G*19 + B*4) >> 5
 *Gray = (R*19 + G*37 + B*8) >> 6
 *Gray = (R*38 + G*75 + B*15) >> 7
 *Gray = (R*76 + G*150 + B*30) >> 8
 *Gray = (R*153 + G*300 + B*59) >> 9
 *Gray = (R*306 + G*601 + B*117) >> 10
 *Gray = (R*612 + G*1202 + B*234) >> 11
 *Gray = (R*1224 + G*2405 + B*467) >> 12
 *Gray = (R*2449 + G*4809 + B*934) >> 13
 *Gray = (R*4898 + G*9618 + B*1868) >> 14
 *Gray = (R*9797 + G*19235 + B*3736) >> 15
 *Gray = (R*19595 + G*38469 + B*7472) >> 16
 *Gray = (R*39190 + G*76939 + B*14943) >> 17
 *Gray = (R*78381 + G*153878 + B*29885) >> 18
 *Gray = (R*156762 + G*307757 + B*59769) >> 19
 *Gray = (R*313524 + G*615514 + B*119538) >> 20
 */

const uint32_t GrayMap[19][3]={
	{1, 2, 1},//2
	{2, 5, 1},//3
	{4, 10, 2},//4
	{9, 19, 4},//5
	{19, 37, 8},//6
	{38, 75, 15},//7
	{76, 150, 30},//8
};

inline uint32_t RGB888ToGray(RGB888_TypeDef *rgb888, uint8_t precision)
{
	return (
	  rgb888->Red   * GrayMap[precision - 2][0] 
	+ rgb888->Green * GrayMap[precision - 2][1]
	+ rgb888->Blue  * GrayMap[precision - 2][2]
	);
}
