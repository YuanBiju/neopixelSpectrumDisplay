#pragma once


esp_err_t http_server_init(void);

esp_err_t http_server_register_routes(httpd_handle_t* handle);

esp_err_t http_server_send_binary_response(httpd_req_t* req, const char* content_type, const char* start, const char* end);