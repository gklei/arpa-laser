int LaserState = LOW;                    // The variable that stores the state of the laser beam.
int sensor = 1023;                         // Change this value to calibrate your harp's sensor
int LASER_DELAY = 5;                     // If you increase this, the laser will be brighter, but the harp will be less fluid
int delaymotor = 500;                     // This variable affects the speed, and fluidity of the harp.

int LaserPin =  7;                       // Tell the arduino that the laser is on pin 7

int motorPin1 = 8;                      //Use these names for the pin numbers.
int motorPin2 = 9;
int motorPin3 = 10;
int motorPin4 = 11;

int motorSpeed = 2400;
const int DEFAULT_STEP_COUNT = 1;
const int STEPPER_COUNT = 8;
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

int note9 = 60;
int note8 = 60;
int note7 = 59;
int note6 = 57;
int note5 = 55;
int note4 = 53;
int note3 = 52;
int note2 = 50;
int note1 = 48;

bool DEBUG_MODE = true;

enum MotorDirection {
  Clockwise,
  Counterclockwise
};

int a, b, c, d, e, f, g, h, i = 0;       // Iniating the note status markers.

// ----------------------------------------------------------------------------
// Setup Methods
// ----------------------------------------------------------------------------
void _setupMotorPins()
{
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void _setupLaserPin()
{
  pinMode(LaserPin, OUTPUT);
}

void _setupStatusLED()
{
  pinMode(13, OUTPUT);
}

void _connectToMIDI()
{
  Serial.begin(31250);
}

void _connectToConsoleForDebugging()
{
  Serial.begin(9600);
}

// ----------------------------------------------------------------------------
// MIDI Utility Methods
// ----------------------------------------------------------------------------
void turnLaserON(int laserDelay = LASER_DELAY)
{
  digitalWrite(LaserPin, HIGH);
  delay(laserDelay);
}

void turnLaserOFF()
{
  digitalWrite(LaserPin, LOW);
}

// ----------------------------------------------------------------------------
// MIDI Utility Methods
// ----------------------------------------------------------------------------
void noteOn(int cmd, int pitch, int velocity)
{
  if (!DEBUG_MODE) {
    Serial.write(cmd);
    Serial.write(pitch);
    Serial.write(velocity); 
  }
}

// ----------------------------------------------------------------------------
// Motor Utility Methods
// ----------------------------------------------------------------------------
void moveMotorCounterclockwise(int steps = DEFAULT_STEP_COUNT)
{
  for (int s = 0; s < steps; ++s) {
    for (int i = 0; i < STEPPER_COUNT; ++i) {
      setMotorPinsWithLookupKey(i);
      delayMicroseconds(motorSpeed);
    } 
  }
}

void moveMotorClockwise(int steps = DEFAULT_STEP_COUNT)
{
  for (int s = 0; s < steps; ++s) {
    for (int i = STEPPER_COUNT; i > 0; --i) {
      setMotorPinsWithLookupKey(i);
      delayMicroseconds(motorSpeed);
    } 
  }
}

void moveMotor(MotorDirection md)
{
  switch (md) {
    case Clockwise: 
      moveMotorClockwise();
      break;
    case Counterclockwise: 
      moveMotorCounterclockwise();
      break;
  }
}

void setMotorPinsWithLookupKey(int key)
{
  digitalWrite(motorPin1, bitRead(lookup[key], 0));
  digitalWrite(motorPin2, bitRead(lookup[key], 1));
  digitalWrite(motorPin3, bitRead(lookup[key], 2));
  digitalWrite(motorPin4, bitRead(lookup[key], 3));
}

// ----------------------------------------------------------------------------
// Misc. Methods
// ----------------------------------------------------------------------------
void printSensorValueToConsoleIfInDebug()
{
  if (DEBUG_MODE) {
    Serial.println(analogRead(A0)); 
  }
}

void _turnStatusLED_ON()
{
  digitalWrite(13, HIGH);
}

void _turnStatusLED_OFF()
{
  digitalWrite(13, LOW);
}

// ----------------------------------------------------------------------------
// Overridden Arduino Methods
// ----------------------------------------------------------------------------
void setup()
{
  _setupMotorPins();
  _setupLaserPin();
  _setupStatusLED();

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

  turnLaserON();
   
  if ((analogRead(0) > sensor ) && (a == 0)) {
    noteOn(0x90, note1, 0x7F);
    a++;
  }
  else if (analogRead(0) < sensor ) {
    noteOn(0x90, note1, 0x00);
    a = 0;
  }

  turnLaserOFF();
  moveMotor(Clockwise);
  delay(delaymotor);

  turnLaserON();
  
  if ((analogRead(0) > sensor ) && (b == 0)) {
    noteOn(0x90, note2, 0x7F);
    b++;
  }
  else if ((analogRead(0) < sensor)) {
    noteOn(0x90, note2, 0x00);
    b = 0;
  }
  
  turnLaserOFF();
  moveMotor(Clockwise);
  delay(delaymotor);

  turnLaserON();

  if ((analogRead(0) > sensor ) && (c == 0)) {
    noteOn(0x90, note3, 0x7F);
    c++;
  }
  else if (analogRead(0) < sensor) {
    noteOn(0x90, note3, 0x00);
    c = 0;
  }

  turnLaserOFF();
  moveMotor(Clockwise);
  delay(delaymotor);

  turnLaserON();

  if ((analogRead(0) > sensor ) && (d == 0)) {
    noteOn(0x90, note4, 0x7F);
    d++;
  }
  else if (analogRead(0) < sensor) {
    noteOn(0x90, note4, 0x00);
    d = 0;
  }

  turnLaserOFF();
  moveMotor(Clockwise);
  delay(delaymotor);

  turnLaserON();

  if ((analogRead(0) > sensor ) && (e == 0)) {
    noteOn(0x90, note5, 0x7F);
    e++;
  }
  else if (analogRead(0) < sensor) {
    noteOn(0x90, note5, 0x00);
    e = 0;
  }

  turnLaserOFF();
  moveMotor(Clockwise);
  delay(delaymotor);

  turnLaserON();

  if ((analogRead(0) > sensor ) && (f == 0)) {
    noteOn(0x90, note6, 0x7F);
    f++;
  }
  else if (analogRead(0) < sensor) {
    noteOn(0x90, note6, 0x00);
    f = 0;
  }

  turnLaserOFF();
  moveMotor(Clockwise);
  delay(delaymotor);

  turnLaserON();

  if ((analogRead(0) > sensor) && (g == 0)) {
    noteOn(0x90, note7, 0x7F);
    g++;
  }
  else if(analogRead(0) < sensor ) {
    noteOn(0x90, note7, 0x00);
    g = 0;
  }

  turnLaserOFF();
  moveMotor(Clockwise);
  delay(delaymotor);

  turnLaserON();

  if( (analogRead(0) > sensor ) && (h == 0) ) {
    noteOn(0x90, note8, 0x7F);
    h++;
  }
  else if (analogRead(0) < sensor) {
    noteOn(0x90, note8, 0x00);
    h = 0;
  }

  turnLaserOFF();
  moveMotor(Clockwise);  
  delay(delaymotor);

  turnLaserON();

  if ((analogRead(0) > sensor ) && (i == 0)) {
    noteOn(0x90, note9, 0x7F);
    i++;
  }
  else if(analogRead(0) < sensor ) {
    noteOn(0x90, note9, 0x00);
    i = 0;
  }

  turnLaserOFF();
  moveMotor(Counterclockwise);
  delay(delaymotor);

  turnLaserON();

  if ((analogRead(0) > sensor ) && (h == 0)) {
    noteOn(0x90, note8, 0x7F);
    h++;
  }
  else if (analogRead(0) < sensor) {
    noteOn(0x90, note8, 0x00);
    h = 0;
  }

  turnLaserOFF();
  moveMotor(Counterclockwise);  
  delay(delaymotor);

  turnLaserON();

  if ((analogRead(0) > sensor ) && (g == 0)) {
    noteOn(0x90, note7, 0x7F);
    g++;
  }
  else if (analogRead(0) < sensor) {
    noteOn(0x90, note7, 0x00);
    g = 0;
  }

  turnLaserOFF();
  moveMotor(Counterclockwise);  
  delay(delaymotor);

  turnLaserON();

  if ((analogRead(0) > sensor ) && (f == 0)) {
    noteOn(0x90, note6, 0x7F);
    f++;
  }
  else if(analogRead(0) < sensor ) {
    noteOn(0x90, note6, 0x00);
    f = 0;
  }

  turnLaserOFF();
  moveMotor(Counterclockwise);  
  delay(delaymotor);

  turnLaserON();

  if ((analogRead(0) > sensor ) && (e == 0)) {
    noteOn(0x90, note5, 0x7F);
    e++;
  }
  else if (analogRead(0) < sensor) {
    noteOn(0x90, note5, 0x00);
    e = 0;
  }

  turnLaserOFF();
  moveMotor(Counterclockwise);
  delay(delaymotor);

  turnLaserON();

  if ((analogRead(0) > sensor ) && (d == 0)) {
    noteOn(0x90, note4, 0x7F);
    d++;
  }
  else if (analogRead(0) < sensor) {
    noteOn(0x90, note4, 0x00);
    d = 0;
  }

  turnLaserOFF();
  moveMotor(Counterclockwise);
  delay(delaymotor);

  turnLaserON();

  if ( (analogRead(0) > sensor ) && (c == 0)) {
    noteOn(0x90, note3, 0x7F);
    c++;
  }
  else if(analogRead(0) < sensor) {
    noteOn(0x90, note3, 0x00);
    c = 0;
  }

  turnLaserOFF();
  moveMotor(Counterclockwise);
  delay(delaymotor);

  turnLaserON();

  if ((analogRead(0) > sensor ) && (b == 0) ) {
    noteOn(0x90, note2, 0x7F);
    b++;
  }
  else if (analogRead(0) < sensor) {
    noteOn(0x90, note2, 0x00);
    b = 0;
  }

  turnLaserOFF();
  moveMotor(Counterclockwise);
  delay(delaymotor);
}
