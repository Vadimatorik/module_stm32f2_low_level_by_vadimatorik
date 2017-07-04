#pragma once

#include "stm32_f20x_f21x_conf.h"

/*
 * Подключаем файлы-заголовки модулей (которые используются).
 */
#ifdef MODULE_PORT
#include "stm32_f20x_f21x_port.h"
#endif

#ifdef MODULE_RCC
#include "stm32_f20x_f21x_rcc.h"
#endif

#ifdef MODULE_SPI
#include "stm32_f20x_f21x_spi.h"
#endif
