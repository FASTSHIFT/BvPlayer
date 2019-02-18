#include "FileGroup.h"

#ifdef __DEBUG_BVC
#define DEBUG(format, ...) printf (format, ##__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif


/**
  * @brief  在所在目录生成Bmp视频文件(RGB565)(*.bv)
  * @param  *name: 文件名
  * @param  width: 帧宽
  * @param  height: 帧高
  * @param  num: 总帧数
  * @retval 视频文件实际总帧数
  */
uint32_t BMP_CreatVideo_RGB565(char* name, uint16_t width, uint16_t height, uint32_t num)
{
	uint32_t ret = 0;
	uint16_t *Picture = new uint16_t[width * height];	

	char path[50] = {0};
	sprintf(path, "%s.bv", name);
	DEBUG("Creat:%s...\r\n",path);
	Sleep(500);

	uint32_t starttime = clock();
	FILE *BvFile = fopen(path, "wb+");
	if(BvFile)
	{
		BvHeader_TypeDef Head;
		Head.Type = BvType::BvType_RGB565;
		Head.FrameNum = num;
		Head.Width = width;
		Head.Height = height;
		fwrite(&Head, sizeof(BvHeader_TypeDef), 1, BvFile);//写入头信息

		uint32_t i;
		for(i = 1; i <= num; i++)
		{
			if(BMP_LoadToBuffer_RGB565(i, Picture, width * height))//加载一张BMP图片,并判断是否为最后一张图片
			{
				fwrite(Picture, sizeof(uint16_t) * width * height, 1, BvFile);//往视频文件写入一帧数据
				DEBUG(" (%d/%d %0.2f%%)", i, num, (float)i / num * 100.0);
			}
			else 
				break;
		}
		ret = i - 1;
		fclose(BvFile);
		uint32_t endtime = clock() - starttime;
		printf("\r\nCreat %s finished!\r\n", path);
		printf("(use %d ms)\r\n", endtime);
		printf("Speed: %0.2f fps\r\n",(float)ret * 1000.0 / endtime);
		uint32_t size = GetFileSize(path);
		if(size)
			printf("Size: %0.2f MB (%dB) @%dx%d\r\n", (float)size / 1024.0 / 1024.0, size, Head.Width, Head.Height);
		
	}
	else
		DEBUG("%s Error opening\r\n", path);

	delete[] Picture;
	
	return ret;
}

/**
  * @brief  在所在目录生成Bmp视频文件(RGB888)(*.bv)
  * @param  *name: 文件名
  * @param  width: 帧宽
  * @param  height: 帧高
  * @param  num: 总帧数
  * @retval 视频文件实际总帧数
  */
uint32_t BMP_CreatVideo_RGB888(char* name, uint16_t width, uint16_t height, uint32_t num)
{
	uint32_t ret = 0;
	RGB888_TypeDef *Picture = new RGB888_TypeDef[width * height];	

	char path[50] = {0};
	sprintf(path, "%s.bv", name);
	DEBUG("Creat:%s...\r\n",path);
	Sleep(500);

	uint32_t starttime = clock();
	FILE *BvFile = fopen(path, "wb+");
	if(BvFile)
	{
		BvHeader_TypeDef Head;
		Head.Type = BvType::BvType_RGB888;
		Head.FrameNum = num;
		Head.Width = width;
		Head.Height = height;
		fwrite(&Head, sizeof(BvHeader_TypeDef), 1, BvFile);//写入头信息

		uint32_t i;
		for(i = 1; i <= num; i++)
		{
			if(BMP_LoadToBuffer_RGB888(i, Picture, width * height))//加载一张BMP图片,并判断是否为最后一张图片
			{
				fwrite(Picture, sizeof(RGB888_TypeDef) * width * height, 1, BvFile);//往视频文件写入一帧数据
				DEBUG(" (%d/%d %0.2f%%)", i, num, (float)i / num * 100.0);
			}
			else 
				break;
		}
		ret = i - 1;
		fclose(BvFile);
		uint32_t endtime = clock() - starttime;
		printf("\r\nCreat %s finished!\r\n", path);
		printf("(use %d ms)\r\n", endtime);
		printf("Speed: %0.2f fps\r\n",(float)ret * 1000.0 / endtime);
		uint32_t size = GetFileSize(path);
		if(size)
			printf("Size: %0.2f MB (%dB) @%dx%d\r\n", (float)size / 1024.0 / 1024.0, size, Head.Width, Head.Height);
		
	}
	else
		DEBUG("%s Error opening\r\n", path);

	delete[] Picture;
	
	return ret;
}
