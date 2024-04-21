#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#include <esp_check.h>
#include <esp_log.h>

#include <lwip/err.h>
#include <lwip/sockets.h>
#include <lwip/sys.h>
#include <lwip/netdb.h>

#include "tcp/tcp_server.h"
#include "system/common.h"

#define TCP_SERVER_TASK_PRIORITY   10
#define TCP_SERVER_TASK_CORE       0
#define TCP_CLIENT_BUFFER_SIZE     25

// Log message tag
static const char* TAG = "tcp_server";
// Number of clients connected to the tcp server
static int connected_clients_count = 0;
// Maximum clients that can be connected to the server
static int tcp_server_port = DEFAULT_TCP_SERVER_PORT;
// TCP server port number
static int maximum_client_count = 3;
// Look up table to store tcp client info
static struct tcp_client_info_t tcp_server_client_LUT[TCP_CLIENT_BUFFER_SIZE] = {0};

/**
 * @brief   Task to send data to all connected clients.
 * @param   params unused
 */
static void tcp_server_send_data_task(void* params){
    ssize_t return_value;
    while(1){
        vTaskDelay(1);
    }
    //Delete the task.
    vTaskDelete(NULL);
}

/**
 * @brief   TCP server setup and client connection task.
 */
static void tcp_server_task(void *pvParameters){
    struct sockaddr_in server_address, client_address;
    int listen_socket, client_socket;
    socklen_t address_length = sizeof(struct sockaddr_in);

    listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_socket < 0) {
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
        vTaskDelete(NULL);
        return;
    }

    ESP_LOGI(TAG, "Socket created");

    server_address.sin_addr.s_addr = htonl(INADDR_ANY);//returns a 32-bit number in the network byte order used in TCP/IP networks.
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(tcp_server_port);//returns a 16-bit number in network byte order used in TCP/IP networks.

    if (bind(listen_socket, (struct sockaddr*)&server_address, sizeof(server_address)) != 0) {
        ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
        close(listen_socket);
        vTaskDelete(NULL);
        return;
    }

    ESP_LOGI(TAG, "Socket binding done");

    if (listen(listen_socket, maximum_client_count) != 0) {
        ESP_LOGE(TAG, "Error occurred during listen: errno %d", errno);
        close(listen_socket);
        vTaskDelete(NULL);
        return;
    }

    ESP_LOGI(TAG, "Socket started listening for connections on port %d", tcp_server_port);

    //create task to check the queue and send data over tcp
    // xTaskCreatePinnedToCore(tcp_server_send_data_task, "tcp_server_send_data_task", DEFAULT_TASK_STACK_SIZE, NULL, TCP_SERVER_TASK_PRIORITY, NULL, TCP_SERVER_TASK_CORE);

    while (1) {
            ESP_LOGI(TAG, "Waiting for client to connect...");
            client_socket = accept(listen_socket, (struct sockaddr*)&client_address, &address_length);
            if (client_socket < 0){
                ESP_LOGE(TAG, "Unable to accept connection: errno %d", errno);
                break;
            }

            ESP_LOGI(TAG, "Client %d connected: %s:%d", client_socket, inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

            // Check if the maximum number of clients has been reached
            if (connected_clients_count < maximum_client_count) {
                // Add the client to the data structure
                for(int client_index = 0;client_index < maximum_client_count;client_index++){
                    if(false == tcp_server_client_LUT[client_index].client_connected){
                        tcp_server_client_LUT[client_index].client_socket_id = client_socket;
                        tcp_server_client_LUT[client_index].client_connected = true;
                        break;
                    }
                }
                connected_clients_count++;

                //if client is connected turn on led
                // ESP_ERROR_CHECK(ui_led_set(UI_SOLID));

            } else {
                ESP_LOGW(TAG, "Client connection exceeds limit, closing connection\n");
                // Reject the connection if the maximum number of clients has been reached
                close(client_socket);
            }
    }
    //Close the tcp listen socket
    close(listen_socket);
    vTaskDelete(NULL);
}

/**
 * @brief   Initialize TCP server.
 * @retval  Returns ESP_OK if initialized successfully else returns ESP_FAIL.
 */
esp_err_t tcp_server_init(void){
    //Initialize the client structure instances.
    for(int client_index = 0;client_index < maximum_client_count;client_index++){
        tcp_server_client_LUT[client_index].client_connected = false;
    }
    //Create task to create TCP server and handle clients.
    xTaskCreatePinnedToCore(tcp_server_task, "tcp_server_task", DEFAULT_TASK_STACK_SIZE, NULL, TCP_SERVER_TASK_PRIORITY, NULL, TCP_SERVER_TASK_CORE);
    return ESP_OK;
}

/**
 * @brief   Return TCP server port number.
 * @param   ptcp_server_port Pointer to buffer to store tcp server port number.
 */
void tcp_server_get_port(uint16_t *tcp_server_port_buffer){
    *tcp_server_port_buffer = tcp_server_port;
}