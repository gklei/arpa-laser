/*
  Scale.h
*/

#ifndef SCALE_h
#define SCALE_h

#include "Arduino.h"
#include "Note.h"

enum NoteIndex {
  NoteIndex1,
  NoteIndex2,
  NoteIndex3,
  NoteIndex4,
  NoteIndex5
};

enum ScaleType {
  MinorPentatonic,
  MajorPentatonic,
  MinorHarmonic,
  Ethiopian,
  EthiopianMajor,
  Major7_2,
  Minor7_2
};

class Scale
{
  public:
    Scale();

    int totalNotes();
    NoteIndex* noteIndexArray();

    MIDIEvent midiEvent(NoteIndex index, ScaleType scale);
  private:
};

#endif