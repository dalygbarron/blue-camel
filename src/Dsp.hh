#pragma once

#include <vector>
#include <stdint.h>
#include "Config.hh"
#include "Job.hh"
#include "Note.hh"

/**
 * A module that can receive input from multiple sources and generate output
 * somehow.
 */
class Dsp: public Job {
    public:
        /**
         * Represents a dependency on another Dsp Module.
         * Dependency is the one being depended upon.
         * audio is true if it's an audio depency, otherwise note.
         * from is the output of dependency to take data from.
         * to is the input of the consumer to send that data to.
         */
        class Dependency {
            public:
                Dsp const *dsp;
                bool audio;
                uint8_t output;
                uint8_t input;

                /**
                 * Basic constructor that just sets shit.
                 * @param dsp the dsp.
                 * @param audio true if audio dependency
                 * @param output where it comes from in dep.
                 * @param input where it goes in here.
                 */
                Dependency(
                    Dsp const *dsp,
                    bool audio,
                    uint8_t output,
                    uint8_t input
                );
        };

        /**
         * Params that are passed to all the dsp jobs.
         */
        class DspJobParams {
            public:
                unsigned long bufferSize;
                float const *inBuffer;
                float *outBuffer;
        };

        /**
         * Representation of a parameter that a DSP effect can have.
         */
        class Parameter {
            private:
                char const *name;
                char const *description;
            public:
                float value;
                float min;
                float max;
        };

    private:
        bool execute(void const *params) override;

        /**
         * This is the function where the actual algorithm is implemented.
         * @param params is the set of params taht are sent to them all.
         */
        virtual void implementation(DspJobParams const &params) = 0;

    protected:
        float **audioOutputs;
        Note **noteOutputs;
        std::vector<Dependency> dependencies;

    public:

        /**
         * Tells you how many audio inputs this module can take.
         * @return the number of audio inputs it can take.
         */
        virtual uint8_t getAudioInputs() const = 0;

        /**
         * Tells you how many note inputs this module can take.
         * @return the number of note inputs this module can take.
         */
        virtual uint8_t getNoteInputs() const = 0;

        /**
         * Tells you how many audio outputs this module can produce.
         * @return the number of audio outputs this module produces.
         */
        virtual uint8_t getAudioOutputs() const = 0;

        /**
         * Tells you how many note outputs this module can produce.
         * @return the number of note outputs this module can produce.
         */
        virtual uint8_t getNoteOutputs() const = 0;

        /**
         * Sends you a const pointer to the output buffer of this DSP effect if
         * the effect has been processed, if it has not yet then NULL will be
         * returned instead.
         * @param output is the output channel to get. If this DSP doesn't
         *        have a channel with that number then you get NULL.
         * @return a const pointer to it or null if it is not ready.
         */
        float const *getAudio(uint8_t output) const;

        /**
         * Sends you a const pointer to a note buffer of this DSP effect if
         * the effect has been processed, if it hasn't yet then NULL will be
         * returned instead.
         * @param output is which note output to get, if this is not valid you
         *        get NULL.
         * @return a pointer to the note buffer.
         */
        Note const *getNotes(uint8_t output) const;

        /**
         * Sets this DSP as dependent on the given DSP for audio and sets what
         * audio output of the DSP will be fed into what audio input of this
         * one.
         * @param dependency is the dsp to add as a dependency.
         * @param audio is whether it's audio or notes, true meaning audio.
         * @param source is the output number of the dsp to depend on.
         * @param input is the input number of this dsp to connect it to.
         */
        void addDependency(
            Dsp const *dependency,
            bool audio,
            uint8_t source,
            uint8_t input
        );
};
