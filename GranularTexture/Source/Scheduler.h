class GrainScheduler {
public:
    GrainScheduler() = default;
    GrainScheduler(int samples);
    void reset(int samples);
    bool tick(int numSamples);

    void setInterval(int samples);
private:
    int samplesUntilNextGrain;
    int intervalSamples;
};
