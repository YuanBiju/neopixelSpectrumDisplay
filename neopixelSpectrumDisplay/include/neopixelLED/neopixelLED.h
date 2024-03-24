/**
 * ****************************************
 * @file    neopixelLED.h
 * @author  Yuan Nevin Biju
 * @brief   This file contains neopixel LED interface functions.
 * ********************/

#ifndef H_GPIO_HAL_INC
#define H_GPIO_HAL_INC
/* ****************************************
 * Includes
 * ********************/
#include "esp_err.h"

/* ****************************************
 * Enums
 * ********************/


/* ****************************************
 * Struct
 * ********************/
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

/* ****************************************
 * Function Declarations
 * ********************/
void set_led_colour(uint8_t redValue, uint8_t greenValue, uint8_t blueValue);
void hsv_to_rgb(uint8_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g, uint8_t *b);
void neopixel_animation();

#endif