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
int motorSpeed = 950;

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


  Serial.begin(31250);                 //  Start a serial communication channel for MIDI
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

void loop() {

  digitalWrite(LaserPin, HIGH);               // Turn on the laser for the 1st beam.
  delay(delaylaser);

  if (true || (analogRead(0) > sensor ) && (a == 0) ) // If the sensor gets a signal, and the not is not playing:

  {
    digitalWrite(13, HIGH);       // Switch on status led.
    noteOn(0x90, note1, 0x7F);    // Play note 1
    a++;                          // Change the status variable to one.
  }


  else if(false && analogRead(0) < sensor )             // If the sensor does not get a signal:

  {
    digitalWrite(13, LOW);         // Switch off the status led.
    noteOn(0x90, note1, 0x00);     // Stop playing note 1.
    a = 0;                         // Change the status variable to zero.
  }


  digitalWrite(LaserPin, LOW);                // Turn off the Laser.

        clockwise();
  delay(delaymotor);                          // Small pause


  digitalWrite(LaserPin, HIGH);              // Turn on the laser for the 2nd beam.
  delay(delaylaser);

  if((analogRead(0) > sensor ) && (b == 0) ) // If the sensor gets a signal, and the not is not playing:

  {
    digitalWrite(13, HIGH);              // Switch on status led.
    noteOn(0x90, note2, 0x7F);           // Play note 2
    b++;                                 // Change the status variable to one.
  }


  else if((analogRead(0) < sensor) )           // If the sensor does not get a signal:

  {
    digitalWrite(13, LOW);          // Switch off the status led.
    noteOn(0x90, note2, 0x00);      // Stop playing note 2.
    b = 0;                          // Change the status variable to zero.
  }

                  // Change the status variable to one.

  digitalWrite(LaserPin, LOW);                    // Turn off the Laser.



  clockwise();
  delay(delaymotor);                          // Small pause


  digitalWrite(LaserPin, HIGH);             // Turn on the laser for the 3rd beam.
  delay(delaylaser);

  if( (analogRead(0) > sensor ) && (c == 0) ) // If the sensor gets a signal, and the not is not playing:

  {
    digitalWrite(13, HIGH);       // Switch on status led.
    noteOn(0x90, note3, 0x7F);    // Play note 3
    c++;                          // Change the status variable to one.
  }


  else if(analogRead(0) < sensor )           // If the sensor does not get a signal:
  {
    digitalWrite(13, LOW);        // Switch off the status led.
    noteOn(0x90, note3, 0x00);    // Stop playing note 2.
    c = 0;                        // Change the status variable to zero.
  }

  digitalWrite(LaserPin, LOW);                 // Turn off the Laser.

  clockwise();
  delay(delaymotor);                            // Small pause

  // Contiue in the same way for the rest of the code.

  digitalWrite(LaserPin, HIGH);               //This is beam 4
  delay(delaylaser);

  if( (analogRead(0) > sensor ) && (d == 0) )
  {
    digitalWrite(13, HIGH);
    noteOn(0x90, note4, 0x7F);
    d++;
  }


  else if(analogRead(0) < sensor )
  {
    digitalWrite(13, LOW);
    noteOn(0x90, note4, 0x00);
    d = 0;
  }

  digitalWrite(LaserPin, LOW);



  clockwise();
  delay(delaymotor);


  digitalWrite(LaserPin, HIGH);                  //This is beam 5
  delay(delaylaser);

  if( (analogRead(0) > sensor ) && (e == 0) )

  {
    digitalWrite(13, HIGH);
    noteOn(0x90, note5, 0x7F);
    e++;
  }


  else if(analogRead(0) < sensor )

  {
    digitalWrite(13, LOW);
    noteOn(0x90, note5, 0x00);
    e = 0;
  }

  digitalWrite(LaserPin, LOW);


  clockwise();
  delay(delaymotor);


  digitalWrite(LaserPin, HIGH);                  //This is beam 6
  delay(delaylaser);

  if( (analogRead(0) > sensor ) && (f == 0) )

  {
    digitalWrite(13, HIGH);
    noteOn(0x90, note6, 0x7F);
    f++;
  }


  else if(analogRead(0) < sensor )

  {
    digitalWrite(13, LOW);
    noteOn(0x90, note6, 0x00);
    f = 0;
  }

  digitalWrite(LaserPin, LOW);

  clockwise();
  delay(delaymotor);


  digitalWrite(LaserPin, HIGH);                  //This is beam 7
  delay(delaylaser);

  if( (analogRead(0) > sensor ) && (g == 0) )

  {
    digitalWrite(13, HIGH);
    noteOn(0x90, note7, 0x7F);
    g++;
  }


  else if(analogRead(0) < sensor )

  {
    digitalWrite(13, LOW);
    noteOn(0x90, note7, 0x00);
    g = 0;
  }

  digitalWrite(LaserPin, LOW);



  clockwise();
  delay(delaymotor);


  digitalWrite(LaserPin, HIGH);                   //This is beam 8
  delay(delaylaser);

  if( (analogRead(0) > sensor ) && (h == 0) )

  {
    digitalWrite(13, HIGH);
    noteOn(0x90, note8, 0x7F);
    h++;
  }


  else if(analogRead(0) < sensor )

  {
    digitalWrite(13, LOW);
    noteOn(0x90, note8, 0x00);
    h = 0;
  }

  digitalWrite(LaserPin, LOW);



  clockwise();
  delay(delaymotor);


  digitalWrite(LaserPin, HIGH);    //This is beam 9
  delay(delaylaser);

  if( (analogRead(0) > sensor ) && (i == 0) )
  {
    digitalWrite(13, HIGH);
    noteOn(0x90, note9, 0x7F);
    i++;
  }

  else if(analogRead(0) < sensor )

  {
    digitalWrite(13, LOW);
    noteOn(0x90, note9, 0x00);
    i = 0;
  }



  digitalWrite(LaserPin, LOW);


  anticlockwise();
  delay(delaymotor);

  digitalWrite(LaserPin, HIGH);       //This is beam 8
  delay(delaylaser);

  if( (analogRead(0) > sensor ) && (h == 0) )

  {
    digitalWrite(13, HIGH);
    noteOn(0x90, note8, 0x7F);
    h++;
  }


  else if(analogRead(0) < sensor )

  {
    digitalWrite(13, LOW);
    noteOn(0x90, note8, 0x00);
    h = 0;
  }

  digitalWrite(LaserPin, LOW);



  anticlockwise();
  delay(delaymotor);


  digitalWrite(LaserPin, HIGH);    //This is beam 7
  delay(delaylaser);

  if( (analogRead(0) > sensor ) && (g == 0) )

  {
    digitalWrite(13, HIGH);
    noteOn(0x90, note7, 0x7F);
    g++;
  }


  else if(analogRead(0) < sensor )
  {
    digitalWrite(13, LOW);
    noteOn(0x90, note7, 0x00);
    g = 0;
  }

  digitalWrite(LaserPin, LOW);


  anticlockwise();
  delay(delaymotor);


  digitalWrite(LaserPin, HIGH);    //This is beam 6
  delay(delaylaser);

  if( (analogRead(0) > sensor ) && (f == 0) )

  {

    digitalWrite(13, HIGH);
    noteOn(0x90, note6, 0x7F);
    f++;
  }


  else if(analogRead(0) < sensor )

  {
    digitalWrite(13, LOW);
    noteOn(0x90, note6, 0x00);
    f = 0;
  }

  digitalWrite(LaserPin, LOW);


  anticlockwise();
  delay(delaymotor);


  digitalWrite(LaserPin, HIGH);    //This is beam 5
  delay(delaylaser);

  if( (analogRead(0) > sensor ) && (e == 0) )

  {
    digitalWrite(13, HIGH);
    noteOn(0x90, note5, 0x7F);
    e++;
  }


  else if(analogRead(0) < sensor )

  {
    digitalWrite(13, LOW);
    noteOn(0x90, note5, 0x00);
    e = 0;
  }

  digitalWrite(LaserPin, LOW);

  anticlockwise();
  delay(delaymotor);


  digitalWrite(LaserPin, HIGH);      //This is beam 4
  delay(delaylaser);

  if( (analogRead(0) > sensor ) && (d == 0) )

  {
    digitalWrite(13, HIGH);
    noteOn(0x90, note4, 0x7F);
    d++;
  }

  else if(analogRead(0) < sensor )

  {
    digitalWrite(13, LOW);
    noteOn(0x90, note4, 0x00);
    d = 0;
  }

  digitalWrite(LaserPin, LOW);

  anticlockwise();
  delay(delaymotor);


  digitalWrite(LaserPin, HIGH);    //This is beam 3
  delay(delaylaser);

  if( (analogRead(0) > sensor ) && (c == 0) )
  {
    digitalWrite(13, HIGH);
    noteOn(0x90, note3, 0x7F);
    c++;
  }


  else if(analogRead(0) < sensor )

  {
    digitalWrite(13, LOW);
    noteOn(0x90, note3, 0x00);
    c = 0;
  }

  digitalWrite(LaserPin, LOW);

  anticlockwise();
  delay(delaymotor);

  digitalWrite(LaserPin, HIGH);    //This is beam 2
  delay(delaylaser);

  if(true || (analogRead(0) > sensor ) && (b == 0) )

  {
    digitalWrite(13, HIGH);
    noteOn(0x90, note2, 0x7F);
    b++;
  }


  else if(analogRead(0) < sensor )

  {
    digitalWrite(13, LOW);
    noteOn(0x90, note2, 0x00);
    b = 0;
  }

  digitalWrite(LaserPin, LOW);


  anticlockwise();
  delay(delaymotor);


// Back to top.

}
