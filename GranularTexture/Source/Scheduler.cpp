#include "Scheduler.h"

GrainScheduler::GrainScheduler(int samples) {
    samplesUntilNextGrain = samples;
    intervalSamples = samples;
}

void GrainScheduler::reset(int samples) {
    samplesUntilNextGrain = samples;
    intervalSamples = samples;
}

bool GrainScheduler::tick(int numSamples) {
    samplesUntilNextGrain -= numSamples;
    if (samplesUntilNextGrain <= 0) {
        samplesUntilNextGrain += intervalSamples;
        return true;
    }

    return false;
}
