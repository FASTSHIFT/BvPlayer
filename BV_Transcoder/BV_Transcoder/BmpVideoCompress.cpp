#include "FileGroup.h"

//RGB232:0RRGGGBB
//RGB565:RRrrrGGGgggBBbbb
//��д������һ֡����
//Сд����ǰһ֡����λ����

#ifdef __DEBUG_BVCP
#define DEBUG(format, ...) printf (format, ##__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif

//����:
//1.����һ֡ͼƬ(RGB888),RGBȡ��λ(RRRRRRRRR->RR000000, GGGGGGGG->GGG00000, BBBBBBBB->BB000000)
//2.��λ��ƴ�ӳ�RGB232(R>>1|G>>3|B>>6)
//3.RGB232�������ļ�

//����:
//1.������һ֡����(RGB232),RGB��λתRGB565(0RRGGGBB -> RR000GGG000BB000)
//2.����һ֡����(RGB565),RGB��λ�ֱ������λ(RRRRRGGGGGGBBBBB -> 00rrr000ggg00bbb)
//3.��֡����(RGB565),(RR000GGG000BB000 | 00rrr000ggg00bbb = RRrrrGGGgggBBbbb)
//5.������һ֡
//4.��ʾ����Ļ

static void RGB888ToRGB232(RGB888_TypeDef *rgb888, uint8_t *rgb232, uint32_t size)
{
	for(uint32_t i = 0; i < size; i++)
	{
		uint8_t R = rgb888[i].Red   & B11000000;
		uint8_t G = rgb888[i].Green & B11100000;
		uint8_t B = rgb888[i].Blue  & B11000000;
		rgb232[i] = (uint8_t)(R >> 1 | G >> 3 | B >> 6);
	}
}

uint32_t BMP_CreatVideo_RGB232(char* name, uint16_t width, uint16_t height, uint32_t num)
{
	uint32_t ret = 0;
	RGB888_TypeDef *rgb888Pic = new RGB888_TypeDef[width * height];
	uint8_t  *rgb232Pic = new uint8_t[width * height];

	char path[50] = {0};
	sprintf(path, "%s.bv", name);
	DEBUG("Creat:%s...\r\n",path);
	Sleep(500);

	uint32_t starttime = clock();
	FILE *BvFile = fopen(path, "wb+");
	if(BvFile)
	{
		BvHeader_TypeDef Head;
		Head.Type = BvType::BvType_RGB232;
		Head.FrameNum = num;
		Head.Width = width;
		Head.Height = height;
		fwrite(&Head, sizeof(BvHeader_TypeDef), 1, BvFile);//д��ͷ��Ϣ

		uint32_t i;
		for(i = 1; i <= num; i++)
		{
			if(BMP_LoadToBuffer_RGB888(i, rgb888Pic, width * height))//����һ��BMPͼƬ,���ж��Ƿ�Ϊ���һ��ͼƬ
			{
				RGB888ToRGB232(rgb888Pic, rgb232Pic, width * height);
				fwrite(rgb232Pic, width * height, 1, BvFile);//����Ƶ�ļ�д��һ֡����
				DEBUG(" (%d/%d %0.2f%%)\r\n", i, num, (float)i / num * 100.0);
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

	delete[] rgb888Pic;
	delete[] rgb232Pic;
	
	return ret;
}
