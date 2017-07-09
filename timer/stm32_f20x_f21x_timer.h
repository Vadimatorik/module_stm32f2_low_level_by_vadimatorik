#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_TIMER

#include "stm32_f20x_f21x_timer_struct.h"

/*
 * Таймер предназначен только для генерации прямоугольных испульсов на одном канале.
 * Модуль умеет только задвавать период испульсов, включать/отключать генерацию.
 * В случае, если нужено настроить модуль на другую частоту -
 * используется другой объект.
 */
class tim_comp_one_channel_base {
public:
    constexpr tim_comp_one_channel_base() {}
    virtual void reinit     ( void ) const = 0;
    virtual void on         ( void ) const = 0;
    virtual void off        ( void ) const = 0;
};


class tim1_comp_one_channel : public tim_comp_one_channel_base {
public:
    constexpr tim1_comp_one_channel ( const tim1_comp_one_channel_cfg_t* const cfg );
    void reinit     ( void ) const;
    void on         ( void ) const;
    void off        ( void ) const;

private:
    tim_1_or_8_registers_struct*    const tim;
    constexpr uint32_t ccm1_reg_msk_get ( const EC_TIM_CH_TOGGLE CH );
    constexpr uint32_t ccm2_reg_msk_get ( const EC_TIM_CH_TOGGLE CH_TOGGLE );
    constexpr uint32_t cce_reg_msk_get  ( const EC_TIM_CH_TOGGLE CH_TOGGLE, const EC_TIM_CH_MODE MODE  );
    constexpr uint32_t bdt_reg_msk_get  ( void );
    const     tim_1_or_8_registers_struct cfg;
};

#include "stm32_f20x_f21x_timer_func.h"

#endif
