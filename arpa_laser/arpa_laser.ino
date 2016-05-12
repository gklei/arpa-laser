#include <Stepper.h>

bool DEBUG_MODE = true;

/*----- Stepper-related Constants -----*/
#define STEPS_FOR_FULL_ROTATION 48
#define STEP_DISTANCE 1
#define STEPPER_SPEED 200

/*----- Laser-related Constants -----*/
#define LASER_DELAY 5
#define LASER_PIN 7

/*----- Note-related Constants -----*/
#define TOTAL_NOTES 8
#define MIDI_PORT 31250

/*----- Declare objects -----*/
Stepper stepper(STEPS_FOR_FULL_ROTATION, 8, 9, 10, 11);

/*---- Setup Methods ----*/
void _setupLaserPin()
{
  pinMode(LASER_PIN, OUTPUT);
}

void _connectToMIDI()
{
  Serial.begin(MIDI_PORT);
}

void _connectToConsoleForDebugging()
{
  Serial.begin(9600);
}

/*---- Utility Methods ----*/
void turnLaserON(int laserDelay = LASER_DELAY)
{
  digitalWrite(LASER_PIN, HIGH);
  delay(laserDelay);
}

void turnLaserOFF()
{
  digitalWrite(LASER_PIN, LOW);
}

void printSensorValueToConsoleIfInDebug()
{
  if (DEBUG_MODE) {
    Serial.println(analogRead(A0)); 
  }
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

  for (int noteIndex = 0; noteIndex < TOTAL_NOTES; ++noteIndex) 
  {
    turnLaserON();
    // read photoresistor value and play or turn note off
    turnLaserOFF();
    
    stepper.step(1);
    delay(1); 
  }
   
  for (int noteIndex = TOTAL_NOTES; noteIndex > 0 ; --noteIndex) 
  {
    turnLaserON();
    // read photoresistor value and play or turn note off
    turnLaserOFF();
    
    stepper.step(-1);
    delay(1);
  }
}
