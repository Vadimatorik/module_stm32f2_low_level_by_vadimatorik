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
    p_pll_main_cfg( this->pll_main_configuration_check( cfg->pll, cfg->pll_count ) ),
    pll_main_cfg_count( cfg->pll_count ) {};


/**********************************************************************
 * Область constexpr функций.
 **********************************************************************/

/*
 * Метод проверяет правильность введенных параметров структуры pll_cfg.
 * В случае, если какой-то из параметров был неверен, компиляция прекратиться с
 * укзаанием причины.
 */
constexpr const pll_cfg* rcc::pll_main_configuration_check ( const pll_cfg* const cfg, uint8_t count ) {
    // Проверяем все имеющиеся структуры конфигурации основного PLL.
    for ( int loop = 0; loop < count; loop++ ) {
        // Ошибка в одной из структур pll_cfg, параметр M.
        if ( ( cfg[loop].m < 2 ) || ( cfg[loop].m > 63 ) )
            throw("Structure has an invalid parameter M! M >= 2 and M <= 63!");

        // Ошибка в одной из структур pll_cfg, параметр N.
        if ( ( cfg[loop].n < 192 ) || ( cfg[loop].n > 432 ) )
            throw("Structure has an invalid parameter N! N >= 192 and N <= 432!");

        // Ошибка в одной из структур pll_cfg, параметр P.
        if ( !( ( cfg[loop].p == EC_RCC_PLL_P::DIV_2 ) || ( cfg[loop].p == EC_RCC_PLL_P::DIV_4 ) ||
                ( cfg[loop].p == EC_RCC_PLL_P::DIV_6 ) || ( cfg[loop].p == EC_RCC_PLL_P::DIV_8 ) )
        )   throw("Structure has an invalid parameter P! N [DIV_2, DIV_5, DIV_6, DIV_8]");

        // Далее получаем входную частоту, на основе которой будем проверять, проходят ли делители.
        uint32_t clock = 0;
        if ( cfg->s == EC_RCC_PLL_SOURCE::HSI ) {
            clock = 16000000;
        } else {
            clock = HSE_VALUE;
        }

        // Коэффициент M подобран неверно.
        if ( ((clock / cfg[loop].m) < 1000000) || ((clock / cfg[loop].m) > 2000000) )
            throw("The coefficient M in the pll_cfg structure is incorrect!");
        clock /= cfg[loop].m;

        // Коэффициент N подобран неверно.
        if ( ((clock * cfg[loop].n) < 192000000) || ((clock * cfg[loop].n) > 432000000) )
            throw("The coefficient N in the pll_cfg structure is incorrect!");
        clock *= cfg[loop].n;

        // Коэффициент P подобран неверно.
        uint8_t dev_p = static_cast<uint8_t>(std::pow(2, static_cast<uint8_t>(cfg[loop].p) + 1));
        if ( clock / dev_p > 120000000 )
            throw("The coefficient P in the pll_cfg structure is incorrect!");
        clock *= cfg[loop].n;
    }
    return cfg;
}


#endif
#endif
