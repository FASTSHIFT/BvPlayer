 #include "BV_Player.h"
#include "FileGroup.h"

//#define DEBUG_OUTPUT Serial

#ifdef DEBUG_SERIAL
#include <Arduino.h>
#define DEBUG(xxx) DEBUG_OUTPUT.print(xxx)
#else
#define DEBUG(xxx)
#endif

BV_Player::BV_Player()
{
}

uint32_t BV_Player::PlayVideo_OLED()
{
  uint32_t start = millis();
  for (uint32_t i = 0; i <= Head.FrameNum; i++)
  {
    BvFile.read(Buffer, 1024);
    oled.display();
    delay(10);
  }
  return (millis() - start);
}

float BV_Player::PlayVideo(String path)
{
  char cpath[path.length() + 1];
  path.toCharArray(cpath, path.length() + 1);
  float fps = PlayVideo(cpath);
  return fps;
}

float BV_Player::PlayVideo(const char *path)
{
  float fps = 0.0;
  BvFile = SD.open(String(path));
  if (BvFile)
  {
    DEBUG(path);
    DEBUG(F("\r\nsuccess opening"));
    if (BvFile.available())
    {
      BvFile.read(&Head, sizeof(BvHeader_TypeDef));
      if (Head.Type == BvType_OLED)
      {
        uint32_t usetime = PlayVideo_OLED();
        if (usetime)
        {
          fps = Head.FrameNum * 1000.0 / usetime;
          DEBUG(F("\r\nplay finished!"));
          //DEBUG("\r\nuse %0.2fs(fps:%0.3f)", usetime / 1000.0, fps);
        }
      }
      else
        DEBUG(F("\r\nunsupport type!"));
    }
    BvFile.close();
  }
  else
    DEBUG(F("\r\nerror opening"));

  return fps;
}
