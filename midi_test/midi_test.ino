
enum Note {
  C, CSharp, D, DSharp, E, F, FSharp, G, GSharp, A, ASharp, B
};

enum Octave {
  Third, Fourth
};

int cMidiValue(Octave octave)
{
  switch (octave) {
    case Third: return 36;
    case Fourth: return 48;
  }
}

int cSharpMidiValue(Octave octave)
{
  switch (octave) {
    case Third: return 37;
    case Fourth: return 49;
  }
}

int dMidiValue(Octave octave)
{
  switch (octave) {
    case Third: return 38;
    case Fourth: return 50;
  }
}

int dSharpMidiValue(Octave octave)
{
  switch (octave) {
    case Third: return 39;
    case Fourth: return 51;
  }
}

int eMidiValue(Octave octave)
{
  switch (octave) {
    case Third: return 40;
    case Fourth: return 52;
  }
}

int fMidiValue(Octave octave)
{
  switch (octave) {
    case Third: return 41;
    case Fourth: return 53;
  }
}

int fSharpMidiValue(Octave octave)
{
  switch (octave) {
    case Third: return 42;
    case Fourth: return 54;
  }
}

int gMidiValue(Octave octave)
{
  switch (octave) {
    case Third: return 43;
    case Fourth: return 55;
  }
}

int gSharpMidiValue(Octave octave)
{
  switch (octave) {
    case Third: return 44;
    case Fourth: return 56;
  }
}

int aMidiValue(Octave octave)
{
  switch (octave) {
    case Third: return 45;
    case Fourth: return 57;
  }
}

int aSharpMidiValue(Octave octave)
{
  switch (octave) {
    case Third: return 46;
    case Fourth: return 58;
  }
}

int bMidiValue(Octave octave)
{
  switch (octave) {
    case Third: return 47;
    case Fourth: return 59;
  }
}

int midiValue(Note note, Octave octave)
{
  switch (note) 
  {
    case C: return cMidiValue(octave);
    case CSharp: return cSharpMidiValue(octave);
    case D: return dMidiValue(octave);
    case DSharp: return dSharpMidiValue(octave);
    case E: return eMidiValue(octave);
    case F: return fMidiValue(octave);
    case FSharp: return fSharpMidiValue(octave);
    case G: return gMidiValue(octave);
    case GSharp: return gSharpMidiValue(octave);
    case A: return aMidiValue(octave);
    case ASharp: return aSharpMidiValue(octave);
    case B: return bMidiValue(octave);
    default: return cMidiValue(octave);
  }
}

void setup() 
{
  Serial.begin(31250);
}

void playNote(Note note, Octave octave)
{
  Serial.write(0x90);

  int value = midiValue(note, octave);
  Serial.write(value);

  int velocity = 0x7F;
  Serial.write(velocity);
}

void stopNote(Note note, Octave octave)
{
  Serial.write(0x90);

  int value = midiValue(note, octave);
  Serial.write(value);
  Serial.write(0x00);
}

void playNote(Note note, Octave octave, float duration)
{ 
  playNote(note, octave);
  delay(duration * 1000);

  stopNote(note, octave);
}

void loop() 
{
  Note notes[] = {C, D, E, FSharp, GSharp, ASharp, C};
  Octave octaves[] = {Third, Third, Third, Third, Third, Third, Fourth};

  for (int i = 0; i < 7; i = i + 1) 
  {
    Note n = notes[i];
    Octave o = octaves[i];
    
    playNote(n, o, 0.25);
  }
}
