/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginSynthAudioProcessorEditor::AudioPluginSynthAudioProcessorEditor (AudioPluginSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1, 5000);
    //attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
    attackSlider.setValue(0.1);
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);
    
}

AudioPluginSynthAudioProcessorEditor::~AudioPluginSynthAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void AudioPluginSynthAudioProcessorEditor::resized()
{
    attackSlider.setBounds(10, 10, 40, 100);
}

void AudioPluginSynthAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if(slider == &attackSlider)
        processor.attackTime = attackSlider.getValue();
}
