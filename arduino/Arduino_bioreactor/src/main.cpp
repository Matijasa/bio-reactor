#include <Arduino.h>
#include <TMCStepper.h>

#define EN_PIN 38  // Enable
#define CS_PIN 42  // Chip select
#define DIR_PIN 2  // Direction
#define STEP_PIN 4 // Step

#define SERIAL_PORT Serial1 // TMC2208/TMC2224 HardwareSerial port

#define R_SENSE 0.11f // Match to your driver

TMC2208Stepper driver(&SERIAL_PORT, R_SENSE); // Hardware Serial

const int steps_per_revolution = 200;
const int desired_rpm = 300;

void setup()
{
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW); // Enable driver in hardware

  SERIAL_PORT.begin(115200);

  driver.begin();
  driver.toff(5);
  driver.rms_current(600);
  driver.microsteps(16);
  driver.en_spreadCycle(true);
  driver.pwm_autoscale(true);
}

void loop()
{
  // Calculate delay based on desired RPM
  unsigned long delay_microseconds = 60000000UL / (steps_per_revolution * desired_rpm);

  // Run the motor continuously
  while (true)
  {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delay_microseconds);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(delay_microseconds);
  }
}