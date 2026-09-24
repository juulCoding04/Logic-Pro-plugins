class GrainScheduler {
public:
    GrainScheduler(int samples);
    bool tick();
private:
    int samplesUntilNextGrain;
    int intervalSamples;
};
