#pragma once

#include <mutex>

/**
 * This class is essentially a container for all the state that makes up the
 * current state of audio synthesis like the DSP graph, notes in the sequencer,
 * and that kinda stuff yee
 */
class State {
    public:
        enum class ActionType {

        };

        class Action {
            public:
                // TODO: my eyes hurt but use a union here.

        };

        float interval;
        std::mutex lock;

        /**
         * Processes a message from a client, which may or may not modify
         * the state and will require some kind of acknowledgement message.
         * If the message did cause state to be modified then the lock will have
         * been used and also the bool in the returned pair will be true which
         * tells you that, and in which case the returned message should be
         * broadcast to all connected TCP clients.
         * @param msg is the client message to parse and action.
         * @return a string message to return to the client and a boolean
         *         specifying if this should also be broadcast to other clients.
         */
        std::pair<std::string, bool> process(char const *msg);
};