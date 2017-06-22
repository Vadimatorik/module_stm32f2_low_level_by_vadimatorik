#ifndef STM32F2_API_RCC_STM32_F20X_F21X_RCC_FUNC_H_
#define STM32F2_API_RCC_STM32_F20X_F21X_RCC_FUNC_H_

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_RCC

#include "stm32_f20x_f21x_rcc.h"
#include <cmath>

/**********************************************************************
 * Область constexpr конструкторов.
 **********************************************************************/

constexpr rcc::rcc( const rcc_cfg* const cfg ):
    p_pll_main_cfg( cfg->pll ),
    pll_main_cfg_count( cfg->pll_count ) {};


/**********************************************************************
 * Область constexpr функций.
 **********************************************************************/



#endif
#endif
