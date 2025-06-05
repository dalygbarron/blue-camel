#pragma once

#include "Dsp.hh"

/**
 * A very basic since oscillator just to get things going.
 */
class Sine: public Dsp {
    private:
        float phase;

        void implementation(DspJobParams const &params) override;

    public:
        uint8_t getAudioInputs() const override;

        uint8_t getNoteInputs() const override;

        uint8_t getAudioOutputs() const override;

        uint8_t getNoteOutputs() const override;

};