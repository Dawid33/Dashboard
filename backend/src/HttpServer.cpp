#include "HttpServer.h"
#include "microhttpd.h"
#include <cstring>
#include <iostream>
#include "cjson/cJSON.h"
#include <memory>

#define POSTBUFFERSIZE  512
#define MAXNAMESIZE     20
#define MAXANSWERSIZE   512

HttpServer::HttpServer(int port) : port(port) {}

HttpServer::~HttpServer() {
    MHD_stop_daemon (daemon);
}

bool HttpServer::start() {
    daemon = MHD_start_daemon (MHD_USE_THREAD_PER_CONNECTION,
                               port, NULL, NULL,
                               &HttpServer::client_connection_handler, NULL,
                               MHD_OPTION_NOTIFY_COMPLETED, &HttpServer::deallocate_connection,
                               NULL, MHD_OPTION_END);
    if (NULL == daemon) return false;
    return true;
}

int
HttpServer::client_connection_handler(void *cls, struct MHD_Connection *connection, const char *url, const char *method,
                                      const char *version, const char *upload_data, size_t *upload_data_size,
                                      void **con_cls) {
    if(*con_cls == NULL) {

        *con_cls = connection;
        return MHD_YES;
    }

    // Continue handling POST request.
    if (0 == strcmp(method, "POST")) {
        if (*upload_data_size != 0) {
            cJSON *json = cJSON_Parse(upload_data);
            char *string = cJSON_Print(json);
            std::cout << string << std::endl;
            cJSON_Delete(json);
            *upload_data_size = 0;
            return MHD_YES;
        } else {
            return MHD_NO;
        }
    }
    return MHD_NO;
}

/*
 * de-allocate a connection that has been terminated abruptly.
 */
void HttpServer::deallocate_connection(void *cls, struct MHD_Connection *connection, void **con_cls,
                                   enum MHD_RequestTerminationCode toe) {
    *con_cls = NULL;
}