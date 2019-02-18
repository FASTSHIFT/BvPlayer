#include "BV_Player.h"

#define DEBUG_SERIAL Serial

#ifdef DEBUG_SERIAL
#include "HardwareSerial.h"
#define DEBUG(format, ...) DEBUG_SERIAL.printf(format, ##__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif

BV_Player::BV_Player(uint32_t bufferSizeMax)
{
    BufferSizeMax = bufferSizeMax;
}
/* Call back function example:
void TFT_FastDrawRGBBitmap(uint16_t *bitmap, BvHeader_TypeDef* head)
{
    uint32_t size = head->Width * head->Height;
    tft.setAddrWindow(0, 0, head->Width - 1, head->Height - 1);
    for(uint32_t i = 0; i < size; i++)
        tft.pushColor(bitmap[i]);
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
            tft.pushColor((b & 0x80) ? ST7735_WHITE : ST7735_BLACK);
        }
    }
}
*/
uint32_t BV_Player::PlayVideo_RGB565()
{
    uint32_t picsize = Head.Width * Head.Height;
    if(picsize > BufferSizeMax)
        return 0;

    uint16_t *Picture = new uint16_t[picsize];

    uint32_t start = millis();
    for(uint32_t i = 0; i <= Head.FrameNum; i++)
    {
        BvFile.read(Picture, picsize * sizeof(uint16_t));
        if(CallBackDrawPicture_u16)
            CallBackDrawPicture_u16(Picture, &Head);
    }
    delete[] Picture;
    return (millis() - start);
}

uint32_t BV_Player::PlayVideo_BIN()
{
    uint32_t picsize = (Head.Width * Head.Height / 8);
    if(picsize > BufferSizeMax)
        return 0;

    uint8_t *Picture = new uint8_t[picsize];

    uint32_t start = millis();
    for(uint32_t i = 0; i <= Head.FrameNum; i++)
    {
        BvFile.read(Picture, picsize);
        if(CallBackDrawPicture_u8)
            CallBackDrawPicture_u8(Picture, &Head);
    }
    delete[] Picture;
    return (millis() - start);
}

//RGB232解码:
//1.读出新一帧数据(RGB232),RGB移位转RGB565(0RRGGGBB 
//                              -> RR000GGG000BB000)
//2.将后一帧数据(RGB565),RGB分别向后移位(RRRRRGGGGGGBBBBB -> 00rrr000ggg00bbb)
//3.两帧叠加(RGB565),(RR000GGG000BB000 | 00rrr000ggg00bbb = RRrrrGGGgggBBbbb)
//4.显示至屏幕
//5.保存这一帧作为刚才的后一帧
#define GET_232RED(r)   ((r&B01100000)<<9)
#define GET_232GREEN(g) ((g&B00011000)<<6)
#define GET_232BLUE(b)  ((b&B00000011)<<3)

#define GET_565RED(rgb)   ((rgb&0xE000)>>2)
#define GET_565GREEN(rgb) ((rgb&0x0700)>>3)
#define GET_565BLUE(rgb)  ((rgb&0x001C)>>2)


uint32_t BV_Player::PlayVideo_RGB232()
{
    uint32_t picsize = Head.Width * Head.Height;
    if(picsize > BufferSizeMax)
        return 0;

    uint16_t *rgb565Pic = new uint16_t[picsize];
    uint8_t *rgb232Pic = new uint8_t[picsize];

    uint32_t start = millis();
    for(uint32_t i = 0; i <= Head.FrameNum; i++)
    {
        BvFile.read(rgb232Pic, picsize);
        
        for(uint32_t j = 0; j < picsize; j++)
        {
            uint16_t newRGB565 = GET_232RED(rgb232Pic[j]) | GET_232GREEN(rgb232Pic[j]) | GET_232BLUE(rgb232Pic[j]);
            //uint16_t oldRGB565 = GET_565RED(rgb565Pic[j]) | GET_565GREEN(rgb565Pic[j]) | GET_565BLUE(rgb565Pic[j]);
            rgb565Pic[j] = newRGB565;// | oldRGB565;
        }      
        if(CallBackDrawPicture_u16)
            CallBackDrawPicture_u16(rgb565Pic, &Head);
    }
    delete[] rgb565Pic;
    delete[] rgb232Pic;
    return (millis() - start);
}

float BV_Player::PlayVideo(String path)
{
    char* cpath = new char[path.length() + 1];
    path.toCharArray(cpath, path.length() + 1);
    float fps = PlayVideo(cpath);
    delete[] cpath;
    return fps;
}

float BV_Player::PlayVideo(const char *path)
{
    float fps = 0.0;
    BvFile = SD.open(String(path));
    if(BvFile)
    {
        DEBUG("\r\n%s success opening", path);
        if(BvFile.available())
        {
            BvFile.read(&Head, sizeof(BvHeader_TypeDef));
            if(Head.Type == BvType_BIN)
            {
                uint32_t usetime = PlayVideo_BIN();
                if(usetime)
                {
                    fps = Head.FrameNum * 1000.0 / usetime;
                    DEBUG("\r\n%s is play finished!", path);
                    DEBUG("\r\nuse %0.2fs(fps:%0.3f)", usetime / 1000.0, fps);
                }
                else 
                    DEBUG("\r\nMemory too few");
            }
            else if(Head.Type == BvType_RGB565)
            {
                uint32_t usetime = PlayVideo_RGB565();
                if(usetime)
                {
                    fps = Head.FrameNum * 1000.0 / usetime;
                    DEBUG("\r\n%s is play finished!", path);
                    DEBUG("\r\nuse %0.2fs(fps:%0.3f)", usetime / 1000.0, fps);
                }
                else 
                    DEBUG("\r\nMemory too few");
            }
            else if(Head.Type == BvType_RGB232)
            {
                uint32_t usetime = PlayVideo_RGB232();
                if(usetime)
                {
                    fps = Head.FrameNum * 1000.0 / usetime;
                    DEBUG("\r\n%s is play finished!", path);
                    DEBUG("\r\nuse %0.2fs(fps:%0.3f)", usetime / 1000.0, fps);
                }
                else 
                    DEBUG("\r\nMemory too few");
            }
            else if(Head.Type == BvType_RGB888)
            {
                DEBUG("\r\nRGB888 is unsupport");
            }
            else
                DEBUG("\r\n%s is unsupport type!", path);
        }
        BvFile.close();
    }
    else
        DEBUG("\r\n%s error opening", path);

    return fps;
}
