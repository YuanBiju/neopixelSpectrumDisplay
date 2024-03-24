/**
 * ****************************************
 * @file    gpioHAL.h
 * @author  Yuan Nevin Biju
 * @brief   Header file for GPIO HAL interface functions
 * @date    2023-12-31
 * 
 * @copyright Copyright (c) 2023
 * ********************/

/* ****************************************
 * Includes
 * ********************/
#include "gpioHAL.h"

/* ****************************************
 * Defines
 * ********************/
#define NEOPIXEL_GPIO_PIN_NUMBER    4
#define NEOPIXEL_GPIO_MODE          GPIO_MODE_OUTPUT

/* ****************************************
 * Data
 * ********************/
static gpio_config_t gpioTable[E_GPIO_MAX] = {
    {NEOPIXEL_GPIO_PIN_NUMBER, NEOPIXEL_GPIO_MODE},
}

/* ****************************************
 * Function Definitions
 * ********************/
/**
 * @brief   Initialize GPIO pin
 * @param   gpioInstance Enumerated GPIO instance
 * @retval  error_flag_t Returns E_ERROR_FLAG if any errors occur else returns E_OK_FLAG
*/
error_flag_t gpio_hal_init(gpio_list_t gpioInstance){
    /**Select NEOPIXEL GPIO*/
    gpio_pad_select_gpio(gpioTable[E_GPIO_NEOPIXEL].gpioNumber);
    /**Set the GPIO as a push/pull output */
    gpio_set_direction(gpioTable[E_GPIO_NEOPIXEL].gpioNumber, gpioTable[E_GPIO_NEOPIXEL].gpioMode);
}

error_flag_t gpio_hal_set(gpio_list_t gpioInstance){

}

error_flag_t gpio_hal_reset(gpio_list_t gpioInstance){

}

error_flag_t gpio_hal_toggle(gpio_list_t gpioInstance){
    
}