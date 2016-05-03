
enum Note {
  C, CSharp, D, DSharp, E, F, FSharp, G, GSharp, A, ASharp, B
};

enum Octave {
  First, Second
};

String noteName(Note note)
{
  String noteName = "";
  switch (note) 
  {
    case C:
      noteName = "C";
      break;
    case CSharp:
      noteName = "C#";
      break;
    case D:
      noteName = "D";
      break;
    case DSharp:
      noteName = "D#";
      break;
    case E:
      noteName = "E";
      break;
    case F:
      noteName = "F";
      break;
    case FSharp:
      noteName = "F#";
      break;
    case G:
      noteName = "G";
      break;
    case GSharp:
      noteName = "G#";
      break;
    case A:
      noteName = "A";
      break;
    case ASharp:
      noteName = "A#";
      break;
    case B:
      noteName = "B";
      break;
  }
  return noteName;
}

int cMidiValue(Octave octave)
{
  switch (octave) {
    case First: return 36;
    case Second: return 48;
  }
}

int cSharpMidiValue(Octave octave)
{
  switch (octave) {
    case First: return 37;
    case Second: return 49;
  }
}

int dMidiValue(Octave octave)
{
  switch (octave) {
    case First: return 38;
    case Second: return 50;
  }
}

int dSharpMidiValue(Octave octave)
{
  switch (octave) {
    case First: return 39;
    case Second: return 51;
  }
}

int eMidiValue(Octave octave)
{
  switch (octave) {
    case First: return 40;
    case Second: return 52;
  }
}

int fMidiValue(Octave octave)
{
  switch (octave) {
    case First: return 41;
    case Second: return 53;
  }
}

int fSharpMidiValue(Octave octave)
{
  switch (octave) {
    case First: return 42;
    case Second: return 54;
  }
}

int gMidiValue(Octave octave)
{
  switch (octave) {
    case First: return 43;
    case Second: return 55;
  }
}

int gSharpMidiValue(Octave octave)
{
  switch (octave) {
    case First: return 44;
    case Second: return 56;
  }
}

int aMidiValue(Octave octave)
{
  switch (octave) {
    case First: return 45;
    case Second: return 57;
  }
}

int aSharpMidiValue(Octave octave)
{
  switch (octave) {
    case First: return 46;
    case Second: return 58;
  }
}

int bMidiValue(Octave octave)
{
  switch (octave) {
    case First: return 47;
    case Second: return 59;
  }
}

int midiValue(Note note, Octave octave)
{
  switch (note) 
  {
    case C: return cMidiValue(octave); break;
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

void playNote(Note note, Octave octave, float seconds)
{ 
  playNote(note, octave);
  delay(seconds * 1000);

  stopNote(note, octave);
}

void loop() 
{
  Note notes[] = {C, D, E, FSharp, GSharp, ASharp, C};
  Octave octaves[] = {First, First, First, First, First, First, Second};

  for (int i = 0; i < 7; i = i + 1) 
  {
    playNote(notes[i], octaves[i], 0.1);
  }
}
