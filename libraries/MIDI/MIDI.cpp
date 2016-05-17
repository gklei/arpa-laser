/*
  MIDI.cpp
*/

#define DEBUGGING_BAUD_RATE 9600
#define MIDI_BAUD_RATE 31250

#include "MIDI.h"

MIDI::MIDI()
{
}

void MIDI::connectWithMode(MIDIConnectionMode mode)
{
	switch (mode) {
		case Debug:
			Serial.begin(DEBUGGING_BAUD_RATE);
			_debug = true;
			break;
		case Play:
			Serial.begin(MIDI_BAUD_RATE);
			break;
	}
}

void MIDI::playNote(Note note, int octave)
{
	if (_debug) {
		Serial.println("Playing note: " + note.debugName(octave));
	}
	else {
	    Serial.write(0x90);
	    Serial.write(note.midiValue(octave));
	    Serial.write(0x7F); 
	}
}

void MIDI::stopPlayingNote(Note note, int octave)
{
	if (_debug) {
		// Serial.println("Stopping note!");
	}
	else {
	    Serial.write(0x90);
	    Serial.write(note.midiValue(octave));
	    Serial.write(0);
	}
}