#include "PluginProcessor.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include "PluginEditor.h"

//==============================================================================
GranularTextureEngineAudioProcessorEditor::GranularTextureEngineAudioProcessorEditor (GranularTextureEngineAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    // define parameters for the grain length slider
    grainLength.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    grainLength.setRange(0.0, 500.0, 1.0);
    grainLength.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    grainLength.setPopupDisplayEnabled(true, false, this);
    grainLength.setValue(200.0);

    addAndMakeVisible(&grainLength);
}

GranularTextureEngineAudioProcessorEditor::~GranularTextureEngineAudioProcessorEditor()
{
}

//==============================================================================
void GranularTextureEngineAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::white);

    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("v0.3.1", getLocalBounds(), juce::Justification::centred, 1);
}

void GranularTextureEngineAudioProcessorEditor::resized()
{
    // set position with arguments (x, y, width, height)
    grainLength.setBounds(40, 30, 100, 100);
}
