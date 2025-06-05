#include "modules/Out.hh"

void Out::implementation(DspJobParams const &params) {
    bool first = true;
    for (Dependency &dep: dependencies) {
        float const *source = dep.dsp->getAudio(dep.output);
        for (int i = 0; i < params.bufferSize; i++) {
            if (first) params.outBuffer[i] = 0;
            params.outBuffer[i] += source[i];
        }
        first = false;
    }
}

uint8_t Out::getAudioInputs() const {
    return 1;
}

uint8_t Out::getNoteInputs() const {
    return 0;
}

uint8_t Out::getAudioOutputs() const {
    return 0;
}

uint8_t Out::getNoteOutputs() const {
    return 0;
}