#ifndef __BV_PLAYER_H
#define __BV_PLAYER_H

#include "BvType.h"
#include "SD.h"

class BV_Player {
  public:
    BV_Player();
    float PlayVideo(String path);
    float PlayVideo(const char *path);
    uint8_t *Buffer; 
  private:
    File BvFile;
    BvHeader_TypeDef Head;
    uint32_t PlayVideo_OLED();
};

#endif
