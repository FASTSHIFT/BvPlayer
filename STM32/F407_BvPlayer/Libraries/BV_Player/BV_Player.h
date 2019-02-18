#ifndef __BV_PLAYER_H
#define __BV_PLAYER_H

#include "BvType.h"
#include "SD.h"

typedef void(*FastDrawPicture_u16_CallbackFunction_t)(uint16_t*,BvHeader_TypeDef*);
typedef void(*FastDrawPicture_u8_CallbackFunction_t)(uint8_t*,BvHeader_TypeDef*);

class BV_Player {
public:
    FastDrawPicture_u16_CallbackFunction_t CallBackDrawPicture_u16;
    FastDrawPicture_u8_CallbackFunction_t  CallBackDrawPicture_u8;

    BV_Player(uint32_t bufferSizeMax);
    float PlayVideo(String path);
    float PlayVideo(const char *path);
private:
    File BvFile;
    BvHeader_TypeDef Head;
    uint32_t BufferSizeMax;
    
    uint32_t PlayVideo_RGB565();
    uint32_t PlayVideo_RGB232();
    uint32_t PlayVideo_BIN();
};

#endif
