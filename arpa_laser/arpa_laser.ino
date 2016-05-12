#include <Stepper.h>

// FOR DEBUGGING!
bool DEBUG_MODE = true;

/*----- Stepper-related Constants -----*/
#define STEPS 48
#define STEP_DISTANCE 1
#define STEPPER_SPEED 200

/*----- Laser-related Constants -----*/
#define LASER_DELAY 5
#define LASER_PIN 7

/*----- Note-related Constants -----*/
#define TOTAL_NOTES 8

/*----- Declare objects -----*/
// The pin connections need to be 4 pins connected
// to Motor Driver In1, In2, In3, In4  and then the pins entered
// here in the sequence 1-3-2-4 for proper sequencing
Stepper _stepper(STEPS, 8, 9, 10, 11);

/*---- Setup Methods ----*/
void _setupLaserPin()
{
  pinMode(LASER_PIN, OUTPUT);
}

void _connectToMIDI()
{
  Serial.begin(31250);
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
  _stepper.setSpeed(STEPPER_SPEED); 
  
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
  
  // Turn Laser on
  // Read Photoresistor Value
  // Do note stuff
  // Turn laser off
  // Step

   for (int noteIndex = 0; noteIndex < TOTAL_NOTES; ++noteIndex) {
      turnLaserON();
      _stepper.step(1);
      turnLaserOFF();
      delay(1); 
   }
   
   for (int noteIndex = TOTAL_NOTES; noteIndex > 0 ; --noteIndex) {
      turnLaserON();
      _stepper.step(-1);
      turnLaserOFF();
      delay(1);
   }
} /* --(end main loop )-- */
