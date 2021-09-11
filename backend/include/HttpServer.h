#ifndef BACKEND_HTTPSERVER_H
#define BACKEND_HTTPSERVER_H
#include "microhttpd.h"
#include <cstring>

class HttpServer {
public:
    HttpServer(int port);
    ~HttpServer ();
    bool start ();
private:
    static int
    client_connection_handler (void *cls, struct MHD_Connection *connection,
                               const char *url,
                               const char *method, const char *version,
                               const char *upload_data,
                               size_t *upload_data_size, void **con_cls);
    static void deallocate_connection (void *cls, struct MHD_Connection *connection,
                            void **con_cls,
                            enum MHD_RequestTerminationCode toe);
    int port = 8888;
    struct MHD_Daemon *daemon;
};
struct connection_info_struct
{
    int connectiontype;
    char *answerstring;
    struct MHD_PostProcessor *postprocessor;
};

#endif //BACKEND_HTTPSERVER_H
