#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_RCC

/**********************************************************************
 * Область упакованных структур.
 **********************************************************************/

/*
 * Перечень регистров физического порта ввода-вывода.
 */
struct pll_cfg_struct {
    const uint32_t              pllcfg_reg_msk;         // Маска конфигурации PLL целиком.
    const uint32_t              dev_bus_msk;            // Маска регистра RCCCFG (только части с делителями частоты шин).
    const uint32_t              flash_acr_msk;          // Маска всего регистра flash_acr (предсказатель + задержки обращения к Flash).
    const bool                  src;                    // true = HSE, false = HSI
};

#endif
