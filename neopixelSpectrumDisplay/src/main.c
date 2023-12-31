#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/timer.h"
#include "sdkconfig.h"

#define NEOPIXEL_GPIO 4

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

range_define_s rangeTable[NUM_LEDS];


void delay(uint32_t usDelay){
        while(usDelay --);
}

void set_led_colour(uint8_t redValue, uint8_t greenValue, uint8_t blueValue){

        neoPixelRGBValue_u uRGBValue = {0};

        neopixelRGBValue_s sRGBValue = {.redValue = redValue, .greenValue = greenValue, .blueValue = blueValue};

        uRGBValue.RGBValue = sRGBValue;

        uint16_t count = 24;

        // for(uint16_t ledNum = 0; ledNum<NUM_LEDS)
        while(count--){
                
                if(uRGBValue.ui32RGBValue&(1<<(24-count))){
                        gpio_set_level(NEOPIXEL_GPIO, 1);
                        for(int i = 0;i<10 ;i++);
                        gpio_set_level(NEOPIXEL_GPIO, 0);
                }
                else{
                        gpio_set_level(NEOPIXEL_GPIO, 1);
                        gpio_set_level(NEOPIXEL_GPIO, 0);
                }
        }
}

void set_strip_colour(){

        neoPixelRGBValue_u uRGBValue = {0};

        neopixelRGBValue_s sRGBValue = {.redValue = redValue, .greenValue = greenValue, .blueValue = blueValue};

        uRGBValue.RGBValue = sRGBValue;

        uint16_t count = 24;

        // for(uint16_t ledNum = 0; ledNum<NUM_LEDS)
        while(count--){
                
                if(uRGBValue.ui32RGBValue&(1<<(24-count))){
                        gpio_set_level(NEOPIXEL_GPIO, 1);
                        for(int i = 0;i<10 ;i++);
                        gpio_set_level(NEOPIXEL_GPIO, 0);
                }
                else{
                        gpio_set_level(NEOPIXEL_GPIO, 1);
                        gpio_set_level(NEOPIXEL_GPIO, 0);
                }
        }
}

void hsv_to_rgb(uint8_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g, uint8_t *b) {
    uint16_t sector = h / 43; // 0 to 5
    uint8_t remainder = (h - (sector * 43)) * 6; // 0 to 252

    uint8_t p = (v * (255 - s)) >> 8;
    uint8_t q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    uint8_t t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

    switch (sector) {
        case 0: *r = v; *g = t; *b = p; break;
        case 1: *r = q; *g = v; *b = p; break;
        case 2: *r = p; *g = v; *b = t; break;
        case 3: *r = p; *g = q; *b = v; break;
        case 4: *r = t; *g = p; *b = v; break;
        default: *r = v; *g = p; *b = q; break;
    }
}
void neopixel_animation() {
    uint8_t hue = 0;

    while (1) {
        for (int i = 0; i < NUM_LEDS; i++) {
            uint8_t red, green, blue;

            // Generate color based on hue
            hsv_to_rgb(hue, 255, 255, &red, &green, &blue);

            set_led_colour(red, green, blue);
            vTaskDelay(5 / portTICK_PERIOD_MS);  // Adjust the delay for the animation speed
        }
        hue += 1;  // Increment hue for the next LED
    }
}
void app_main() {

        /**NEOPIXEL GPIO*/
        gpio_pad_select_gpio(NEOPIXEL_GPIO);
        /* Set the GPIO as a push/pull output */
        gpio_set_direction(NEOPIXEL_GPIO, GPIO_MODE_OUTPUT);

        rangeTable[0] = {0,20,{255,0,0}};
        rangeTable[1] = {1,20,{0,255,0}};
        rangeTable[2] = {2,20,{0,0,255}};

        while(1){

        }
}