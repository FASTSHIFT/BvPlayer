#include "FileGroup.h"


#ifdef __DEBUG_BB
#define DEBUG(format, ...) printf (format, ##__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif

/**
  * @brief  将RGB565压缩成二值化图像，1个字节存8个像素
  * @param  *u16pic: RGB565图片缓冲区地址
  * @param  u16picsize: RGB565图片缓冲区大小
  * @param  *u8pic: 二值化图片缓冲区地址
  * @param  u8picsize: 二值化图片缓冲区大小
  * @param  threshole: 二值化阈值(0.0~1.0)
  * @retval 无
  */
static void CompressPicture(uint16_t *u16pic, uint32_t u16picsize, uint8_t *u8pic, uint32_t u8picsize, float threshole)
{
    for(uint32_t i = 0; i < u8picsize; i++)
    {
        for(uint8_t j = 0; j < 8; j++)
        {
            if((i * 8 + j) == u16picsize) return;
            if(u16pic[i * 8 + j] > 0xFFFF * threshole)//二值化图像
            {
                bitSet(u8pic[i], 7 - j);
            }
            else
            {
                bitClear(u8pic[i], 7 - j);
            }
            //printf("i=%d,j=%d,p=%d\r\n",i,j,(i * 8 + j));
        }
    }
}

/**
  * @brief  在所在目录生成二值化视频文件(*.bv)
  * @param  *name: 文件名
  * @param  width: 帧宽
  * @param  height: 帧高
  * @param  num: 总帧数
  * @param  thresholeValue: 二值化阈值(0.0 ~ 1.0)
  * @retval 视频文件总帧数
  */
uint32_t BMP_CreatVideo_BIN(char *name, uint16_t width, uint16_t height, uint32_t num, float thresholeValue)
{
    uint32_t ret = 0;
    uint16_t *u16Picture = new uint16_t[width * height];//RGB565图片缓冲区
    uint8_t *u8Picture = new uint8_t[width * height / 8];//二值化图片缓冲区

    char path[50] = {0};
    sprintf(path, "%s.bv", name);
    printf("Creat:%s...\r\n",path);

	uint32_t starttime = clock();
    FILE *BvFile = fopen(path, "wb+");
	if(BvFile)
    {
		BvHeader_TypeDef Head;
		Head.Type = BvType::BvType_BIN;
		Head.FrameNum = num;
		Head.Width = width;
		Head.Height = height;
		fwrite(&Head, sizeof(BvHeader_TypeDef), 1, BvFile);//写入头信息

        uint32_t i = 1;//图片编号从1开始
		for(i = 1; i <= num; i++)
		{
			if(BMP_LoadToBuffer_RGB565(i, u16Picture, width * height))//加载一张BMP图片,并判断是否为最后一张图片
			{
				CompressPicture(u16Picture, width * height, u8Picture, width * height / 8, thresholeValue);//压缩图片二值化
				fwrite(u8Picture, width * height / 8, 1, BvFile);//往视频文件写入一帧数据
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
        printf("%s Error opening\r\n", path);

    delete[] u16Picture;
    delete[] u8Picture;

    return ret;
}

/**
  * @brief  将RGB565压缩成OLED二值化图像，1个字节存8个像素
  * @param  threshole: 二值化阈值(0.0~1.0)
  * @retval 无
  */
static void CompressPicture_OLED(
	uint16_t *u16pic, uint8_t  *u8pic,  
	uint16_t width,  uint16_t height,
	float threshole
)
{
    for(uint16_t x = 0; x < width; x++)
    {
        for(uint16_t y = 0; y < height; y++)
        {
            if(u16pic[width * y + x] > 0xFFFF * threshole)//二值化图像
            {
				u8pic[x + (y / 8)*width] |=  (1 << (y & 7));
            }
            else
            {
				u8pic[x + (y / 8)*width] &= ~(1 << (y & 7));
            }
        }
    }
}

/**
  * @brief  在所在目录生成二值化OLED视频文件(*.bv)
  * @param  *name: 文件名
  * @param  width: 帧宽
  * @param  height: 帧高
  * @param  num: 总帧数
  * @param  thresholeValue: 二值化阈值(0.0 ~ 1.0)
  * @retval 视频文件总帧数
  */
uint32_t BMP_CreatVideo_OLED(char *name, uint16_t width, uint16_t height, uint32_t num, float thresholeValue)
{
    uint32_t ret = 0;
    uint16_t *u16Picture = new uint16_t[width * height];//RGB565图片缓冲区
    uint8_t *u8Picture = new uint8_t[width * height / 8];//二值化图片缓冲区

    char path[50] = {0};
    sprintf(path, "%s.bv", name);
    printf("Creat:%s...\r\n",path);

	uint32_t starttime = clock();
    FILE *BvFile = fopen(path, "wb+");
	if(BvFile)
    {
		BvHeader_TypeDef Head;
		Head.Type = BvType::BvType_OLED;
		Head.FrameNum = num;
		Head.Width = width;
		Head.Height = height;
		fwrite(&Head, sizeof(BvHeader_TypeDef), 1, BvFile);//写入头信息

        uint32_t i = 1;//图片编号从1开始
		for(i = 1; i <= num; i++)
		{
			if(BMP_LoadToBuffer_RGB565(i, u16Picture, width * height))//加载一张BMP图片,并判断是否为最后一张图片
			{
				CompressPicture_OLED(u16Picture, u8Picture, width, height, thresholeValue);//压缩图片二值化
				fwrite(u8Picture, width * height / 8, 1, BvFile);//往视频文件写入一帧数据
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
        printf("%s Error opening\r\n", path);

    delete[] u16Picture;
    delete[] u8Picture;

    return ret;
}
