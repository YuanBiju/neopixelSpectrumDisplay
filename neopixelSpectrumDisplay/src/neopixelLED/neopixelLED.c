/**
 * ****************************************
 * @file    neopixelLED.c
 * @author  Yuan Nevin Biju
 * @brief   This file contains neopixelLED interface functions.
 * 
 * @copyright Copyright (c) 2023
 * ********************/

/* ****************************************
 * Includes
 * ********************/
#include "neopixelLED/neopixelLED.h"

/* ****************************************
 * Defines
 * ********************/

/* ****************************************
 * Data
 * ********************/

/* ****************************************
 * Function Definitions
 * ********************/
void set_led_colour(uint8_t redValue, uint8_t greenValue, uint8_t blueValue){

        neoPixelRGBValue_u uRGBValue = {0};

        neopixelRGBValue_s sRGBValue = {.redValue = redValue, .greenValue = greenValue, .blueValue = blueValue};

        uRGBValue.RGBValue = sRGBValue;

        uint16_t count = 24;

        // for(uint16_t ledNum = 0; ledNum<NUM_LEDS)
        while(count--){
                
                if(uRGBValue.ui32RGBValue&(1<<(24-count))){
                        gpio_hal_set(NEOPIXEL_GPIO);
                        for(int i = 0;i<10 ;i++);
                        gpio_hal_reset(NEOPIXEL_GPIO);
                }
                else{
                        gpio_hal_set(NEOPIXEL_GPIO);
                        gpio_hal_reset(NEOPIXEL_GPIO);
                }
        }
}

// void set_strip_colour(){

//         neoPixelRGBValue_u uRGBValue = {0};

//         neopixelRGBValue_s sRGBValue = {.redValue = redValue, .greenValue = greenValue, .blueValue = blueValue};

//         uRGBValue.RGBValue = sRGBValue;

//         uint16_t count = 24;

//         // for(uint16_t ledNum = 0; ledNum<NUM_LEDS)
//         while(count--){
                
//                 if(uRGBValue.ui32RGBValue&(1<<(24-count))){
//                         gpio_set_level(NEOPIXEL_GPIO, 1);
//                         for(int i = 0;i<10 ;i++);
//                         gpio_set_level(NEOPIXEL_GPIO, 0);
//                 }
//                 else{
//                         gpio_set_level(NEOPIXEL_GPIO, 1);
//                         gpio_set_level(NEOPIXEL_GPIO, 0);
//                 }
//         }
// }

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