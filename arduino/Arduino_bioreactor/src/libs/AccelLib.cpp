#include <Arduino.h>

class AccelLib
{
private:
  // variables
  int _maxSpeed;
  int _acceleration;
  int _stepsPerRevolution;
  int _currentSpeed; // RPM
  int _deltaTime;    // time between updates
  int _lastUpdateMicros;
  int _prevStepTimeMicros;
  int _minPulseWidth;

  // set run variables
  int _direction;
  int _speed;

  // pins
  int _stepPin;
  int _dirPin;

protected:
  // methods
  void step();

public:
  AccelLib(int stepPin, int dirPin, int stepsPerRevolution);
  ~AccelLib();

  // methods
  void setPins(int stepPin, int dirPin);
  void setMaxSpeed(int maxSpeed);
  void setAcceleration(int acceleration);
  void setMinPulseWidth(int minPulseWidth);
  void constantRun(int direction, int RPM);
  void update();
  void move();

  // getters
  int getMaxSpeed();
  int getAcceleration();
  int getMinPulseWidth();
  int getCurrentPosition();
};

// constructor
AccelLib::AccelLib(int stepPin, int dirPin, int stepsPerRevolution)
{
  _stepPin = stepPin;
  _dirPin = dirPin;
  _stepsPerRevolution = stepsPerRevolution;

  pinMode(_stepPin, OUTPUT);
  pinMode(_dirPin, OUTPUT);

  // default values
  _maxSpeed = 100;    // max speed is 100 rpm
  _acceleration = 10; // acceleration is 10 rpm/s
  _currentSpeed = 0;
  _prevStepTimeMicros = micros();
}

// destructor
AccelLib::~AccelLib()
{
}

// methods
void AccelLib::setPins(int stepPin, int dirPin)
{
  _stepPin = stepPin;
  _dirPin = dirPin;

  pinMode(_stepPin, OUTPUT);
  pinMode(_dirPin, OUTPUT);
}

void AccelLib::setMaxSpeed(int maxSpeed)
{
  _maxSpeed = maxSpeed;
}

void AccelLib::setAcceleration(int acceleration)
{
  _acceleration = acceleration;
}

void AccelLib::setMinPulseWidth(int minPulseWidth)
{
  _minPulseWidth = minPulseWidth;
}

void AccelLib::constantRun(int direction, int RPM)
{
  _speed = RPM;
  _direction = direction;
}

void AccelLib::update()
{
  // calculate the time between updates
  _deltaTime = micros() - _lastUpdateMicros;
  _lastUpdateMicros = micros();
}
// make one motor step
void AccelLib::step()
{
  // if the time since the last step is greater than the minimum pulse width
  if (micros() - _prevStepTimeMicros >= _minPulseWidth)
  {
    digitalWrite(_stepPin, HIGH);
    // TRY TO REMOVE THIS DELAY
    delayMicroseconds(_minPulseWidth);
    digitalWrite(_stepPin, LOW);
    _prevStepTimeMicros = micros();
  }
}