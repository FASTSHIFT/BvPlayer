#include "FileGroup.h"
#include <SD.h>

#define ChipSelect_Pin SD_CS_Pin

void Init_SD()
{
  //Serial.print(F("Initializing SD card..."));

  if (!SD.begin(SD_CS_Pin)) {
    //Serial.println(F("initialization failed!"));
    while (1);
  }
  //Serial.println(F("initialization done."));

  //rootFile = SD.open("/");
  //PrintCardInfo();
}
