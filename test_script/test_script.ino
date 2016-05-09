int LaserState = LOW;                    // The variable that stores the state of the laser beam.
int sensor = 8;                         // Change this value to calibrate your harp's sensor
int delaylaser = 5;                     // If you increase this, the laser will be brighter, but the harp will be less fluid
int delaymotor = 1;                     // This variable affects the speed, and fluidity of the harp.

int LaserPin =  7;                       // Tell the arduino that the laser is on pin 7

int motorPin1 = 8;                      //Use these names for the pin numbers.
int motorPin2 = 9;
int motorPin3 = 10;
int motorPin4 = 11;

int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
int motorSpeed = 0;

int note9 = 0x61;
int note8 = 0x63;
int note7 = 0x64;
int note6 = 0x66;
int note5 = 0x68;
int note4 = 0x70;
int note3 = 0x71;
int note2 = 0x40;
int note1 = 0x47;

int a, b, c, d, e, f, g, h, i = 0;       // Iniating the note status markers.

void setup()
{
  pinMode(8, OUTPUT);                    // Setup for the motor.
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);


  pinMode(LaserPin, OUTPUT);            // Setup for laser.


  pinMode(13, OUTPUT);                 // Setup for status led.


//  Serial.begin(31250);                 //  Start a serial communication channel for MIDI
  Serial.begin(9600);

  digitalWrite(LaserPin, HIGH);               // Turn on the laser for the 1st beam.
}

void noteOn(int cmd, int pitch, int velocity)     // Function to play the notes
{
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

void anticlockwise()
{
  for(int i = 0; i < 8; i++)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
  for(int i = 0; i < 8; i++)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
  for(int i = 0; i < 8; i++)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void clockwise()
{
  for(int i = 7; i >= 0; i--)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
  for(int i = 7; i >= 0; i--)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
  for(int i = 7; i >= 0; i--)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void setOutput(int out)
{
  digitalWrite(motorPin1, bitRead(lookup[out], 0));
  digitalWrite(motorPin2, bitRead(lookup[out], 1));
  digitalWrite(motorPin3, bitRead(lookup[out], 2));
  digitalWrite(motorPin4, bitRead(lookup[out], 3));
}

bool noteIsOn = false;

void loop() 
{
  delay(100);

  int analogVal = analogRead(A0);
  Serial.println(analogVal);
}
