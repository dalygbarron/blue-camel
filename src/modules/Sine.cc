#include "modules/Sine.hh"

void Sine::implementation(DspJobParams const &params) {
    for (int i = 0; i <params.bufferSize; i++)  {
        
    }
}

uint8_t Sine::getAudioInputs() const {
    return 0;
}

uint8_t Sine::getNoteInputs() const {
    return 0;
}

uint8_t Sine::getAudioOutputs() const {
    return 1;
}

uint8_t Sine::getNoteOutputs() const {
    return 0;
}