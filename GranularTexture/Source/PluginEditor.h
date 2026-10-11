#pragma once

#include "PluginProcessor.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include <memory>

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

    juce::Slider grainLengthKnob;
    std::unique_ptr<SliderAttachment> grainLenghtAttachement;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularTextureEngineAudioProcessorEditor)
};
