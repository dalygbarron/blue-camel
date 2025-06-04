#pragma once

#include "Config.hh"

/**
 * A module that can receive input from multiple sources and generate output
 * somehow.
 */
class Dsp {
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
                Dsp const *dependency;
                bool audio;
                unsigned int from;
                unsigned int to;
        };

    private:
        std::atomic<unsigned int> unprocessedDependencies {0}
        std::vector<Dsp const *> dependents;
        std::vector<Dependency> dependencies;
        bool processed = false;

        /**
         * Actual DSP implementation.
         * @param bufferSize is the number of samples to update and it won't
         *        exceed Config::MAX_BUFFER_SIZE.
         */
        virtual void implementation(unsigned int bufferSize);

    protected:
        float **audioOutputs;
        Note **noteOutputs;

    public:
        /**
         * Call this before every process call to reset dsp modules to their
         * pre processed state.
         */
        void preProcess();

        /**
         * Public wrapper around the DSP algorithm implementation that gets
         * generic stuff set up.
         * @param bufferSize is the amount of samples to process and I promise
         *        it will not be greater than Config::MAX_BUFFER_SIZE.
         */
        void process(unsigned int bufferSize);

        /**
         * Tells you how many audio inputs this module can take.
         * @return the number of audio inputs it can take.
         */
        virtual unsigned int getAudioInputs() const = 0;

        /**
         * Tells you how many note inputs this module can take.
         * @return the number of note inputs this module can take.
         */
        virtual unsigned int getNoteInputs() const = 0;

        /**
         * Tells you how many audio outputs this module can produce.
         * @return the number of audio outputs this module produces.
         */
        virtual unsigned int getAudioOutputs() const = 0;

        /**
         * Tells you how many note outputs this module can produce.
         * @return the number of note outputs this module can produce.
         */
        virtual unsigned int getNoteOutputs() const = 0;

        /**
         * Sends you a const pointer to the output buffer of this DSP effect if
         * the effect has been processed, if it has not yet then NULL will be
         * returned instead.
         * @param output is the output channel to get. If this DSP doesn't
         *        have a channel with that number then you get NULL.
         * @return a const pointer to it or null if it is not ready.
         */
        float const *getAudio(unsigned int output) const;

        /**
         * Sends you a const pointer to a note buffer of this DSP effect if
         * the effect has been processed, if it hasn't yet then NULL will be
         * returned instead.
         * @param output is which note output to get, if this is not valid you
         *        get NULL.
         * @return a pointer to the note buffer.
         */
        Note const *getNotes(unsigned int output) const;


        void addNoteDependency(Dsp *dependency, unsigned int source, unsigned int input);

        /**
         * Sets this DSP as dependent on the given DSP for audio and sets what
         * audio output of the DSP will be fed into what audio input of this
         * one.
         * @param dependency is the dsp to add as a dependency.
         * @param source is the output number of the dsp to depend on.
         * @param input is the input number of this dsp to connect it to.
         */
        void addAudioDependency(Dsp *dependency, unsigned int source, unsigned int input);
};
