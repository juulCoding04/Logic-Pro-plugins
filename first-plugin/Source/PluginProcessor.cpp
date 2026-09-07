#include "PluginProcessor.h"
#include "PluginEditor.h"

HelloWorldPluginAudioProcessor::HelloWorldPluginAudioProcessor()
    : AudioProcessor (BusesProperties()
        .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
}

void HelloWorldPluginAudioProcessor::prepareToPlay (double, int) {}

void HelloWorldPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    // Does nothing to the audio yet — pass-through.
    juce::ignoreUnused (buffer);
}

juce::AudioProcessorEditor* HelloWorldPluginAudioProcessor::createEditor()
{
    return new HelloWorldPluginAudioProcessorEditor (*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HelloWorldPluginAudioProcessor();
}
