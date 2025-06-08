#pragma once

#include <vector>
#include <mongoose.h>
#include "Job.hh"
#include "State.hh"

/**
 * A job whose purpose is to handle tcp messages and connections and also send
 * messages to clients if you want.
 */
class Server: public Job {
    private:
        struct mg_mgr mgr;
        State &state;
        std::vector<mg_connection *> connections;
        static unsigned int const MAX_MESSAGE_SIZE = 1024;

        bool execute(void const *params) override;

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

        /**
         * Broadcast a message to all connected TCP clients.
         * @param msg is the message to send to them all.
         */
        void broadcast(char const *msg);
};