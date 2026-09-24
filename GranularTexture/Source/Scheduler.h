class GrainScheduler {
public:
    GrainScheduler() = default;
    GrainScheduler(int samples);
    void reset(int samples);
    bool tick();
private:
    int samplesUntilNextGrain;
    int intervalSamples;
};
