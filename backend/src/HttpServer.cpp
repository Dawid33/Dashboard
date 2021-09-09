#include "HttpServer.h"
#include <microhttpd.h>
#include <cstring>
#include <iostream>
#include <memory>

#define POSTBUFFERSIZE  512
#define MAXNAMESIZE     20
#define MAXANSWERSIZE   512

HttpServer::HttpServer(int port) : port(port) {}

HttpServer::~HttpServer() {
    MHD_stop_daemon (daemon);
}

bool HttpServer::start() {
    daemon = MHD_start_daemon (MHD_USE_AUTO | MHD_USE_INTERNAL_POLLING_THREAD,
                               port, NULL, NULL,
                               &client_connection_handler, NULL,
                               MHD_OPTION_NOTIFY_COMPLETED, &HttpServer::connection_terminator,
                               NULL, MHD_OPTION_END);
    if (NULL == daemon) return false;
    return true;
}

MHD_Result
HttpServer::client_connection_handler(void *cls, struct MHD_Connection *connection, const char *url, const char *method,
                                      const char *version, const char *upload_data, size_t *upload_data_size,
                                      void **con_cls) {
}

int HttpServer::iterate_post(void *coninfo_cls, enum MHD_ValueKind kind, const char *key, const char *filename,
                             const char *content_type, const char *transfer_encoding, const char *data, uint64_t off,
                             size_t size) {
}

void HttpServer::connection_terminator(void *cls, struct MHD_Connection *connection, void **con_cls,
                                   enum MHD_RequestTerminationCode toe) {
}