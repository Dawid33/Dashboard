#include "HttpServer.h"
#include <microhttpd.h>
#include <cstring>

MHD_Result HttpServer::client_connection_handler(void *cls, struct MHD_Connection *connection, const char *url, const char *method,
                                      const char *version, const char *upload_data, size_t *upload_data_size,
                                      void **con_cls) {
    const char *page = "<html><body>Hello, browser!</body></html>";
    struct MHD_Response *response;
    int ret;
    response = MHD_create_response_from_buffer (strlen(page),
                                                (void*) page, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
    MHD_destroy_response (response);
    return MHD_Result(ret);
}

HttpServer::HttpServer(int port) : port(port) {}

bool HttpServer::start() {
    daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, port, NULL, NULL,
                              &client_connection_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon) return false;
    return true;
}

HttpServer::~HttpServer() {
    MHD_stop_daemon (daemon);
}
