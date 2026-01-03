#include <TMCStepper.h>     // TMCstepper - https://github.com/teemuatlut/TMCStepper
#include <SoftwareSerial.h> // Software serial for the UART to TMC2209 - https://www.arduino.cc/en/Reference/softwareSerial
#include <Streaming.h>

#define MAX_SPEED 40 // In timer value
#define MIN_SPEED 1000

#define SW_TX 10            // SoftwareSerial receive pin - BROWN
#define SW_RX 11            // SoftwareSerial transmit pin - YELLOW
#define DRIVER_ADDRESS 0b00 // TMC2209 Driver address according to MS1 and MS2
#define R_SENSE 0.11f       // SilentStepStick series use 0.11 ...and so does my fysetc TMC2209 (?)
#define STALL_VALUE 100     // stall value

SoftwareSerial SoftSerial(SW_RX, SW_TX); // Be sure to connect RX to TX and TX to RX between both devices

TMC2209Stepper TMCdriver(&SoftSerial, R_SENSE, DRIVER_ADDRESS); // Create TMC driver

int accel;
long maxSpeed;
// bool dir = false;

void setup()
{

  Serial.begin(11520);          // initialize hardware serial for debugging
  SoftSerial.begin(11520);      // initialize software serial for UART motor control
  TMCdriver.beginSerial(11520); // Initialize UART

  TMCdriver.begin();
  TMCdriver.toff(4);
  TMCdriver.blank_time(24);
  TMCdriver.rms_current(800); // mA
  TMCdriver.en_spreadCycle(true);
  TMCdriver.microsteps(2);
  TMCdriver.TCOOLTHRS(0xFFFFF); // 20bit max
  TMCdriver.semin(5);
  TMCdriver.semax(2);
  TMCdriver.blank_time(24);
  TMCdriver.sedn(0b01);
  TMCdriver.SGTHRS(STALL_VALUE);

  accel = 200;     // Speed increase/decrease amount
  maxSpeed = 3200; // Maximum speed to be reached

  for (long i = 0; i <= maxSpeed; i = i + accel)
  {                       // Speed up to maxSpeed
    TMCdriver.VACTUAL(i); // Set motor speed
    delay(50);
  }
}

void loop()
{
  static uint32_t last_time = 0;
  uint32_t ms = millis();

  while (Serial.available() > 0)
  {
    int8_t read_byte = Serial.read();
    if (read_byte == '0')
    {
      TIMSK1 &= ~(1 << OCIE1A);
    }
    else if (read_byte == '1')
    {
      TIMSK1 |= (1 << OCIE1A);
    }
    else if (read_byte == '+')
    {
      if (OCR1A > MAX_SPEED)
        OCR1A -= 20;
    }
    else if (read_byte == '-')
    {
      if (OCR1A < MIN_SPEED)
        OCR1A += 20;
    }
  }

  if ((ms - last_time) > 100)
  { // run every 0.1s
    last_time = ms;

    Serial.print("0 ");
    Serial.print(TMCdriver.SG_RESULT(), DEC);
    Serial.print(" ");
    Serial.println(TMCdriver.cs2rms(TMCdriver.cs_actual()), DEC);
  }
}