#include "FileGroup.h"

#ifdef __DEBUG_BL
#define DEBUG(format, ...) printf (format, ##__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif

#define RGB565_RED   0xF8//B1111 1000 红色分量取高5位，低位舍弃
#define RGB565_GREEN 0xFC//B1111 1100 绿色分量取高6位，低位舍弃
#define RGB565_BLUE  0xF8//B1111 1000 蓝色分量取高5位，低位舍弃

/**
  * @brief  RGB888转RGB565
  * @param  *rgb888: RGB888结构体地址
  * @retval RGB565数据
  */
static inline uint16_t RGB888ToRGB565(RGB888_TypeDef *rgb888)
{
	return ((rgb888->Red & RGB565_RED) << 8) | ((rgb888->Green & RGB565_GREEN) << 3) | ((rgb888->Blue & RGB565_BLUE) >> 3);
}

/**
  * @brief  打开指定的BMP文件
  * @param  n:指定的图片编号
  * @retval 获取到的BMP文件指针(注意，文件指针使用后必须使用fclose(fp)关闭文件，否则打开文件数量到510时无法继续打开)
  */
static FILE *BMP_Open(uint32_t n)
{
	bool ret = false;
	char path[20] = {0};
	sprintf(path, "%d.bmp", n);
	DEBUG("\r\nOpening %s...", path);
	return fopen(path, "rb");
}

/**
  * @brief  打印BMP文件信息
  * @param  *head: RGB888结构体地址
  * @retval 无
  */
void BMP_PrintHeader(BitmapHeader_TypeDef *head)
{
	printf("--- File: ---\r\n");
	printf("bfType:%d\r\n",head->File.bfType);
	printf("bfSize:%d\r\n",head->File.bfSize);
	printf("bfReserved1:%d\r\n",head->File.bfReserved1);
	printf("bfReserved2:%d\r\n",head->File.bfReserved2);
	printf("bfOffBits:%d\r\n",head->File.bfOffBits);

	printf("--- Info: ---\r\n");
	printf("biSize:%d\r\n",head->Info.biSize);
	printf("biWidth:%d\r\n",head->Info.biWidth);
	printf("biHeight:%d\r\n",head->Info.biHeight);
	printf("biPlanes:%d\r\n",head->Info.biPlanes);
	printf("biBitCount:%d\r\n",head->Info.biBitCount);
	printf("biCompression:%d\r\n",head->Info.biCompression);
	printf("biSizeImage:%d\r\n",head->Info.biSizeImage);
	printf("biXPelsPerMeter:%d\r\n",head->Info.biXPelsPerMeter);
	printf("biYPelsPerMeter:%d\r\n",head->Info.biYPelsPerMeter);
	printf("biClrUsed:%d\r\n",head->Info.biClrUsed);
	printf("biClrImportant:%d\r\n",head->Info.biClrImportant);
}

/**
  * @brief  打印BMP文件信息
  * @param  n:指定的图片编号
  * @retval true:成功 false:失败
  */
bool BMP_PrintHeader(uint32_t n)
{
	bool ret = false;
	BitmapHeader_TypeDef Head;
	if(BMP_LoadHeader(1,&Head))
	{
		BMP_PrintHeader(&Head);
		ret = true;
	}

	return ret;
}

/**
  * @brief  加载指定BMP文件的头信息
  * @param  n:指定的图片编号
  * @param  *head: RGB888结构体地址
  * @retval true:成功 false:失败
  */
bool BMP_LoadHeader(uint32_t n, BitmapHeader_TypeDef *head)
{
	bool ret = false;
	FILE *BmpFile = BMP_Open(n);
	if(BmpFile)
	{
		fread(head, sizeof(BitmapHeader_TypeDef), 1, BmpFile);
		fclose(BmpFile);
		ret = true;
		DEBUG("OK\r\n");
	}
	else
	{
		ret = false;
		DEBUG("Error\r\n");
	}

	return ret;
}

/**
  * @brief  获取最后一张图片的编号
  * @param  无
  * @retval 图片编号
  */
uint32_t BMP_GetLastPictureNum()
{
	uint32_t ret = 0, num = 1;
	uint32_t starttime = clock();
	while(true)
	{
		FILE *BmpFile = BMP_Open(num);
		if(BmpFile)//加载一张BMP图片,并判断是否为最后一张图片
		{
			fclose(BmpFile);
			DEBUG(" OK", num);
			num++;
		}
		else
		{
			ret = num - 1;
			DEBUG(" END\r\n",ret);
			printf("(use %d ms)\r\n", clock() - starttime);
			break;
		}
	}
	return ret;
}

/**
  * @brief  加载一张BMP图片到指定缓冲区(RGB565格式)，作为视频的一帧
  * @param  n: 图片编号
  * @param  *picture: 缓冲区地址
  * @param  picsize: 缓冲区大小
  * @retval true:成功 false:失败
  */
bool BMP_LoadToBuffer_RGB565(uint32_t n, uint16_t *picture, uint32_t picsize)
{
	bool ret = false;
	FILE *BmpFile = BMP_Open(n);
	if(BmpFile)
	{
		fseek(BmpFile, sizeof(BitmapHeader_TypeDef), SEEK_SET);//跳过文件头
		for(uint32_t i = picsize; i > 0; i--)//遍历当前BMP图片文件的每个像素
		{
			RGB888_TypeDef rgb888;
			fread(&rgb888, sizeof(rgb888), 1, BmpFile);
			picture[i - 1] = RGB888ToRGB565(&rgb888);//RGB888转RGB565
		}
		fclose(BmpFile);
		ret = true;
		DEBUG("OK");
	}
	else
	{
		ret = false;
		DEBUG("END\r\n");
	}

	return ret;
}

/**
  * @brief  加载一张BMP图片到指定缓冲区(RGB888格式)，作为视频的一帧
  * @param  n: 图片编号
  * @param  *picture: 缓冲区地址
  * @param  picsize: 缓冲区大小
  * @retval true:成功 false:失败
  */
bool BMP_LoadToBuffer_RGB888(uint32_t n, RGB888_TypeDef *picture, uint32_t picsize)
{
	bool ret = false;
	FILE *BmpFile = BMP_Open(n);
	if(BmpFile)
	{
		fseek(BmpFile, sizeof(BitmapHeader_TypeDef), SEEK_SET);//跳过文件头
		for(uint32_t i = picsize; i > 0; i--)//遍历当前BMP图片文件的每个像素
		{
			fread(&picture[i - 1], sizeof(RGB888_TypeDef), 1, BmpFile);
		}
		fclose(BmpFile);
		ret = true;
		DEBUG("OK");
	}
	else
	{
		ret = false;
		DEBUG("END\r\n");
	}

	return ret;
}
