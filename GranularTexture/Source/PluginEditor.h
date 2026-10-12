#pragma once

#include "PluginProcessor.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include <memory>

#define VERSION "v0.1.0"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

//==============================================================================
class GranularTextureEngineAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit GranularTextureEngineAudioProcessorEditor (GranularTextureEngineAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~GranularTextureEngineAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GranularTextureEngineAudioProcessor& processorRef;
    juce::AudioProcessorValueTreeState& valueTreeState;

    juce::Label grainLengthLabel;
    juce::Slider grainLengthKnob;
    std::unique_ptr<SliderAttachment> grainLenghtAttachement;

    juce::Label grainRateHzLabel;
    juce::Slider grainRateHzKnob;
    std::unique_ptr<SliderAttachment> grainRateHzAttachement;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularTextureEngineAudioProcessorEditor)
};
