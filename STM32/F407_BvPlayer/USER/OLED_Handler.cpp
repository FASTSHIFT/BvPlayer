#include "FileGroup.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_PCD8544.h"
#include "BV_Player.h"

#define OLED_SDA PA7
#define OLED_SCL PA5
#define OLED_DC  PA4
#define OLED_RST PA3
#define OLED_CS  PA2
Adafruit_SSD1306 oled(OLED_SDA, OLED_SCL, OLED_DC, OLED_RST, OLED_CS);
//Adafruit_SSD1306 oled(-1);

//Adafruit_PCD8544 lcd(PA7, PA6, PA5, PA4, PA3);
//// PA7 - Serial clock out (SCLK)
//// PA6 - Serial data out (DIN)
//// PA5 - Data/Command select (D/C)
//// PA4 - LCD chip select (CS)
//// PA3 - LCD reset (RST)

BV_Player oledPlayer(128 * 64 / 8);

//extern void TFT_FastDrawBitmap(uint8_t *bitmap, BvHeader_TypeDef* head);

void OLED_FastDrawBitmap(uint8_t *bitmap, BvHeader_TypeDef* head)
{
    //TFT_FastDrawBitmap(bitmap, head);

    oled.drawBitmap(0, 0, bitmap, head->Width, head->Height, oled.WHITE, oled.BLACK);
    oled.display();
    togglePin(InfoLED_Pin);
}

void Init_OLED()
{
    Wire.begin();
    for(uint8_t i = 0; i < 20; i++)
    {
        oled.begin(SSD1306_SWITCHCAPVCC);
    }
    oled.setTextSize(1);
    oled.display();

    oledPlayer.CallBackDrawPicture_u8 = OLED_FastDrawBitmap;
}

float OLED_PlayVideo(char* path)
{
    return oledPlayer.PlayVideo(path);
}
