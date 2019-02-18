/** 
  *@Illustrate: ������Ƶת����(BMPͼƬ���� -> BV��Ƶ�ļ�, ������Ƕ��ʽ�豸�򵥵���Ƶ����)
  *@Author: _VIFEXTech
  *@UpgradeLog:
  *		2019.2.2	v1.0 ӵ��BMP����ת BIN(��ֵ��)��RGB565��RGB888 ��Ƶ�Ĺ���,����Ƶѹ��
  *		2019.2.3	v1.1 ���RGB232����֧��
  *		2019.2.14	v1.1 ���OLEDר�ñ���֧��
 **/

#include "FileGroup.h"

int main()
{
	uint16_t Width;
	uint16_t Height;
	char FileName[FILENAME_LENGTH_MAX] = FILENAME_DEFAULT;
	uint32_t FrameNum = 0;

	uint32_t PictureNum = InitTranscoder(&Width, &Height);	
	SetVideoFileName(FileName);

	Bv_Type mode = SetTranscodeMode();
	if(mode == Bv_Type::BvType_BIN)
	{
		if(Width % 8 != 0)
			printf("(Warning : BMP Width = %d, it's not a multiple of 8!)\r\n",Width);

		float ThresholeValue = SetThresholeValue();
		printf("Start transcode video(BIN),Waiting...\r\n");
		FrameNum = BMP_CreatVideo_BIN(FileName, Width, Height, PictureNum, ThresholeValue);
	}
	else if(mode == Bv_Type::BvType_RGB565)
	{
		printf("Start transcode video(RGB565),Waiting...\r\n");
		FrameNum = BMP_CreatVideo_RGB565(FileName, Width, Height, PictureNum);
	}
	else if(mode == Bv_Type::BvType_RGB888)
	{
		printf("Start transcode video(RGB888),Waiting...\r\n");
		FrameNum = BMP_CreatVideo_RGB888(FileName, Width, Height, PictureNum);
	}
	else if(mode == Bv_Type::BvType_RGB232)
	{
		printf("Start transcode video(RGB232),Waiting...\r\n");
		FrameNum = BMP_CreatVideo_RGB232(FileName, Width, Height, PictureNum);
	}
	else if(mode == Bv_Type::BvType_OLED)
	{
		if(Width % 8 != 0)
			printf("(Warning : BMP Width = %d, it's not a multiple of 8!)\r\n",Width);

		float ThresholeValue = SetThresholeValue();
		printf("Start transcode video(OLED),Waiting...\r\n");
		FrameNum = BMP_CreatVideo_OLED(FileName, Width, Height, PictureNum, ThresholeValue);
	}

	printf("\r\n---- Convert %d Frame! ----\r\n", FrameNum);
	system("pause");
	return 0;
}
