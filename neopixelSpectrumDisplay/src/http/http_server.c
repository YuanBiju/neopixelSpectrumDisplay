#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <esp_log.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include "esp_netif.h"
#include "esp_tls_crypto.h"
#include <esp_http_server.h>
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_tls.h"
#include "esp_check.h"

#include "http/http_server.h"

static const char* TAG = "http_server";

static httpd_handle_t http_server_start_webserver(void);

esp_err_t http_server_init(void){
    http_server_start_webserver();
    return ESP_OK;
}

esp_err_t http_server_send_binary_response(httpd_req_t* req, const char* content_type, const char* start, const char* end) {
    if (start == NULL || end == NULL || end < start) {
        return ESP_ERR_INVALID_ARG;
    }

    const uint32_t length = end - start;

    if (content_type != NULL) {
        ESP_RETURN_ON_ERROR(httpd_resp_set_type(req, content_type), TAG, "failed to set content_type");
    }

    ESP_RETURN_ON_ERROR(httpd_resp_send(req, start, length), TAG, "failed to send http response");

    return ESP_OK;
}

/* Function for starting the webserver */
static httpd_handle_t http_server_start_webserver(void){

    /* Generate default configuration */
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    /* Empty handle to esp_http_server */
    httpd_handle_t server = NULL;

    /* Start the httpd server */
    if (httpd_start(&server, &config) == ESP_OK){
        http_server_register_routes(&server);
    }
    /* If server failed to start, handle will be NULL */
    return server;
}

/* Function for stopping the webserver */
void http_server_stop_webserver(httpd_handle_t server){
    if (server) {
        /* Stop the httpd server */
        httpd_stop(server);
    }
}