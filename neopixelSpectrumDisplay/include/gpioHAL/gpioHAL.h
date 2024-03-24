/**
 * ****************************************
 * @file    gpioHAL.h
 * @author  Yuan Nevin Biju
 * @brief   This file contains GPIO HAL interface functions.
 * ********************/

#ifndef H_GPIO_HAL_INC
#define H_GPIO_HAL_INC
/* ****************************************
 * Includes
 * ********************/
#include "driver/gpio.h"
#include "esp_err.h"

/* ****************************************
 * Enums
 * ********************/
typedef enum{
    E_GPIO_NEOPIXEL = 0,/**< GPIO for controlling Neopixel LED*/
    E_GPIO_MAX,
} gpio_list_t;

/* ****************************************
 * Struct
 * ********************/
typedef struct{
    uint8_t gpioNumber;/**<GPIO pin number*/
    gpio_mode_t gpioMode;/**<Gpio mode*/
} gpio_hal_config_t;

/* ****************************************
 * Function Declarations
 * ********************/
esp_err_t gpio_hal_init(gpio_list_t);
esp_err_t gpio_hal_set(gpio_list_t);
esp_err_t gpio_hal_reset(gpio_list_t);
esp_err_t gpio_hal_toggle(gpio_list_t);

#endif