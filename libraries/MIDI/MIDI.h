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
    void playEvent(MIDIEvent event);

    void stopPlayingNote(Note note, int octave);
    void stopPlayingEvent(MIDIEvent event);
  private:
  	bool _debug = false;
};

#endif