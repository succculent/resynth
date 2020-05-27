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
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound(SynthesiserSound *sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    //========================================
    void startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    }
    //========================================
    void stopNote(float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        allowTailOff = true;
        clearCurrentNote();
    }
    //========================================
    void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {
        env1.setAttack(2000);
        env1.setDecay(500);
        env1.setSustain(0.8);
        env1.setRelease(2000);
        
        for(int sample = 0; sample < numSamples; sample++)
        {
            double wave = osc1.square(frequency);
            wave = env1.adsr(wave, env1.trigger) * level;
            wave = filter.lores(wave, 200, 0.1);
            for(int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
            {
                outputBuffer.addSample(channel, startSample, wave);
            }
            startSample++;
        }
        
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
    
private:
    double level;
    double frequency;
    
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter;
};

