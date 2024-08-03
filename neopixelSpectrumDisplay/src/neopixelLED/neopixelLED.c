/**
 * ****************************************
 * @file    neopixelLED.c
 * @author  Yuan Nevin Biju
 * @brief   This file contains neopixelLED interface functions.
 * 
 * @copyright Copyright (c) 2023
 * ********************/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "gpioHAL/gpioHAL.h"

#include "neopixelLED/neopixelLED.h"

#define NEOPIXEL_T0H_LOOP_COUNT     7
#define NEOPIXEL_TOTAL_BIT_COUNT    24

led_strip_s rangeTable[NUM_LEDS] = {
    {0, 20, {255, 0, 0}},
    {0, 20, {0, 255, 0}},
    {0, 20, {0, 0, 255}},
    {INVALID_STRIP_ID, 20, {0, 0, 255}},
};

uint32_t stripNums = 3;

neoPixelRGBValue_u uRGBValue = {0};

neopixelRGBValue_s sRGBValue;

static void hsv_to_rgb(uint8_t, uint8_t, uint8_t, uint8_t *, uint8_t *, uint8_t *);
static void neopixelLED_animation(void* params);
static void neopixelLED_set_led_colour(uint8_t, uint8_t, uint8_t);

void neopixelLED_init(){
    xTaskCreate(neopixelLED_animation, "neopixel_animation", 1024, NULL, tskIDLE_PRIORITY, NULL);
}

void neopixelLED_setStripColor(){

}

void neopixelLED_applyStripColor(){

}

static void neopixelLED_animation(void* params){
    while (1) {
        for(uint8_t ledGroupIndex = 0; ledGroupIndex < NUM_LEDS; ledGroupIndex++){
            if(INVALID_STRIP_ID == rangeTable[ledGroupIndex].LedStripId){
                break;
            }
            for(uint8_t ledCount = 0; ledCount < rangeTable[ledGroupIndex].stripLedCount; ledCount++){
                neopixelLED_set_led_colour(rangeTable[ledGroupIndex].rgbValue.redValue,rangeTable[ledGroupIndex].rgbValue.greenValue,rangeTable[ledGroupIndex].rgbValue.blueValue);
            }
        }
        for(uint8_t ledGroupIndex = 0; ledGroupIndex < NUM_LEDS; ledGroupIndex++){
                rangeTable[ledGroupIndex].
                break;
            }
            for(uint8_t ledCount = 0; ledCount < rangeTable[ledGroupIndex].stripLedCount; ledCount++){
                neopixelLED_set_led_colour(rangeTable[ledGroupIndex].rgbValue.redValue,rangeTable[ledGroupIndex].rgbValue.greenValue,rangeTable[ledGroupIndex].rgbValue.blueValue);
            }
        }
        vTaskDelay(1000);  // Adjust the delay for the animation speed
    }
}

void neopixelLED_set_led_colour(uint8_t redValue, uint8_t greenValue, uint8_t blueValue){
    sRGBValue.redValue = redValue;
    sRGBValue.greenValue = greenValue;
    sRGBValue.blueValue = blueValue;

    uRGBValue.RGBValue = sRGBValue;

    uint16_t count = NEOPIXEL_TOTAL_BIT_COUNT;
        
    while(count--){
            
            if(uRGBValue.ui32RGBValue&(1<<(NEOPIXEL_TOTAL_BIT_COUNT-count))){
                    gpio_hal_set(E_GPIO_NEOPIXEL);
                    for(int i = 0;i < NEOPIXEL_T0H_LOOP_COUNT ;i++);
                    gpio_hal_reset(E_GPIO_NEOPIXEL);
            }
            else{
                    gpio_hal_set(E_GPIO_NEOPIXEL);
                    gpio_hal_reset(E_GPIO_NEOPIXEL);
            }
    }
}

// void set_strip_colour(){

// }

static void hsv_to_rgb(uint8_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g, uint8_t *b){
    uint16_t sector = h / 43; // 0 to 5
    uint8_t remainder = (h - (sector * 43)) * 6; // 0 to 252

    uint8_t p = (v * (255 - s)) >> 8;
    uint8_t q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    uint8_t t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

    switch(sector){
        case 0: *r = v; *g = t; *b = p; break;
        case 1: *r = q; *g = v; *b = p; break;
        case 2: *r = p; *g = v; *b = t; break;
        case 3: *r = p; *g = q; *b = v; break;
        case 4: *r = t; *g = p; *b = v; break;
        default: *r = v; *g = p; *b = q; break;
    }
}