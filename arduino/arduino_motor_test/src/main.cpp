#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TMCStepper.h>

#define STEP_PIN 8
#define R_SENSE 0.11f
#define DRIVER_ADDRESS 0b00
#define MICROSTEPS 2

SoftwareSerial SoftSerial(10, 11, false); // receive, transmit
TMC2209Stepper driver(&SoftSerial, R_SENSE, DRIVER_ADDRESS);

void setup()
{
  SoftSerial.begin(115200); // INITIALIZE UART TMC2209
  Serial.begin(115200);
  delay(500);
  Serial.println(F("Serial Initialized"));

  driver.begin(); // Initialize driver
  driver.toff(5); // Enables driver in software

  driver.rms_current(300); // Set motor RMS current
  driver.microsteps(MICROSTEPS);

  driver.pwm_autoscale(true);   // Needed for stealthChop
  driver.en_spreadCycle(false); // false = StealthChop / true = SpreadCycle
  driver.shaft(false);

  Serial.print(F("microsteps: "));
  Serial.println(driver.microsteps());
  Serial.print(F("current: "));
  Serial.println(driver.rms_current());
}

void loop()
{
  digitalWrite(STEP_PIN, HIGH);
  delay(3.6);
  digitalWrite(STEP_PIN, LOW);
  delay(3.6);
}