#include <Stepper.h>

bool DEBUG_MODE = true;

/*----- Stepper-related Constants -----*/
#define STEPS_FOR_FULL_ROTATION 48
#define STEP_DISTANCE 1
#define STEPPER_SPEED 3000

/*----- Laser-related Constants -----*/
#define LASER_DELAY 9
// If this is too small, the stepper will freak out.
#define LASER_SHORTSTOP 4
#define LASER_PIN 7

/*----- Note-related Constants -----*/
#define TOTAL_NOTES 8
#define MIDI_BAUD 31250

/*----- Declare objects -----*/
Stepper stepper(STEPS_FOR_FULL_ROTATION, 8, 9, 10, 11);

/*---- Setup Methods ----*/
void _setupLaserPin()
{
  pinMode(LASER_PIN, OUTPUT);
}

void _connectToMIDI()
{
  Serial.begin(MIDI_BAUD);
}

void _connectToConsoleForDebugging()
{
  Serial.begin(9600);
}

/*---- Utility Methods ----*/
void turnLaserON()
{
  delay(LASER_SHORTSTOP);
  digitalWrite(LASER_PIN, HIGH);
  delay(LASER_DELAY);
}

void turnLaserOFF()
{
  digitalWrite(LASER_PIN, LOW);
  delay(LASER_DELAY);
}

void printSensorValueToConsoleIfInDebug()
{
  if (DEBUG_MODE) {
    Serial.println(analogRead(A0));
  }
}

void waitASecond() {
  stepper.step(0);
  delay(10);
  stepper.step(0);
}

/*---- Overridden Methods ----*/
void setup()
{
  _setupLaserPin();
  stepper.setSpeed(STEPPER_SPEED);

  if (DEBUG_MODE) {
    _connectToConsoleForDebugging();
  }
  else {
    _connectToMIDI();
  }
}

void loop()
{
  printSensorValueToConsoleIfInDebug();

  // Reduce blur on the beginning note.
  delay(LASER_SHORTSTOP);

  for (int noteIndex = 0; noteIndex < TOTAL_NOTES; ++noteIndex)
  {
    turnLaserON();
    // read photoresistor value and play or turn note off
    turnLaserOFF();

    stepper.step(STEP_DISTANCE);
    delay(LASER_DELAY);
  }

  // Don't draw lasers on the downstroke, to reduce blur.
  for (int noteIndex = TOTAL_NOTES; noteIndex > 0; --noteIndex)
  {
    stepper.step(-STEP_DISTANCE);
    delay(LASER_SHORTSTOP);
  }
}
