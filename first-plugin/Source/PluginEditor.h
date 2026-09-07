#pragma once
#include "PluginProcessor.h"
#include "juce_gui_basics/juce_gui_basics.h"

class HelloWorldPluginAudioProcessorEditor : public juce::AudioProcessorEditor,
                                                    juce::Slider::Listener
{
public:
    HelloWorldPluginAudioProcessorEditor (HelloWorldPluginAudioProcessor&);
    ~HelloWorldPluginAudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    HelloWorldPluginAudioProcessor& processorRef;

    // default callback function
    void sliderValueChanged(juce::Slider* slider) override;

    // create a slider object to controll midi volume
    juce::Slider midiVolume;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloWorldPluginAudioProcessorEditor)
};
