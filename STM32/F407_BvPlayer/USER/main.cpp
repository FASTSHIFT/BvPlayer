#include "FileGroup.h"

void setup()
{
    Serial.begin(115200);
    pinMode(InfoLED_Pin, OUTPUT);
    
    Init_SD();
    Init_OLED();
    //Init_TFT();
}

float avgfps;

void loop()
{   
    avgfps = OLED_PlayVideo((char*)"BADAPLE.bv");   
}


int main(void)
{
    Delay_Init();
    ADCx_Init(ADC1);
    setup();
    for(;;)loop();
}
