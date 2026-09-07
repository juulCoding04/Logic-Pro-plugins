#pragma once
#include "PluginProcessor.h"

class HelloWorldPluginAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit HelloWorldPluginAudioProcessorEditor (HelloWorldPluginAudioProcessor&);
    ~HelloWorldPluginAudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override {}

private:
    HelloWorldPluginAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloWorldPluginAudioProcessorEditor)
};
