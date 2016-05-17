/*
  MIDI.h
*/

#ifndef MIDI_h
#define MIDI_h

#include "Arduino.h"
#include "Note.h"

enum MIDIConnectionMode {
	Debug,
	Play
};

class MIDI
{
  public:
    MIDI();

    void connectWithMode(MIDIConnectionMode mode);

    void playNote(Note note, int octave);
    void stopPlayingNote(Note note, int octave);
  private:
  	bool _debug = false;
};

#endif