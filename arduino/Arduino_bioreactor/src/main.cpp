#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define ONE_WIRE_BUS 4
#define GATE_PIN 2
#define TEMP_WANTED 43.0
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int initial_time = 0;
int initial_temp = 0;
bool has_reached_temp = false;
void setup()
{
  Serial.begin(9600);
  sensors.begin();
  delay(500);

  // GATE SETUP
  pinMode(GATE_PIN, OUTPUT);

  // reset time
  initial_time = millis();
  // reset temp
  initial_temp = sensors.getTempCByIndex(0);
}

void loop()
{
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  Serial.print(temp);
  Serial.print(" C  |  ");
  delay(500);

  if (temp - (-127.0) < 0.0001)
  {
    Serial.println("No sensor found");
    delay(1000);
    return;
  }

  if (temp < TEMP_WANTED)
  {
    // INVERTED PINS
    digitalWrite(GATE_PIN, LOW);
    Serial.print("Gate opened  |  ");
  }
  else
  {
    // INVERTED PINS
    digitalWrite(GATE_PIN, HIGH);
    Serial.print("Gate closed  |  ");

    if (!has_reached_temp)
    {
      has_reached_temp = true;
      Serial.println("");
      Serial.print("Time to reach temp: ");
      int time = millis() - initial_time;
      Serial.print(time / 1000);
      Serial.print(" s || ");
      Serial.print("Temp delta: ");
      Serial.print(temp - initial_temp);
      Serial.println(" C");
    }
  }

  // time from start
  int time = millis() - initial_time;
  Serial.print(time / 1000);
  Serial.println(" s");
}