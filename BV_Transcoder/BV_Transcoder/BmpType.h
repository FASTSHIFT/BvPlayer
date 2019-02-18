#ifndef __BMPTYPE_H
#define __BMPTYPE_H

#include <stdint.h>

#pragma pack (1) //��һ���ֽڶ���

typedef struct tagBitmapFileHeader{
	uint16_t bfType;//λͼ�ļ������ͣ�����ΪBM(1-2�ֽڣ�
	uint32_t bfSize;//λͼ�ļ��Ĵ�С�����ֽ�Ϊ��λ��3-6�ֽڣ���λ��ǰ��
	uint16_t bfReserved1;//λͼ�ļ������֣�����Ϊ0(7-8�ֽڣ�
	uint16_t bfReserved2;//λͼ�ļ������֣�����Ϊ0(9-10�ֽڣ�
	uint32_t bfOffBits;//λͼ���ݵ���ʼλ�ã��������λͼ��11-14�ֽڣ���λ��ǰ��
	//�ļ�ͷ��ƫ������ʾ�����ֽ�Ϊ��λ
}BitmapFileHeader_TypeDef;

typedef struct tagBitmapInfoHeader{
	uint32_t biSize;//���ṹ��ռ���ֽ�����15-18�ֽڣ�
	int32_t biWidth;//λͼ�Ŀ�ȣ�������Ϊ��λ��19-22�ֽڣ�
	int32_t biHeight;//λͼ�ĸ߶ȣ�������Ϊ��λ��23-26�ֽڣ�
	uint16_t biPlanes;//Ŀ���豸�ļ��𣬱���Ϊ1(27-28�ֽڣ�
	uint16_t biBitCount;//ÿ�����������λ����������1��˫ɫ������29-30�ֽڣ�
	//4(16ɫ����8(256ɫ��16(�߲�ɫ)��24�����ɫ��֮һ
	uint32_t biCompression;//λͼѹ�����ͣ�������0����ѹ��������31-34�ֽڣ�
	//1(BI_RLE8ѹ�����ͣ���2(BI_RLE4ѹ�����ͣ�֮һ
	uint32_t biSizeImage;//λͼ�Ĵ�С(���а�����Ϊ�˲���������4�ı�������ӵĿ��ֽ�)�����ֽ�Ϊ��λ��35-38�ֽڣ�
	int32_t biXPelsPerMeter;//λͼˮƽ�ֱ��ʣ�ÿ����������39-42�ֽڣ�
	int32_t biYPelsPerMeter;//λͼ��ֱ�ֱ��ʣ�ÿ����������43-46�ֽ�)
	uint32_t biClrUsed;//λͼʵ��ʹ�õ���ɫ���е���ɫ����47-50�ֽڣ�
	uint32_t biClrImportant;//λͼ��ʾ��������Ҫ����ɫ����51-54�ֽڣ�
}BitmapInfoHeader_TypeDef;

typedef struct tagBitmapHeader{
	BitmapFileHeader_TypeDef File;
	BitmapInfoHeader_TypeDef Info;
}BitmapHeader_TypeDef;

typedef struct tagRGB888{
	uint8_t Red;//��ɫ����
	uint8_t Green;//��ɫ����
	uint8_t Blue;//��ɫ����
}RGB888_TypeDef;

#pragma pack() //�������ֽڶ���

#endif
