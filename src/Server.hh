#pragma once

#include "mongoose.h"
#include "Job.hh"
#include "State.hh"

/**
 * A job whose purpose is to handle http events. In order to avoid the need to
 * lock and to make undoing easier, this does not directly modify the state of
 * the synthesis engine but rather creates a todo list that will be completed
 * synchronously after the next block finishes processing.
 */
class Server: public Job {
    private:
        struct mg_mgr mgr;
        State &state;

        void execute(void const *params) override;

        /**
         * The callback that is called when the server processes a request.
         * @param c is the connection it came from.
         * @param event is the event type.
         * @param eventData references relevant data whose type is known by the
         *        type of event.
         * @param userData is a reference to the server instance itself.
         */
        static void callback(
            struct mg_connection *c,
            int event,
            void *eventData
        );

    public:
        /**
         * Sets up the server and stores the state
         * @param state the audio engine state.
         */
        Server(State &state);
};