#include "PluginEditor.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"

HelloWorldPluginAudioProcessorEditor::HelloWorldPluginAudioProcessorEditor (HelloWorldPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    setSize (200, 200);

    midiVolume.setSliderStyle(juce::Slider::LinearBarVertical);
    midiVolume.setRange (0.0, 127.0, 1.0);
    midiVolume.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    midiVolume.setPopupDisplayEnabled (true, false, this);
    midiVolume.setTextValueSuffix (" Volume");
    midiVolume.setValue (1.0);

    // adds slider to the editor
    addAndMakeVisible (&midiVolume);
}

void HelloWorldPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);
    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Midi Volume", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void HelloWorldPluginAudioProcessorEditor::resized() {
    // sets the position and size of the slider with arguments (x, y, width, height)
    midiVolume.setBounds (40, 30, 20, getHeight() - 60);
}
