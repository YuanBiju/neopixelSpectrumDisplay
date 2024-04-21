#ifndef INC_WIFI_H
#define INC_WIFI_H

#include "esp_err.h"

esp_err_t wifi_init();

void wifi_init_sta();

#endif