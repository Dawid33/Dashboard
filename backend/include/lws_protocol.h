#ifndef BACKEND_LWS_PROTOCOL_H
#define BACKEND_LWS_PROTOCOL_H
#include <stdlib.h>
#include <libwebsockets.h>

#define RING_DEPTH 4096

/* one of these created for each message */

struct msg {
    void *payload; /* is malloc'd */
    size_t len;
    char binary;
    char first;
    char final;
};

struct per_session_data__minimal_server_echo {
    struct lws_ring *ring;
    uint32_t msglen;
    uint32_t tail;
    uint8_t completed:1;
    uint8_t flow_controlled:1;
    uint8_t write_consume_pending:1;
};

struct vhd_minimal_server_echo {
    struct lws_context *context;
    struct lws_vhost *vhost;

    int *interrupted;
    int *options;
};

int
callback_minimal_server_echo(struct lws *wsi, enum lws_callback_reasons reason,
                             void *user, void *in, size_t len);

#define LWS_PLUGIN_PROTOCOL_MINIMAL_SERVER_ECHO \
	{ \
		"lws-minimal-server-echo", \
		callback_minimal_server_echo, \
		sizeof(struct per_session_data__minimal_server_echo), \
		1024, \
		0, NULL, 0 \
	}

#endif //BACKEND_LWS_PROTOCOL_H
