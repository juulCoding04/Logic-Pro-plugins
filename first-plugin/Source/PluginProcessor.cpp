#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_core/juce_core.h"

HelloWorldPluginAudioProcessor::HelloWorldPluginAudioProcessor()
    : AudioProcessor (BusesProperties()
        .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
}

void HelloWorldPluginAudioProcessor::prepareToPlay (double, int) {}

void HelloWorldPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    buffer.clear();
    juce::MidiBuffer processMidi;

    for (const auto metadata : midiMessages) {
        auto message = metadata.getMessage();
        const auto time = metadata.samplePosition;

        if (message.isNoteOn()) {
            message = juce::MidiMessage::noteOn(message.getChannel(), message.getNoteNumber(), (juce::uint8) noteOnVel);
        }

        processMidi.addEvent(message, time);
    }
    midiMessages.swapWith(processMidi);
}

juce::AudioProcessorEditor* HelloWorldPluginAudioProcessor::createEditor()
{
    return new HelloWorldPluginAudioProcessorEditor (*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HelloWorldPluginAudioProcessor();
}
