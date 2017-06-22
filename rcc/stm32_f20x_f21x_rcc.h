#ifndef STM32F2_API_RCC_STM32_F20X_F21X_RCC_H_
#define STM32F2_API_RCC_STM32_F20X_F21X_RCC_H_

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_RCC

#include "stm32_f20x_f21x_rcc_struct.h"

/**********************************************************************
 * В данном файле содержится класс, экземпляром которого можно
 * управлять системой тактирования всего микроконтроллера.
 **********************************************************************/

/*
 * По средствам объекта данного класса производятся все манипуляции
 * с частотами микркоконтроллера.
 */
class rcc {
public:
    constexpr rcc( const rcc_cfg* const cfg );

private:
    const pll_cfg*          const p_pll_main_cfg;
    uint8_t                 pll_main_cfg_count;
};

#include "stm32_f20x_f21x_rcc_func.h"

#endif
#endif
