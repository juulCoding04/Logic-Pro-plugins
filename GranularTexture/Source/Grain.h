#include <math.h>

class Grain {
public:
    Grain() = default;

    // getters/setters
    int getStartSample() { return startSample; }
    int getLengthSamples() { return lengthSamples; }
    int getCurrentSample() { return currentSample; }
    int getProgress() { return progress; }
    bool isIdle() { return !active; }

    void start(int newStartSample, int newLengthSamples);
    void advance(int samplesRead, int circularBufferSize);
    float getEnvValue();

private:
    int startSample = 0;
    int lengthSamples = 0;
    int currentSample = 0;
    int progress = 0;
    bool active = false;
};
