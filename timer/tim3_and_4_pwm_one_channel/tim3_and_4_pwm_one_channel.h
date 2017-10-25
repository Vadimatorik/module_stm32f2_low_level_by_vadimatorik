#pragma once

#include "f2_api_conf.h"

#ifdef MODULE_TIMER

#include "mc_hardware_interfaces_timer.h"
#include "tim_3_and_4_struct.h"

//
// Генератор ШИМ сигнала таймерами 3 и 5.
//
template < TIM3_OR_TIM4        P_TIM,                   // Используемый таймер.
           uint16_t            PRESCALER,               // Предделитель 1..0x10000.
           uint16_t            PERIOD_TOGGLE,           // Еще 1 делитель 1..0x10000.
           EC_TIM_3_AND_4_CH   CH_TOGGLE >              // Канал, на котором произволится генерация (именно таймера, не пина!).
class tim3_and_4_pwm_one_channel : public tim_pwm_one_channel_base {
public:
    tim3_and_4_pwm_one_channel ();
    void reinit     ( void )        const;
    void on         ( void )        const;
    void off        ( void )        const;

    void duty_set   ( float duty )  const;

private:
    constexpr uint32_t ccm1_reg_msk_get ();
    constexpr uint32_t ccm2_reg_msk_get ();
    constexpr uint32_t cce_reg_msk_get  ();

    tim_3_and_4_registers_struct*            const tim;
    const tim_3_and_4_registers_struct       cfg;
};

#include "tim3_and_4_pwm_one_channel_func.h"

#endif
