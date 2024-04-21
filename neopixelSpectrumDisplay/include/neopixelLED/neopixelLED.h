/**
 * ****************************************
 * @file    neopixelLED.h
 * @author  Yuan Nevin Biju
 * @brief   This file contains neopixel LED interface functions.
 * ********************/

#ifndef H_NEOPIXEL_LED_INC
#define H_NEOPIXEL_LED_INC
/* ****************************************
 * Includes
 * ********************/
#include "esp_err.h"

#define NUM_LEDS 60

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

/* ****************************************
 * Function Declarations
 * ********************/
void neopixelLED_init();

#endif