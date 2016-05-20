/*
	Note.h
*/

#ifndef NOTE_h
#define NOTE_h

#include "Arduino.h"

enum NoteName {
   C, CSharp, D, DSharp, E, F, FSharp, G, GSharp, A, ASharp, B
};

class Note
{
	public:
		Note();
		Note(NoteName name);
		int midiValue(int octave);

		String name();
		String debugName(int octave);
	private:
		NoteName _name;
};

struct MIDIEvent {
  Note note;
  int octave;
};

#endif