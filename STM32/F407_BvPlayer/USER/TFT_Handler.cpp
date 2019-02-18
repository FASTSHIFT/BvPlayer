#include "FileGroup.h"
#include "Adafruit_ST7735.h"
#include "BV_Player.h"

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);

BV_Player tftPlayer(128 * 64 * 2);

void TFT_FastDrawRGBBitmap(uint16_t *bitmap, BvHeader_TypeDef* head)
{
    uint32_t size = head->Width * head->Height;
    tft.setAddrWindow(0, 0, head->Width - 1, head->Height - 1);
    for(uint32_t i = 0; i < size; i++)
        tft.pushColor(bitmap[i]);
    togglePin(InfoLED_Pin);
}

void TFT_FastDrawBitmap(uint8_t *bitmap, BvHeader_TypeDef* head)
{
    tft.setAddrWindow(0, 0, head->Width - 1, head->Height - 1);

    int16_t byteWidth = (head->Width + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t b = 0;

    for(int16_t j = 0; j < head->Height; j++)
    {
        for(int16_t i = 0; i < head->Width; i++ )
        {
            if(i & 7) b <<= 1;
            else      b   = bitmap[j * byteWidth + i / 8];
            tft.pushColor((b & 0x80) ? ST7735_BLUE : ST7735_BLACK);
        }
    }
    togglePin(InfoLED_Pin);
}

void Init_TFT()
{
    tft.initR(INITR_MINI128x64);
    tft.invertDisplay(false);
    tft.fillScreen(ST7735_BLACK);

    tftPlayer.CallBackDrawPicture_u16 = TFT_FastDrawRGBBitmap;
    tftPlayer.CallBackDrawPicture_u8  = TFT_FastDrawBitmap;
}

float TFT_PlayVideo(char* path)
{
    return tftPlayer.PlayVideo(path);
}
