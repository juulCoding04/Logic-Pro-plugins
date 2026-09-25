#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "juce_core/juce_core.h"

//==============================================================================
GranularTextureEngineAudioProcessor::GranularTextureEngineAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
{
}

GranularTextureEngineAudioProcessor::~GranularTextureEngineAudioProcessor()
{
}

//==============================================================================
const juce::String GranularTextureEngineAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GranularTextureEngineAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GranularTextureEngineAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GranularTextureEngineAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GranularTextureEngineAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GranularTextureEngineAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GranularTextureEngineAudioProcessor::getCurrentProgram()
{
    return 0;
}

void GranularTextureEngineAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String GranularTextureEngineAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void GranularTextureEngineAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void GranularTextureEngineAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // set size of circularBuffer
    auto circularBufferSize = sampleRate * 2.0; // 2 seconds of sound
    circularBuffer.setSize(getTotalNumOutputChannels(), (int)circularBufferSize);
    circularBuffer.clear();

    writePosition = 0;

    int grainRateSamples = static_cast<int>(sampleRate / 4.0); // 4 grains/sec
    scheduler.reset(grainRateSamples);
}

void GranularTextureEngineAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool GranularTextureEngineAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

void GranularTextureEngineAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;

    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    const int bufferSize = buffer.getNumSamples();
    const int circularBufferSize = circularBuffer.getNumSamples();

    if (circularBufferSize <= 0 || bufferSize <= 0)
        return;

    // Clear unused output channels
    for (int channel = totalNumInputChannels;
         channel < totalNumOutputChannels;
         ++channel)
    {
        buffer.clear(channel, 0, bufferSize);
    }

    // write input to circular buffer

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        if (writePosition + bufferSize <= circularBufferSize)
        {
            // No wraparound
            circularBuffer.copyFrom(
                channel,
                writePosition,
                channelData,
                bufferSize);
        }
        else
        {
            // Wraparound
            const int numSamplesToEnd =
                circularBufferSize - writePosition;

            const int numSamplesFromStart =
                bufferSize - numSamplesToEnd;

            // First part -> end of circular buffer
            circularBuffer.copyFrom(
                channel,
                writePosition,
                channelData,
                numSamplesToEnd);

            // Remaining part -> beginning of circular buffer
            circularBuffer.copyFrom(
                channel,
                0,
                channelData + numSamplesToEnd,
                numSamplesFromStart);
        }
    }

    buffer.clear();

    if (scheduler.tick(bufferSize)) {
        for (int i = 0; i < grains.size(); i++) {
            if (grains[i].isIdle()) {
                int newCurrent = writePosition - GRAIN_LEN;
                if (newCurrent < 0) {
                    newCurrent += circularBufferSize;
                }
                grains[i].start(newCurrent, GRAIN_LEN);
                break;
            }
        }
        // all grains busy
    }

    // read active grains
    
    for (int i = 0; i < grains.size(); i++) {
        if (grains[i].isIdle())
            continue; // grain is idle so nothing to read

        const int samplesLeft = juce::jmax(0, grains[i].getLengthSamples() - grains[i].getProgress());
        const int samplesToRead = juce::jmin(bufferSize, samplesLeft);

        if (samplesToRead > 0)
        {
            int readPosition = grains[i].getCurrentSample();
            readPosition %= circularBufferSize;

            for (int channel = 0; channel < totalNumInputChannels; ++channel)
            {
                if (readPosition + samplesToRead <= circularBufferSize)
                {
                    // No wraparound
                    buffer.addFrom(
                        channel,
                        0,
                        circularBuffer.getReadPointer(channel, readPosition),
                        samplesToRead);
                }
                else
            {
                    // Grain wraps around circular buffer
                    const int numSamplesToEnd =
                        circularBufferSize - readPosition;

                    const int numSamplesFromStart =
                        samplesToRead - numSamplesToEnd;

                    buffer.addFrom(
                        channel,
                        0,
                        circularBuffer.getReadPointer(channel, readPosition),
                        numSamplesToEnd);

                    buffer.addFrom(
                        channel,
                        numSamplesToEnd,
                        circularBuffer.getReadPointer(channel, 0),
                        numSamplesFromStart);
                }
            }

            // Advance grain ONCE, after processing all channels
            grains[i].advance(samplesToRead, circularBufferSize);
        }
    }

    // advance circular buffer once
    writePosition += bufferSize;
    writePosition %= circularBufferSize;
}

//==============================================================================
bool GranularTextureEngineAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GranularTextureEngineAudioProcessor::createEditor()
{
    return new GranularTextureEngineAudioProcessorEditor (*this);
}

//==============================================================================
void GranularTextureEngineAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void GranularTextureEngineAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GranularTextureEngineAudioProcessor();
}
