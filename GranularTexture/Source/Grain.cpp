#include "Grain.h"
#include "juce_core/juce_core.h"

void Grain::start(int newStartSample, int newLengthSamples) {
    startSample = newStartSample;
    lengthSamples = newLengthSamples;
    currentSample = startSample;
    progress = 0;
    active = true;
}

void Grain::advance(int samplesRead, int circularBufferSize) {
    currentSample += samplesRead;
    currentSample %= circularBufferSize;
    progress += samplesRead;

    if (progress >= lengthSamples) {
        active = false;
    }
}

float Grain::getEnvValue() {
    float fraction = (float) progress / (float) (lengthSamples - 1); // n/N
    float windowValue = 0.5 - 0.5 * std::cos(2 * juce::MathConstants<float>::pi * fraction);
    return windowValue;
}
