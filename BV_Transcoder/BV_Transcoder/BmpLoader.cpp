#include "FileGroup.h"

#ifdef __DEBUG_BL
#define DEBUG(format, ...) printf (format, ##__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif

#define RGB565_RED   0xF8//B1111 1000 ��ɫ����ȡ��5λ����λ����
#define RGB565_GREEN 0xFC//B1111 1100 ��ɫ����ȡ��6λ����λ����
#define RGB565_BLUE  0xF8//B1111 1000 ��ɫ����ȡ��5λ����λ����

/**
  * @brief  RGB888תRGB565
  * @param  *rgb888: RGB888�ṹ���ַ
  * @retval RGB565����
  */
static inline uint16_t RGB888ToRGB565(RGB888_TypeDef *rgb888)
{
	return ((rgb888->Red & RGB565_RED) << 8) | ((rgb888->Green & RGB565_GREEN) << 3) | ((rgb888->Blue & RGB565_BLUE) >> 3);
}

/**
  * @brief  ��ָ����BMP�ļ�
  * @param  n:ָ����ͼƬ���
  * @retval ��ȡ����BMP�ļ�ָ��(ע�⣬�ļ�ָ��ʹ�ú����ʹ��fclose(fp)�ر��ļ���������ļ�������510ʱ�޷�������)
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
  * @brief  ��ӡBMP�ļ���Ϣ
  * @param  *head: RGB888�ṹ���ַ
  * @retval ��
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
  * @brief  ��ӡBMP�ļ���Ϣ
  * @param  n:ָ����ͼƬ���
  * @retval true:�ɹ� false:ʧ��
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
  * @brief  ����ָ��BMP�ļ���ͷ��Ϣ
  * @param  n:ָ����ͼƬ���
  * @param  *head: RGB888�ṹ���ַ
  * @retval true:�ɹ� false:ʧ��
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
  * @brief  ��ȡ���һ��ͼƬ�ı��
  * @param  ��
  * @retval ͼƬ���
  */
uint32_t BMP_GetLastPictureNum()
{
	uint32_t ret = 0, num = 1;
	uint32_t starttime = clock();
	while(true)
	{
		FILE *BmpFile = BMP_Open(num);
		if(BmpFile)//����һ��BMPͼƬ,���ж��Ƿ�Ϊ���һ��ͼƬ
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
  * @brief  ����һ��BMPͼƬ��ָ��������(RGB565��ʽ)����Ϊ��Ƶ��һ֡
  * @param  n: ͼƬ���
  * @param  *picture: ��������ַ
  * @param  picsize: ��������С
  * @retval true:�ɹ� false:ʧ��
  */
bool BMP_LoadToBuffer_RGB565(uint32_t n, uint16_t *picture, uint32_t picsize)
{
	bool ret = false;
	FILE *BmpFile = BMP_Open(n);
	if(BmpFile)
	{
		fseek(BmpFile, sizeof(BitmapHeader_TypeDef), SEEK_SET);//�����ļ�ͷ
		for(uint32_t i = picsize; i > 0; i--)//������ǰBMPͼƬ�ļ���ÿ������
		{
			RGB888_TypeDef rgb888;
			fread(&rgb888, sizeof(rgb888), 1, BmpFile);
			picture[i - 1] = RGB888ToRGB565(&rgb888);//RGB888תRGB565
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
  * @brief  ����һ��BMPͼƬ��ָ��������(RGB888��ʽ)����Ϊ��Ƶ��һ֡
  * @param  n: ͼƬ���
  * @param  *picture: ��������ַ
  * @param  picsize: ��������С
  * @retval true:�ɹ� false:ʧ��
  */
bool BMP_LoadToBuffer_RGB888(uint32_t n, RGB888_TypeDef *picture, uint32_t picsize)
{
	bool ret = false;
	FILE *BmpFile = BMP_Open(n);
	if(BmpFile)
	{
		fseek(BmpFile, sizeof(BitmapHeader_TypeDef), SEEK_SET);//�����ļ�ͷ
		for(uint32_t i = picsize; i > 0; i--)//������ǰBMPͼƬ�ļ���ÿ������
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
