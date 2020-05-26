/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    frequency = 440;
    phase = 0;
    wavetableSize = 1024;
    increment = frequency * wavetableSize / sampleRate;
    amplitude = 0.25;
    //add values to wavetable (one cycle of a sine wave)
    for(int i = 0; i < wavetableSize; i++)
    {
        wavetable.insert(i, sin(2 * double_Pi * i / wavetableSize));
    }
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    /*WHITE NOISE - works for this, but using one pointer for left & right channels is wrong... see sine example

    for(int channel = 0; channel < bufferToFill.buffer->getNumChannels(); channel++)
    {
        float* const buffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
        for(int sample = 0; sample < bufferToFill.numSamples; sample++)
        {
            buffer[sample] = (random.nextFloat() * 2.0f - 1.0f)*0.25f;
        }
    }
     */
        float* const leftSpeaker = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
        float* const rightSpeaker = bufferToFill.buffer->getWritePointer(1, bufferToFill.startSample);
    
        for(int sample = 0; sample < bufferToFill.numSamples; sample++)
        {
            leftSpeaker[sample] = wavetable[(int)phase] * amplitude;
            rightSpeaker[sample] = wavetable[(int)phase] * amplitude;
            phase = fmod((phase + increment), wavetableSize); //wraps around
        }
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
