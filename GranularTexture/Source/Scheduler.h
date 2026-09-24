class GrainScheduler {
public:
    GrainScheduler() = default;
    GrainScheduler(int samples);
    void reset(int samples);
    bool tick(int numSamples);
private:
    int samplesUntilNextGrain;
    int intervalSamples;
};
