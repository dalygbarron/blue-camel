#include "Dsp.hh"

Dsp::Dependency::Dependency(
    Dsp const *dsp,
    bool audio,
    uint8_t output,
    uint8_t input
):
    dsp(dsp),
    audio(audio),
    output(output),
    input(input)
{}

bool Dsp::execute(void const *params) {
    // wait for all dependencies to be completed.
    while (true) {
        bool escape = true;
        for (Dependency &dep: dependencies) {
            // if (dep.dsp->getIterations() <= getIterations()) {
            //     escape = false;
            //     continue;
            // }
        }
        if (escape) break;
    }
    DspJobParams const &dspParams = *((DspJobParams *)params);
    implementation(dspParams);
    return false;
}

float const *Dsp::getAudio(uint8_t output) const {
    if (output >= getAudioOutputs()) return NULL;
    return audioOutputs[output];
}

Note const *Dsp::getNotes(uint8_t output) const {
    if (output >= getNoteOutputs()) return NULL;
    return noteOutputs[output];
}

void Dsp::addDependency(
    Dsp const *dependency,
    bool audio,
    uint8_t output,
    uint8_t input
) {
    // TODO: possibly a good time to validate that we are not creating a cycle?
    // Eh, we might as well do the whole graph and calculate numbers of
    // dependencies at the same time so we can just add it where we call this
    // or something idk.
    dependencies.emplace_back(dependency, audio, output, input);
}