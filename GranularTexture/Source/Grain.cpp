#include "Grain.h"

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
