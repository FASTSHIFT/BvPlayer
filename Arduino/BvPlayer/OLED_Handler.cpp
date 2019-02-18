#include "FileGroup.h"

#include "BV_Player.h"

Adafruit_SSD1306 oled(OLED_DC, OLED_RST, OLED_CS);
//Adafruit_SSD1306 oled(-1);

BV_Player oledPlayer;

void Init_OLED()
{
  oled.begin(SSD1306_SWITCHCAPVCC);

  oled.display();
  delay(2000);
  oled.clearDisplay();

  oled.setTextSize(1);
  oled.setTextColor(WHITE, BLACK);
  oled.setCursor(0, 0);

  oledPlayer.Buffer = oled.getBuffer();
}

float OLED_PlayVideo(char* path)
{
  return oledPlayer.PlayVideo(path);
}
