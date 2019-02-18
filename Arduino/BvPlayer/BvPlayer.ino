#include "FileGroup.h"

void setup()
{
  //Serial.begin(115200);
  pinMode(OLED_CS, OUTPUT);
  pinMode(SD_CS_Pin, OUTPUT);
  pinMode(NRF_CSN_Pin, OUTPUT);
  digitalWrite(OLED_CS, HIGH);
  digitalWrite(SD_CS_Pin, HIGH);
  digitalWrite(NRF_CSN_Pin, HIGH);

  Init_OLED();
  Init_SD();
}

void loop()
{
  float fps = OLED_PlayVideo("NewVID.bv");
  oled.setTextSize(2);
  oled.setCursor(0, 30);
  oled << "FPS:" << fps;
  oled.display();
  delay(5000);
  oled.setTextSize(1);
  oled.clearDisplay();
}

