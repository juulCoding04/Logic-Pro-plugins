#include "PluginProcessor.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_events/juce_events.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include "PluginEditor.h"

//==============================================================================
GranularTextureEngineAudioProcessorEditor::GranularTextureEngineAudioProcessorEditor (GranularTextureEngineAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processorRef (p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    // --- grain length ---
    grainLengthKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    grainLengthKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    grainLengthKnob.setPopupDisplayEnabled(true, false, this);
    addAndMakeVisible(&grainLengthKnob);

    grainLengthLabel.setText("Grain Length", juce::dontSendNotification);
    grainLengthLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    grainLengthLabel.attachToComponent(&grainLengthKnob, false);

    grainLenghtAttachement.reset(new SliderAttachment (valueTreeState, "grainLength", grainLengthKnob));

    // --- grain rate Hz ---
    grainRateHzKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    grainRateHzKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    grainRateHzKnob.setPopupDisplayEnabled(true, false, this);
    addAndMakeVisible(&grainRateHzKnob);

    grainRateHzLabel.setText("Grain Rate (Hz)", juce::dontSendNotification);
    grainRateHzLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    grainRateHzLabel.attachToComponent(&grainRateHzKnob, false);

    grainRateHzAttachement.reset(new SliderAttachment(valueTreeState, "grainRate", grainRateHzKnob));

    // --- grain pool ---
    grainPoolSlider.setSliderStyle(juce::Slider::LinearBarVertical);
    grainPoolSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    grainPoolSlider.setPopupDisplayEnabled(true, false, this);
    addAndMakeVisible(&grainPoolSlider);

    grainPoolLabel.setText("Pool", juce::dontSendNotification);
    grainPoolLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    grainPoolLabel.attachToComponent(&grainPoolSlider, false);

    grainPoolAttachement.reset(new SliderAttachment(valueTreeState, "grainPool", grainPoolSlider));
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
    g.drawFittedText (VERSION, getLocalBounds(), juce::Justification::centred, 1);
}

void GranularTextureEngineAudioProcessorEditor::resized()
{
    // set position with arguments (x, y, width, height)
    grainLengthKnob.setBounds(40, 30, 100, 100);
    grainRateHzKnob.setBounds(180, 30, 100, 100);
    grainPoolSlider.setBounds(70, 180, 50, 100);
}
