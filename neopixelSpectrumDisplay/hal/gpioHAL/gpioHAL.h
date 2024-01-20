/**
 * ****************************************
 * @file    gpioHAL.h
 * @author  Yuan Nevin Biju
 * @brief   Header file for GPIO HAL interface functions
 * @date    2023-12-31
 * 
 * @copyright Copyright (c) 2023
 * ********************/

#ifndef H_GPIOHAL_INC
#define H_GPIOHAL_INC
/* ****************************************
 * Includes
 * ********************/
#include "driver/gpio.h"

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
} gpio_config_t;

/* ****************************************
 * Function Declarations
 * ********************/
error_flag_t gpio_init(gpio_list_t, uint8_t);
error_flag_t gpio_set(gpio_list_t);
error_flag_t gpio_reset(gpio_list_t);
error_flag_t gpio_toggle(gpio_list_t);

#endif