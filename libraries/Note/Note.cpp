/*
	Note.h
*/

#include "Note.h"

#define TOTAL_NOTES 12

int _noteValue(NoteName name)
{
	switch (name) {
		case C: return 0;
		case CSharp: return 1;
		case D: return 2;
		case DSharp: return 3;
		case E: return 4;
		case F: return 5;
		case FSharp: return 6;
		case G: return 7;
		case GSharp: return 8;
		case A: return 9;
		case ASharp: return 10;
		case B: return 11;
	}
}

Note::Note(NoteName name)
{
	_name = name;
}

int Note::midiValue(int octave)
{
	int noteVal = _noteValue(_name);
	int value = (12 * octave) + noteVal;
	return value;
}

String Note::name()
{
	switch (_name) 
	{
		case C: return "C";
		case CSharp: return "C#";
		case D: return "D";
		case DSharp: return "D#";
		case E: return "E";
		case F: return "F";
		case FSharp: return "F#";
		case G: return "G";
		case GSharp: return "G#";
		case A: return "A";
		case ASharp: return "A#";
		case B: return "B";
	}
}

String Note::debugName(int octave)
{
	String nameVal = name();
	int midiVal = midiValue(octave);

	return nameVal + " - (midi val: " + midiVal + ", octave: " + octave + ")";
}