#include <sys/socket.h>
#include <esp_check.h>
#include <esp_wifi.h>
#include <esp_http_server.h>

#include "http/http_server.h"

static const char* TAG = "http_routes";

httpd_handle_t s_httpd_handle;

extern const char g_index_start[] asm("_binary_index_html_gz_start");
extern const char g_index_end[] asm("_binary_index_html_gz_end");

extern const char g_icon_start[] asm("_binary_icon_png_start");
extern const char g_icon_end[] asm("_binary_icon_png_end");

static esp_err_t http_route_index_html_get(httpd_req_t* req);
static esp_err_t http_route_icon_get(httpd_req_t* r);


const httpd_uri_t http_routes[] = {{
    .uri      = "/",
    .method   = HTTP_GET,
    .handler  = http_route_index_html_get,
    .user_ctx = NULL
},{
    .uri      = "/icon.png",
    .method   = HTTP_GET,
    .handler  = http_route_icon_get,
    .user_ctx = NULL   
}};

esp_err_t http_server_register_routes(httpd_handle_t* handle) {
    const size_t route_count = sizeof(http_routes) / sizeof(httpd_uri_t);

    s_httpd_handle = handle;

    for (int route_index = 0; route_index < route_count; route_index++) {
        const httpd_uri_t* route = &http_routes[route_index];

        ESP_LOGI(TAG, "registering route[%d]: %s", route_index, route->uri);

        ESP_RETURN_ON_ERROR(httpd_register_uri_handler(*handle, route), TAG, "failed to register route '%s'", route->uri);
    }

    return ESP_OK;
}

static esp_err_t http_route_index_html_get(httpd_req_t* req) {
    HTTP_RETURN_ON_ERROR(req, http_assert_in_header(req, "Accept-Encoding", "gzip"), TAG, "browser does not accept gzip encoding");
    HTTP_RETURN_ON_ERROR(req, httpd_resp_set_hdr(req, "Content-Encoding", "gzip"), TAG, "failed to set header");

    return http_server_send_binary_response(req, "text/html", g_index_start, g_index_end);
}

static esp_err_t http_route_icon_get(httpd_req_t* r) {
    return http_server_send_binary_response(r, "image/png", g_icon_start, g_icon_end);
}