#pragma once

#include "nvic.h"                   // NVIC тянем всегда.
#include "freertos_headers.h"
#include "f2_api_conf.h"

/*
 * Подключаем файлы-заголовки модулей (которые используются).
 */
#ifdef MODULE_PORT
#include "pin.h"
#include "port.h"
#include "pin_many_cfg_pin.h"
#endif

#ifdef MODULE_RCC
#include "rcc.h"
#endif

#ifdef MODULE_SPI
#include "spi.h"
#endif

#ifdef MODULE_TIMER
#include "tim3_and_4_pwm_one_channel.h"
#include "tim1_and_8_comp_one_channel.h"
#include "tim6_and_7_interrupt.h"
#endif

#ifdef MODULE_WDT
#include "wdt.h"
#endif
