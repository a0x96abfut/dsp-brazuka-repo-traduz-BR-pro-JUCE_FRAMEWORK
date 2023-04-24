/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Vst3projectbifutiAudioProcessorEditor  : public juce::AudioProcessorEditor,private juce::Slider::Listener     // [2]
{
public:
    Vst3projectbifutiAudioProcessorEditor (Vst3projectbifutiAudioProcessor&);
    ~Vst3projectbifutiAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    void sliderValueChanged (juce::Slider* slider) override; // [3]
    Vst3projectbifutiAudioProcessor& audioProcessor;
    juce::Slider midiVolume; // [1]
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Vst3projectbifutiAudioProcessorEditor)
};
