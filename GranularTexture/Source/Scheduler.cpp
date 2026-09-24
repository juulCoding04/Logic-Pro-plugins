#include "Scheduler.h"

GrainScheduler::GrainScheduler(int samples) {
    samplesUntilNextGrain = samples;
    intervalSamples = samples;
}

bool GrainScheduler::tick() {
    samplesUntilNextGrain -= 1;
    if (samplesUntilNextGrain <= 0) {
        samplesUntilNextGrain = intervalSamples;
        return true;
    }

    return false;
}
