#include <Stepper.h>
#include <MIDI.h>
#include <Note.h>
#include <Scale.h>

#define DEBUG_MODE false

/*----- Stepper-related Constants -----*/
#define STEPS_FOR_FULL_ROTATION 48
#define STEP_DISTANCE 1
#define STEPPER_SPEED 1000

/*----- Laser-related Constants -----*/
#define LASER_DELAY 18
// If this is too small, the stepper will freak out.
#define LASER_SHORTSTOP 4
#define LASER_PIN 7

#define LASER_THRESHOLD 100

/*----- Note-related Constants -----*/
#define MIDI_BAUD 31250
#define DEBUG_BAUD 9600

/*----- Button-related Constants -----*/
#define BUTTON_PIN 2

/*----- Declare objects -----*/
Stepper stepper(STEPS_FOR_FULL_ROTATION, 8, 9, 10, 11);
MIDI midi;
Note note(NoteName::FSharp);
Scale scale;

bool playing1, playing2, playing3, playing4, playing5 = false;
NoteIndex noteIndicies[5] = { NoteIndex1, NoteIndex2, NoteIndex3, NoteIndex4, NoteIndex5 };
ScaleType currentScaleType = ScaleType::Ethiopian;

/*---- Setup Methods ----*/
void _setupLaserPin()
{
  pinMode(LASER_PIN, OUTPUT);
}

void _setupButtons()
{
  pinMode(13, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
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
  delay(LASER_SHORTSTOP);
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
  _setupButtons();
  stepper.setSpeed(STEPPER_SPEED);

  if (DEBUG_MODE) {
    midi.connectWithMode(MIDIConnectionMode::Debug);
  } else {
    midi.connectWithMode(MIDIConnectionMode::Play);
  }
}

void setPlaying(int noteIndex, bool playing)
{
  if (noteIndex == 0) {
    playing1 = playing;
  }
  else if (noteIndex == 1) {
    playing2 = playing;
  }
  else if (noteIndex == 2) {
    playing3 = playing;
  }
  else if (noteIndex == 3) {
    playing4 = playing;
  }
  else if (noteIndex == 4) {
    playing5 = playing;
  }
}

int isPlaying(int noteIndex)
{
  if (noteIndex == 0) {
    return playing1;
  }
  else if (noteIndex == 1) {
    return playing2;
  }
  else if (noteIndex == 2) {
    return playing3;
  }
  else if (noteIndex == 3) {
    return playing4;
  }
  else if (noteIndex == 4) {
    return playing5;
  }
  return false;
}

void advanceScaleType()
{
  currentScaleType = scale.next(currentScaleType);
}

void printcurrentScaleTypeName()
{
  String currentScaleTypeName = scale.scaleName(currentScaleType);
  Serial.println(currentScaleTypeName); 
}

float lastTimestamp = 0;
void loop()
{
//  float currentTimestamp = millis();
//  if (currentTimestamp - lastTimestamp > (10 * 1000)) 
//  {
//    lastTimestamp = currentTimestamp;
//    turnOffAllNotes(currentScaleType);
//    advanceScaleType();
//  }
  
  laser_harp_loop();
}

void scale_testing_loop()
{
  printcurrentScaleTypeName();
  advanceScaleType();
  delay(1000);
}

int buttonState = 0;
void button_testing_loop()
{
  buttonState = digitalRead(BUTTON_PIN);
  Serial.println(buttonState);
  
  if (buttonState == HIGH) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }

  delay(100);
}

void turnOffAllNotes(ScaleType type)
{
  for (int index = 0; index < scale.totalNotes(); ++index)
  {
    NoteIndex noteIndex = noteIndicies[index];
    MIDIEvent event = scale.midiEvent(noteIndex, type);
    midi.stopPlayingEvent(event);
  }
}

void laser_harp_loop()
{
  // Reduce blur on the beginning note.
  delay(LASER_SHORTSTOP);
  for (int index = 0; index < scale.totalNotes(); ++index)
  {
    turnLaserON();
    
    delay(LASER_DELAY);
    int light = analogRead(0);
    printSensorValueToConsoleIfInDebug();

    NoteIndex noteIndex = noteIndicies[index];
    MIDIEvent event = scale.midiEvent(noteIndex, currentScaleType);
       
    if (light > LASER_THRESHOLD) {
      if (!isPlaying(index)) {
        setPlaying(index, true);
        midi.playEvent(event);
      }
    }
    else {
      setPlaying(noteIndex, false);
      midi.stopPlayingEvent(event);
    }

    turnLaserOFF();
    delay(2);
    stepper.step(STEP_DISTANCE);
    delay(4);
  }
  
  // Don't draw lasers on the downstroke, to reduce blur.
  for (int noteIndex = scale.totalNotes(); noteIndex > 0; --noteIndex)
  {
    stepper.step(-STEP_DISTANCE);
    delay(LASER_SHORTSTOP);
  }
}

