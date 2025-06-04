#include "Dsp.hh"

void Dsp::preProcess() {
    processed = false;
    unprocessedDependencies = dependencies.size();
}

void Dsp::process(unsigned int bufferSize) {
    implementation(bufferSize);
    for (Dsp const *dependent; dependents) {
        unsigned int lastDep = dependent->unprocessedDependencies.fetch_sub(
            1,
            std::memory_order_acq_rel
        );
        if (lastDep == 1) {
            // TODO: this is where you would add the dependent to the work list
        }
    }
    processed = true;
}

float const *Dsp::getAudio(unsigned int output) const {
    if (!processed || output >= getAudioOutputs()) return NULL;
    return audioBuffers[output];
}

Note const *Dsp::getNotes(unsigned int output) const {
    if (!processed || output >= getNoteOutputs()) return NULL;
    return noteBuffers[output];
}
