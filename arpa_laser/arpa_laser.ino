#include <Stepper.h>
#include <MIDI.h>
#include <Note.h>

#define DEBUG_MODE false

/*----- Stepper-related Constants -----*/
#define STEPS_FOR_FULL_ROTATION 48
#define STEP_DISTANCE 1
#define STEPPER_SPEED 10

/*----- Laser-related Constants -----*/
#define LASER_DELAY 9
// If this is too small, the stepper will freak out.
#define LASER_SHORTSTOP 4
#define LASER_PIN 7

/*----- Note-related Constants -----*/
#define TOTAL_NOTES 5
#define MIDI_BAUD 31250
#define DEBUG_BAUD 9600

/*----- Declare objects -----*/
Stepper stepper(STEPS_FOR_FULL_ROTATION, 8, 9, 10, 11);
MIDI midi;
Note note(NoteName::FSharp);

/*---- Setup Methods ----*/
void _setupLaserPin()
{
  pinMode(LASER_PIN, OUTPUT);
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
  
  midi.connectWithMode(MIDIConnectionMode::Play);
}

bool playing1, playing2, playing3, playing4, playing5 = false;

void setPlaying(int noteNumber, bool playing)
{
  if (noteNumber == 1) {
    playing1 = playing;
  }
  else if (noteNumber == 2) {
    playing2 = playing;
  }
  else if (noteNumber == 3) {
    playing3 = playing;
  }
  else if (noteNumber == 4) {
    playing4 = playing;
  }
  else if (noteNumber == 5) {
    playing5 = playing;
  }
}

int isPlaying(int noteNumber)
{
  if (noteNumber == 1) {
    return playing1;
  }
  else if (noteNumber == 2) {
    return playing2;
  }
  else if (noteNumber == 3) {
    return playing3;
  }
  else if (noteNumber == 4) {
    return playing4;
  }
  else if (noteNumber == 5) {
    return playing5;
  }
  return false;
}

void theLoopFunctionToBeUsed()
{
  Note noteNames[] = {GSharp, DSharp, ASharp, B, DSharp};
  Note majorNoteNames[] = {E, B, FSharp, GSharp, B};

  int octaves[] = {3, 4, 4, 4, 5};
  int majorOctaves[] {3, 3, 4, 4, 4};
  
  // Reduce blur on the beginning note.
  delay(LASER_SHORTSTOP);

  for (int noteIndex = 0; noteIndex < TOTAL_NOTES; ++noteIndex)
  {
    turnLaserON();
    // read photoresistor value and play or turn note off

    delay(LASER_DELAY);
    int light = analogRead(0);

    Note note(majorNoteNames[noteIndex]);
    int octave = majorOctaves[noteIndex];
    
    if (light > 3) {
      if (!isPlaying(noteIndex + 1)) {
        setPlaying(noteIndex + 1, true);
        midi.playNote(note, octave); 
      }
    }
    else {
      setPlaying(noteIndex + 1, false);
      midi.stopPlayingNote(note, octave);
    }

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

void testingLoop()
{
  Note noteNames[] = {GSharp, DSharp, ASharp, B, DSharp};
  Note majorNoteNames[] = {E, B, FSharp, GSharp, B};

  int octaves[] = {3, 4, 4, 4, 5};
  int majorOctaves[] {3, 3, 4, 4, 4};

  for (int i = 0; i < 5; ++i) {
    Note note(noteNames[i]);
    int octave = octaves[i];
    midi.playNote(note, octave);

    delay(500);
  }

  for (int i = 0; i < 5; ++i) { 
    Note note(noteNames[i]);
    int octave = octaves[i];
    midi.stopPlayingNote(note, octave);
  }


  for (int i = 0; i < 5; ++i) {
    Note note(majorNoteNames[i]);
    int octave = majorOctaves[i];
    midi.playNote(note, octave);

    delay(500);
  }

  for (int i = 0; i < 5; ++i) { 
    Note note(majorNoteNames[i]);
    int octave = majorOctaves[i];
    midi.stopPlayingNote(note, octave);
  }
}

void loop()
{
  theLoopFunctionToBeUsed();
//  testingLoop();
}
