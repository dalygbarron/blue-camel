#pragma once

#include "Dsp.hh"

/**
 * This module is a special one whose sole purpose is to transfer it's inputs to
 * the system output buffer.
 */
class Out: public Dsp {
    private:
        void implementation(DspJobParams const &params);

    public:
        uint8_t getAudioInputs() const;

        uint8_t getNoteInputs() const;

        uint8_t getAudioOutputs() const;

        uint8_t getNoteOutputs() const;

};