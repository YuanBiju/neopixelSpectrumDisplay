#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/timer.h"
#include "sdkconfig.h"

#include "mqtt_client.h"

#include "esp_system.h" //esp_init funtions esp_err_t 
#include "esp_wifi.h" //esp_wifi_init functions and wifi operations
#include "esp_log.h" //for showing logs
#include "esp_event.h" //for wifi event
#include "nvs_flash.h" //non volatile storage
#include "lwip/err.h" //light weight ip packets error handling
#include "lwip/sys.h" //system applications for light weight ip apps

#include "gpioHAL/gpioHAL.h"

#define NUM_LEDS 60

uint32_t stripNums = 3;

typedef struct{
        uint8_t redValue;
        uint8_t greenValue;
        uint8_t blueValue;
}neopixelRGBValue_s;

typedef union{
      neopixelRGBValue_s RGBValue;
      uint32_t ui32RGBValue;  
}neoPixelRGBValue_u;

typedef struct{
        
        uint8_t rangeNum;

        uint8_t rangeUpperLimit;

        neopixelRGBValue_s rgbValue;

}range_define_s;

range_define_s rangeTable[NUM_LEDS] = {
    {0, 20, {255, 0, 0}},
    {1, 20, {0, 255, 0}},
    {2, 20, {0, 0, 255}},
};

static void mqtt_event_handler(esp_mqtt_event_handle_t event){ //here esp_mqtt_event_handle_t is a struct which receieves struct event from mqtt app start funtion
        esp_mqtt_client_handle_t client = event->client; //making obj client of struct esp_mqtt_client_handle_t and assigning it the receieved event client
        if(event->event_id == MQTT_EVENT_CONNECTED){
                printf("MQTT_EVENT_CONNECTED");
                esp_mqtt_client_subscribe(client,"your-topic",0); //in mqtt we require a topic to subscribe and client is from event client and 0 is quality of service it can be 1 or 2
                printf("sent subscribe successful" );
        }
        else if(event->event_id == MQTT_EVENT_DISCONNECTED)
        {
                printf("MQTT_EVENT_DISCONNECTED"); //if disconnected
        }
        else if(event->event_id == MQTT_EVENT_SUBSCRIBED)
        {
                printf("MQTT_EVENT_SUBSCRIBED");
        }
        else if(event->event_id == MQTT_EVENT_UNSUBSCRIBED) //when subscribed
        {
                printf("MQTT_EVENT_UNSUBSCRIBED");
        }
        else if(event->event_id == MQTT_EVENT_DATA)//when unsubscribed
        {
                char data[20];
                printf("\n");
                printf("MQTT_EVENT_DATA:");
                memcpy(data,event->data,10);
                printf(data);
        }
        else if(event->event_id == MQTT_EVENT_ERROR)//when any error
        {
                printf("MQTT_EVENT_ERROR");
        }
}

esp_mqtt_client_handle_t client;

static void mqtt_initialize(void)
{/*Depending on your website or cloud there could be more parameters in mqtt_cfg.*/
  const esp_mqtt_client_config_t mqtt_cfg={
    .uri="mqtt://192.168.1.6:1883", //Uniform Resource Identifier includes path,protocol
    .event_handle=mqtt_event_handler, //described above event handler
  };
  client=esp_mqtt_client_init(&mqtt_cfg); //sending struct as a parameter in init client function
  esp_mqtt_client_start(client); //starting the process
}



void delay(uint32_t usDelay){
        while(usDelay --);
}

const char *ssid = "BIJU MIHANA-2.4G";
const char *pass = "22552255";
int retry_num=0;
static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id,void *event_data){
        if(event_id == WIFI_EVENT_STA_START)
        {
        printf("WIFI CONNECTING....\n");
        }
        else if (event_id == WIFI_EVENT_STA_CONNECTED)
        {
        printf("WiFi CONNECTED\n");
        }
        else if (event_id == WIFI_EVENT_STA_DISCONNECTED)
        {
        printf("WiFi lost connection\n");
        if(retry_num<5){esp_wifi_connect();retry_num++;printf("Retrying to Connect...\n");}
        }
        else if (event_id == IP_EVENT_STA_GOT_IP)
        {
        printf("Wifi got IP...\n\n");
        }
}

void wifi_connection()
{
     //                          s1.4
    // 2 - Wi-Fi Configuration Phase
    esp_netif_init();
    esp_event_loop_create_default();     // event loop                    s1.2
    esp_netif_create_default_wifi_sta(); // WiFi station                      s1.3
    wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_initiation); //     
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL);
    wifi_config_t wifi_configuration = {
        .sta = {
            .ssid = "",
            .password = "",
            
           }
    
        };
    strcpy((char*)wifi_configuration.sta.ssid, ssid);
    strcpy((char*)wifi_configuration.sta.password, pass);    
    //esp_log_write(ESP_LOG_INFO, "Kconfig", "SSID=%s, PASS=%s", ssid, pass);
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_configuration);
    // 3 - Wi-Fi Start Phase
    esp_wifi_start();
    esp_wifi_set_mode(WIFI_MODE_STA);
    // 4- Wi-Fi Connect Phase
    esp_wifi_connect();
    printf( "wifi_init_softap finished. SSID:%s  password:%s",ssid,pass);
    
}

void app_main() {

        gpio_hal_init(E_GPIO_NEOPIXEL);

        nvs_flash_init(); //keeps stored important wifi configs like ssid and password also mqtt configs code will not work without it
        wifi_connection(); // connects to wifi

        while(1){
                vTaskDelay((1000)/portTICK_RATE_MS);
        }
}