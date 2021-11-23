#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include "Free_Fonts.h"
#include <MAX6675.h>

#define MAX6675_CS_PIN A0
MAX6675 tcouple(MAX6675_CS_PIN);
TFT_eSPI tft = TFT_eSPI();  
#define BuiltIn_Led PC13
float NewTemp = 0;
float OldTemp = 0;
uint16_t NewSetTemp = 127;
uint16_t OldSetTemp = 0;

void setup() 
{
  Serial.begin(115200);
  pinMode(BuiltIn_Led, OUTPUT);
  tft.init();
  tft.initDMA();
  tft.setRotation(1); 
  tft.setFreeFont(FSSB9);
  tft.setTextColor(TFT_SKYBLUE);
  tft.fillScreen(TFT_BLACK);
  tft.drawRect(0,0,128,128,TFT_WHITE);
  tft.drawRect(1,1,64,50,TFT_GREEN);
  tft.fillRect(2,2,62,48,TFT_BLACK);
  tft.drawRect(64,1,63,50,TFT_GREEN);
  tft.fillRect(65,2,61,48,TFT_BLACK);
  tft.setCursor(7, 15);
  tft.print("Temp");
  tft.setCursor(80, 15);
  tft.print("Set");

  tft.drawRect(1,52,126,75,TFT_RED);
  tft.fillRect(2,53,124,72,TFT_YELLOW);

  delay(1);

}

void loop() 
{
  NewTemp = tcouple.readTempC();
  if(NewTemp != OldTemp)
  {
    delay(100);
    tft.fillRect (5, 20 , 58, 30, TFT_BLACK);
    tft.setCursor(5, 40);
    if(NewTemp < 100) tft.print(" ");
    tft.print(NewTemp, 1); tft.print("C");
    OldTemp = NewTemp;
  }

  if(NewSetTemp != OldSetTemp)
  {
    tft.fillRect (65, 20 , 58, 30, TFT_BLACK);
    tft.setCursor(70, 40);
    if(NewSetTemp < 100) tft.print(" ");
    tft.print(NewSetTemp); tft.print("C");
    OldSetTemp = NewSetTemp;
  }
  digitalWrite(BuiltIn_Led, !digitalRead(BuiltIn_Led));
  delay(1000);
}