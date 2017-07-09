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

/*
 * Выходной канал сравнения таймера 1.
 */
enum class EC_TIM_CH_TOGGLE {
    CH_1    = 0,
    CH_2    = 1,
    CH_3    = 2,
    CH_4    = 3,
};

/*
 * Какие подканалы использовать? (Прямой, инверсный, оба)
 */
enum class EC_TIM_CH_MODE {
    P       = 0,
    N       = 1,
    ALL     = 2
};

#define TEMPLATE_TIM_1_OR_8_TOGGLE       P_TIM, PRESCALER, PERIOD_TOGGLE, CH_TOGGLE, MODE

/*
 * Конкретные реализации интерфейсов.
 */
template < TIM1_OR_TIM8 P_TIM, uint16_t PRESCALER, uint16_t PERIOD_TOGGLE, EC_TIM_CH_TOGGLE CH_TOGGLE, EC_TIM_CH_MODE MODE >
class tim1_comp_one_channel_base : public tim_comp_one_channel_base {
public:
    constexpr tim1_comp_one_channel_base();
    void reinit     ( void ) const;
    void on         ( void ) const;
    void off        ( void ) const;

private:
    constexpr uint32_t ccm1_reg_msk_get ( void );
    constexpr uint32_t ccm2_reg_msk_get ( void );
    constexpr uint32_t cce_reg_msk_get  ( void );
    constexpr uint32_t bdt_reg_msk_get  ( void );
    const     tim_1_or_8_registers_struct cfg_tim;
};

#include "stm32_f20x_f21x_timer_func.h"

#endif
