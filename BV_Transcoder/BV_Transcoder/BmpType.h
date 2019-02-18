#ifndef __BMPTYPE_H
#define __BMPTYPE_H

#include <stdint.h>

#pragma pack (1) //按一个字节对齐

typedef struct tagBitmapFileHeader{
	uint16_t bfType;//位图文件的类型，必须为BM(1-2字节）
	uint32_t bfSize;//位图文件的大小，以字节为单位（3-6字节，低位在前）
	uint16_t bfReserved1;//位图文件保留字，必须为0(7-8字节）
	uint16_t bfReserved2;//位图文件保留字，必须为0(9-10字节）
	uint32_t bfOffBits;//位图数据的起始位置，以相对于位图（11-14字节，低位在前）
	//文件头的偏移量表示，以字节为单位
}BitmapFileHeader_TypeDef;

typedef struct tagBitmapInfoHeader{
	uint32_t biSize;//本结构所占用字节数（15-18字节）
	int32_t biWidth;//位图的宽度，以像素为单位（19-22字节）
	int32_t biHeight;//位图的高度，以像素为单位（23-26字节）
	uint16_t biPlanes;//目标设备的级别，必须为1(27-28字节）
	uint16_t biBitCount;//每个像素所需的位数，必须是1（双色），（29-30字节）
	//4(16色），8(256色）16(高彩色)或24（真彩色）之一
	uint32_t biCompression;//位图压缩类型，必须是0（不压缩），（31-34字节）
	//1(BI_RLE8压缩类型）或2(BI_RLE4压缩类型）之一
	uint32_t biSizeImage;//位图的大小(其中包含了为了补齐行数是4的倍数而添加的空字节)，以字节为单位（35-38字节）
	int32_t biXPelsPerMeter;//位图水平分辨率，每米像素数（39-42字节）
	int32_t biYPelsPerMeter;//位图垂直分辨率，每米像素数（43-46字节)
	uint32_t biClrUsed;//位图实际使用的颜色表中的颜色数（47-50字节）
	uint32_t biClrImportant;//位图显示过程中重要的颜色数（51-54字节）
}BitmapInfoHeader_TypeDef;

typedef struct tagBitmapHeader{
	BitmapFileHeader_TypeDef File;
	BitmapInfoHeader_TypeDef Info;
}BitmapHeader_TypeDef;

typedef struct tagRGB888{
	uint8_t Red;//红色分量
	uint8_t Green;//绿色分量
	uint8_t Blue;//蓝色分量
}RGB888_TypeDef;

#pragma pack() //按正常字节对齐

#endif
