/*
	Scale.cpp
*/

#include "Scale.h"

#define TOTAL_NOTES 5

// Private function declarations
NoteName* _noteNames(ScaleType type);
int* _octaves(ScaleType type);
Note* _notesForScale(ScaleType type);
Note* _notes(NoteName* names);

Scale::Scale()
{
}

MIDIEvent Scale::midiEvent(NoteIndex index, ScaleType scale)
{
	Note* notes = _notesForScale(scale);
	int* octaves = _octaves(scale);

	Note note = notes[index];
	int octave = octaves[index];

	MIDIEvent event = { note, octave };

	delete notes;
	delete octaves;

	return event;
}

int Scale::totalNotes()
{
	return TOTAL_NOTES;
}

NoteIndex* Scale::noteIndexArray()
{
	NoteIndex indicies[TOTAL_NOTES] = {
	  NoteIndex1,
	  NoteIndex2,
	  NoteIndex3,
	  NoteIndex4,
	  NoteIndex5 
	};

	return indicies;
}

Note* _notesForScale(ScaleType type)
{
	Note* results = new Note[TOTAL_NOTES];
	NoteName* names = _noteNames(type);

	for (int i = 0; i < TOTAL_NOTES; ++i) {
		results[i] = Note(names[i]);
	}

	delete names;
	return results;
}

NoteName* _noteNames(ScaleType type)
{
	NoteName* names = new NoteName[TOTAL_NOTES];

	switch (type) {
		case MinorPentatonic: 
			names[0] = C;
			names[1] = DSharp;
			names[2] = F;
			names[3] = G;
			names[4] = ASharp;
			break;
		case MajorPentatonic: 
			names[0] = C;
			names[1] = G;
			names[2] = D;
			names[3] = E;
			names[4] = C;
			break;
		case MinorHarmonic: 
			names[0] = C;
			names[1] = G;
			names[2] = GSharp;
			names[3] = B;
			names[4] = C;
			break;
		case Ethiopian: 
			names[0] = C;
			names[1] = CSharp;
			names[2] = F;
			names[3] = G;
			names[4] = GSharp;
			break;
		case Major7_2: 
			names[0] = C;
			names[1] = G;
			names[2] = D;
			names[3] = E;
			names[4] = B;
			break;
		case Minor7_2: 
			names[0] = C;
			names[1] = DSharp;
			names[2] = G;
			names[3] = D;
			names[4] = ASharp;
			break;
		case EthiopianMajor: 
			names[0] = C;
			names[1] = CSharp;
			names[2] = F;
			names[3] = GSharp;
			names[4] = C;
			break;
	}

	return names;
}

int* _octaves(ScaleType type)
{
	int* octaves = new int[TOTAL_NOTES];

	switch (type) {
		case MinorPentatonic: 
			octaves[0] = 4;
			octaves[1] = 4;
			octaves[2] = 4;
			octaves[3] = 4;
			octaves[4] = 4;
			break;
		case MajorPentatonic: 
			octaves[0] = 4;
			octaves[1] = 4;
			octaves[2] = 4;
			octaves[3] = 5;
			octaves[4] = 5;
			break;
		case MinorHarmonic: 
			octaves[0] = 4;
			octaves[1] = 4;
			octaves[2] = 4;
			octaves[3] = 4;
			octaves[4] = 5;
			break;
		case Ethiopian: 
			octaves[0] = 4;
			octaves[1] = 4;
			octaves[2] = 4;
			octaves[3] = 4;
			octaves[4] = 4;
			break;
		case EthiopianMajor: 
			octaves[0] = 4;
			octaves[1] = 4;
			octaves[2] = 4;
			octaves[3] = 4;
			octaves[4] = 5;
			break;
		case Major7_2: 
			octaves[0] = 4;
			octaves[1] = 4;
			octaves[2] = 5;
			octaves[3] = 5;
			octaves[4] = 5;
			break;
		case Minor7_2: 
			octaves[0] = 4;
			octaves[1] = 4;
			octaves[2] = 4;
			octaves[3] = 5;
			octaves[4] = 5;
			break;
	}

	return octaves;
}

Note* _notes(NoteName* names)
{
	int count = sizeof(names) / sizeof(NoteName);
	Note* notes = new Note[count];

	for (int i = 0; i < count; ++i) {
		notes[i] = Note(names[i]);
	}

	return notes;
}