/*
  ==============================================================================

    SynthVoice.h
    Created: 26 May 2020 4:58:33pm
    Author:  Lorand Cheng

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound(SynthesiserSound *sound)
    {
        
    }
    //========================================
    void startNote(int midiNoteNUmner, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition)
    {
        
    }
    //========================================
    void stopNote(float velocity, bool allowTailOff)
    {
        
    }
    //========================================
    void pitchWheelMoved(int newPitchWheelValue)
    {
        
    }
    //========================================
    void controllerMoved(int controllerNumber, int newControllerValue)
    {
        
    }
    //========================================
    void renderNextBlock(AudioBuvver<float> &outputBuffer, int startSample, int numSamples)
    {
        
    }
    //========================================
private:
    
}

