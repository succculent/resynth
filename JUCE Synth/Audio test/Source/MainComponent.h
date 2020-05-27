/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "maximilian.h"

/*
 LINKING MAXIMILIAN
 1. "Maximilian libs" folder under JUCE synth contains useful maximilian files
 2. Drag that folder into the "Source" folder on the Projucer page for the desired project
 3. (OPTIONAL) Projucer -> Exporters -> Debug -> header search paths -> drag maximilian libs in there
 4. #include "maximilian.h"
 */

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    //white noise
    Random random;
    //sine wave
    Array<float> wavetable; //Array in JUCE is more like a vector in C++
    double wavetableSize;
    double frequency;
    double phase; //position in wavetable
    double increment; //defines how much to move over in wavetable
    double amplitude;
    //maximilian
    maxiOsc testOsc;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
