#include "FileGroup.h"

uint32_t InitTranscoder(uint16_t *width, uint16_t *height)
{
	printf("---- Bmp Video Creater %s ----\r\n",__BV_TRANSCODER_VERISON);
	printf(" Designed by _VIFEXTexh\r\n");
	printf(" %s %s Build\r\n",__DATE__,__TIME__);
	system("pause");

	printf("Checking bmp files...\r\n");
	Sleep(500);
	uint32_t PictureNum = BMP_GetLastPictureNum();
	if(PictureNum)
		printf("Find %d bmp\r\n", PictureNum);
	else
	{
		printf("Bmp not found! Please check the file.\r\n");
		system("pause");
		exit(0);
	}

	printf("Load bmp head...\r\n");
	BitmapHeader_TypeDef Head;
	if(BMP_LoadHeader(1,&Head))
	{
		BMP_PrintHeader(&Head);
		*width = Head.Info.biWidth;
		*height = Head.Info.biHeight;
	}
	else
	{
		printf("Bmp head load error!");
		system("pause");
		exit(0);
	}

	return PictureNum;
}

void SetVideoFileName(char *FileName)
{
	printf("\r\nDefault file name:%s\r\n",FileName);
Reinput:
	printf("Use default file name?[y/N]:");
	char select;
	scanf("%c",&select);
	if(select == 'Y' || select == 'y')
	{
		printf("Use default file name...\r\n");
	}
	else if(select == 'N' || select == 'n')
	{
		printf("Input new file name(<%dBytes):",FILENAME_LENGTH_MAX);
		scanf("%s",FileName);

		printf("New file name:%s\r\n", FileName);
		system("pause");
	}
	else
	{
		printf("Error select!\r\n");
		goto Reinput;
	}
}

Bv_Type SetTranscodeMode()
{
	char c;
Reinput:
	printf("Input transcode mode(0:BIN, 1:RGB565, 2:RGB888£¬3:RGB232, 4:OLED):");
	getchar();
	scanf("%c",&c);
	switch(c)
	{
	case '0':
		printf("You selsct BIN mode\r\n");
		return Bv_Type::BvType_BIN;
		break;

	case '1':
		printf("You selsct RGB565 mode\r\n");
		return Bv_Type::BvType_RGB565;
		break;

	case '2':
		printf("You selsct RGB888 mode\r\n");
		return Bv_Type::BvType_RGB888;
		break;

	case '3':
		printf("You selsct RGB232 mode\r\n");
		return Bv_Type::BvType_RGB232;
		break;

	case '4':
		printf("You selsct OLED mode\r\n");
		return Bv_Type::BvType_OLED;
		break;

	default:
		printf("Error select!\r\n");
		goto Reinput;
		break;
	}
}

float SetThresholeValue()
{
	float thresholeValue = THRESHOLE_DEFAULT;
	printf("\r\nDefault threshole value=%0.2f\r\n", thresholeValue);
Reinput:
	printf("Use default threshole value?[y/N]:");
	char select;
	getchar();
	scanf("%c",&select);
	if(select == 'Y' || select == 'y')
	{
		printf("Use default threshole value...\r\n");
	}
	else if(select == 'N' || select == 'n')
	{
		getchar();
		printf("Input new threshole value:");
		scanf("%f",&thresholeValue);

		printf("New threshole value:%0.2f\r\n",thresholeValue);
		system("pause");
	}
	else
	{
		printf("Error select!\r\n");
		goto Reinput;
	}

	return thresholeValue;
}
