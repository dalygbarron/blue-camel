#include "Server.hh"

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
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        if (mg_match(hm->uri, mg_str("/api/time/get"), NULL)) {
            mg_http_reply(c, 200, "", "{%m:%lu}\n", MG_ESC("time"), time(NULL));
        } else if (mg_match(hm->uri, mg_str("/interval"), NULL)) {
        } else {
            mg_http_reply(
                c,
                500,
                "",
                "{%m:%m}\n",
                MG_ESC("error"),
                MG_ESC("Unsupported URI")
            ); 
        }
    }
}

Server::Server(State &state): state(state) {
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, "http://0.0.0.0:8000", &Server::callback, this);
}