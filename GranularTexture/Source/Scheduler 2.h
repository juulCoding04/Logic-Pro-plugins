class Scheduler {
public:
    bool tick();

    void setSamplesUntilNextGrain(int samples) { samplesUntilNextGrain = samples; }
private:
    int samplesUntilNextGrain = 0;
};
