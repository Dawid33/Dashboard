#ifndef BACKEND_HTTPSERVER_H
#define BACKEND_HTTPSERVER_H
#include <microhttpd.h>
#include <cstring>

class HttpServer {
public:
    HttpServer(int port);
    ~HttpServer();
    bool start();
private:
    static MHD_Result client_connection_handler (void *cls, struct MHD_Connection *connection,
                                     const char *url,
                                     const char *method, const char *version,
                                     const char *upload_data,
                                     size_t *upload_data_size, void **con_cls);
    int port = 8888;
    struct MHD_Daemon *daemon;
};


#endif //BACKEND_HTTPSERVER_H
