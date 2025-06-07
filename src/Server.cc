#include "Server.hh"
#include "Util.hh"

void Server::execute(void const *params) {
    mg_mgr_poll(&mgr, 200);
    enqueue(NULL);
}

void Server::callback(
    struct mg_connection *c,
    int ev,
    void *ev_data
) {
    Server *self = (Server *)c->fn_data;
    if (ev == MG_EV_ACCEPT) {
        self->connections.push_back(c);
    } else if (ev == MG_EV_CLOSE) {
        self->connections.erase(std::remove(
            self->connections.begin(),
            self->connections.end(),
            c
        ), self->connections.end());
    } else if (ev == MG_EV_READ) {
        std::pair<std::string, bool> result = self->state.process(c->recv.buf);
        if (result.second) self->broadcast(result.first.c_str());
        else mg_send(c, result.first.c_str(), result.first.length());
    }
}

Server::Server(State &state): state(state) {
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, "http://0.0.0.0:8000", &Server::callback, this);
}

void Server::broadcast(char const *msg) {
    for (mg_connection *c: connections) {
        mg_send(c, msg, strlen(msg));
    }
}