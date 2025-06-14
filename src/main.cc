#include <portaudio.h>
#include <cmath>
#include <iostream>
#include "Job.hh"
#include "State.hh"
#include "Server.hh"
#include "Util.hh"

float const SAMPLEL_RATE = 44100.0f;
float const FREQUENCY = 440.0f; // A4 note
unsigned int const BUFFER_SIZE = 64;

// Data structure to pass to the callback
struct SineData {
    float phaseL = 0;
    float phaseR = 0;
    float phaseIncrementL = 0;
    float phaseIncrementR = 0;
    State *state;
    Server *server;
};

// Audio callback function
static int paCallback(
    const void *inBuffer,
    void *outBuffer,
    unsigned long size,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData
) {

    float const *in = (float const *)inBuffer;
    float *out = (float *)outBuffer;
    SineData *data = (SineData*)userData;

    // TODO: first thing we need to do

    std::lock_guard<std::mutex> lock(data->state->lock);
    for(unsigned int i = 0; i < size; i++) {
        *out++ = (sin(data->phaseL) > 0) ? 1 : -1;
        *out++ = (sin(data->phaseR) > 0) ? 1 : -1;
        data->phaseL += data->phaseIncrementL;
        data->phaseR += data->phaseIncrementR;
        // Wrap phase to keep it in [0, 2*PI) range to avoid precision loss
        data->phaseL = fmod(data->phaseL, 2.0f * (float)M_PI);
        data->phaseR = fmod(data->phaseR, 2.0f * (float)M_PI);
    }
    //data->server->broadcast(uuid.c_str());
    return paContinue;
}

PaStream *initPortAudio(PaStreamCallback callback, void *userData) {
    PaStream *stream;
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return NULL;
    }
    PaStreamParameters outputParameters;
    outputParameters.device = Pa_GetDefaultOutputDevice();
    if(outputParameters.device == paNoDevice) {
        std::cerr << "Error: No default output device." << std::endl;
        Pa_Terminate();
        return NULL;
    }
    outputParameters.channelCount = 2;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;
    err = Pa_OpenStream(
        &stream,
        NULL,
        &outputParameters,
        SAMPLEL_RATE,
        BUFFER_SIZE,
        paClipOff, // We won't output out of range samples so don't bother clipping them
        callback,
        userData
    );
    if(err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        Pa_Terminate();
        return NULL;
    }
    err = Pa_StartStream(stream);
    if(err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        Pa_CloseStream(stream);
        Pa_Terminate();
        return NULL;
    }
    return stream;
}

int main(int argc, char const **argv) {
    State state;
    Server server(state);
    Job::List jobs(0);
    SineData data {
        0,
        0,
        (2.0f * (float)M_PI * FREQUENCY) / SAMPLEL_RATE,
        (2.0f * (float)M_PI * (FREQUENCY + 0.5f)) / SAMPLEL_RATE,
        &state,
        &server
    };
    PaStream *stream = initPortAudio(paCallback, &data);
    if (stream == NULL) return 1;
    jobs.enqueue(&server, NULL);
    std::cout << "Playing sine wave. Press ENTER to stop." << std::endl;
    std::cin.get();
    PaError err = Pa_StopStream(stream);
    if(err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    }
    err = Pa_CloseStream(stream);
    if(err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
    }
    Pa_Terminate();
    return 0;
}
