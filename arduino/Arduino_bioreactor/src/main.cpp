#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <QuickPID.h>

//SPI pins
#define TFT_DC 2
#define TFT_CS 15
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// Thermistor pin
#define THERMISTOR_PIN A0

// Heater pin
#define HEATER_PIN 3

void setup() {
  // put your setup code here, to run once:

  // SPI pin readout
  Serial.begin(9600);
  Serial.print("MOSI: ");
  Serial.println(MOSI);
  Serial.print("MISO: ");
  Serial.println(MISO);
  Serial.print("SCK: ");
  Serial.println(SCK);
  Serial.print("SS: ");
  Serial.println(SS);  
 

// Basic graphics display test
    tft.begin();
  Serial.begin(9600);
  Serial.println("1234567890");
  tft.setCursor(20, 120);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(3);
  tft.println("Hello ESP32");

  tft.setCursor(24, 160);
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);
  tft.println("I can do SPI :-)");
  tft.invertDisplay(true);



}

void loop() 
 { delay(10); }
