#pragma once

#include "esp_err.h"
#include <stdbool.h>

struct tcp_client_info_t{
    volatile int client_socket_id;
    volatile bool client_connected;
};

esp_err_t tcp_server_init(void);

void tcp_server_get_port(uint16_t *);


