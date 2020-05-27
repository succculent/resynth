/*
  ==============================================================================

    SynthSound.h
    Created: 26 May 2020 4:58:23pm
    Author:  Lorand Cheng

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public SynthesiserSound
{
public:
    bool appliesToNote(int /*midiNoteNumber*/)
    {
        return true;
    }
    bool appliesToChannel(int /*midiChannel*/)
    {
        return true;
    }
};
