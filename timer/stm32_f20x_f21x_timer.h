#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_TIMER

#include "mk_hardware_interfaces_timer.h"
#include "stm32_f20x_f21x_timer_struct.h"

template < TIM1_OR_TIM8        P_TIM,
           uint16_t            PRESCALER,
           uint16_t            PERIOD_TOGGLE,
           EC_TIM_CH_TOGGLE    CH_TOGGLE,
           EC_TIM_CH_MODE      MODE >
class tim1_or_8_comp_one_channel : public tim_comp_one_channel_base {
public:
    tim1_or_8_comp_one_channel ();
    void reinit     ( void ) const;
    void on         ( void ) const;
    void off        ( void ) const;

private:
    constexpr uint32_t ccm1_reg_msk_get ();
    constexpr uint32_t ccm2_reg_msk_get ();
    constexpr uint32_t cce_reg_msk_get  ();
    constexpr uint32_t bdt_reg_msk_get  ();

    tim_1_or_8_registers_struct*            const tim;
    const tim_1_or_8_registers_struct       cfg;
};

#include "stm32_f20x_f21x_timer_func.h"

#endif
