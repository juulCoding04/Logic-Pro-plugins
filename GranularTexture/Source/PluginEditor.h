#pragma once

#include "PluginProcessor.h"
#include "juce_gui_basics/juce_gui_basics.h"

//==============================================================================
class GranularTextureEngineAudioProcessorEditor final : public juce::AudioProcessorEditor, private juce::Slider::Listener
{
public:
    explicit GranularTextureEngineAudioProcessorEditor (GranularTextureEngineAudioProcessor&);
    ~GranularTextureEngineAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged (juce::Slider* slider) override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GranularTextureEngineAudioProcessor& processorRef;

    juce::Slider grainLengthKnob;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularTextureEngineAudioProcessorEditor)
};
