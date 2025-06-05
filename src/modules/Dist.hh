#pragma once

#include "Dsp.hh"

/**
 * Just a nice distortion effect.
 */
class Dist: public Dsp {
    private:
        Parameter gain;

    protected:
        void implementation(unsigned int bufferSize) override;

    public:
        Dist(float gain = 1.0f, float threshold = 0.5f);

        void setGain(float gain);
        void setThreshold(float threshold);
};