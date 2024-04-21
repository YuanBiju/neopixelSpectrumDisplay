#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <sdkconfig.h>

#include <nvs_flash.h>

#include "gpioHAL/gpioHAL.h"
#include "neopixelLED/neopixelLED.h"
#include "wifi/wifi.h"

#include "tcp/tcp_server.h"

// static void mqtt_event_handler(esp_mqtt_event_handle_t event){ //here esp_mqtt_event_handle_t is a struct which receieves struct event from mqtt app start funtion
//         esp_mqtt_client_handle_t client = event->client; //making obj client of struct esp_mqtt_client_handle_t and assigning it the receieved event client
//         if(event->event_id == MQTT_EVENT_CONNECTED){
//                 printf("MQTT_EVENT_CONNECTED");
//                 esp_mqtt_client_subscribe(client,"your-topic",0); //in mqtt we require a topic to subscribe and client is from event client and 0 is quality of service it can be 1 or 2
//                 printf("sent subscribe successful" );
//         }
//         else if(event->event_id == MQTT_EVENT_DISCONNECTED)
//         {
//                 printf("MQTT_EVENT_DISCONNECTED"); //if disconnected
//         }
//         else if(event->event_id == MQTT_EVENT_SUBSCRIBED)
//         {
//                 printf("MQTT_EVENT_SUBSCRIBED");
//         }
//         else if(event->event_id == MQTT_EVENT_UNSUBSCRIBED) //when subscribed
//         {
//                 printf("MQTT_EVENT_UNSUBSCRIBED");
//         }
//         else if(event->event_id == MQTT_EVENT_DATA)//when unsubscribed
//         {
//                 char data[20];
//                 printf("\n");
//                 printf("MQTT_EVENT_DATA:");
//                 memcpy(data,event->data,10);
//                 printf(data);
//         }
//         else if(event->event_id == MQTT_EVENT_ERROR)//when any error
//         {
//                 printf("MQTT_EVENT_ERROR");
//         }
// }

// esp_mqtt_client_handle_t client;

// static void mqtt_initialize(void)
// {/*Depending on your website or cloud there could be more parameters in mqtt_cfg.*/
//   const esp_mqtt_client_config_t mqtt_cfg={
//     .uri="mqtt://192.168.1.6:1883", //Uniform Resource Identifier includes path,protocol
//     .event_handle=mqtt_event_handler, //described above event handler
//   };
//   client=esp_mqtt_client_init(&mqtt_cfg); //sending struct as a parameter in init client function
//   esp_mqtt_client_start(client); //starting the process
// }


void app_main() {

        gpio_hal_init(E_GPIO_NEOPIXEL);

        nvs_flash_init(); //keeps stored important wifi configs like ssid and password also mqtt configs code will not work without it
        wifi_init(); // connects to wifi

        neopixelLED_init();

        tcp_server_init();

        while(1){
                vTaskDelay((1000)/portTICK_PERIOD_MS);
        }
}