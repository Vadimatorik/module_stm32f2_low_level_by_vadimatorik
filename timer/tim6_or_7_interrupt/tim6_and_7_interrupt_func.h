#pragma once

#include "stm32_f20x_f21x_timer_6_and_7_struct.h"
#include "mk_hardware_interfaces_timer.h"

// Генератор прерываний.
#define TIM6_AND_7_COMP_ONE_CHANNEL_CFG_TEMPLATE_HEADING     TIM6_OR_TIM7        P_TIM,              \
                                                            uint16_t            PRESCALER,          \
                                                            uint16_t            PERIOD_TOGGLE

#define TIM6_AND_7_COMP_ONE_CHANNEL_CFG_TEMPLATE_PARAM       P_TIM, PRESCALER, PERIOD_TOGGLE

template < TIM6_AND_7_COMP_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
tim6_and_7_interrupt< TIM6_AND_7_COMP_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::tim6_and_7_interrupt () :
    tim( ( tim_6_and_7_registers_struct* )P_TIM ),
    cfg( {
            .C1         = 0,
            .C2         = 0,
            .RES_0      = 0,
            .DIE        = M_EC_TO_U32( EC_TIM_6_AND_7_DIE_REG_BIT_MSK::UIE ),
            .S          = 0,
            .EG         = 0,
            .RES_1      = 0,                        // Режим работы канала (нам нужен триггер).
            .RES_2      = 0,
            .RES_3      = 0,                        // Включение-отключение выходных каналов.
            .CNT        = 0,
            .PSC        = PRESCALER - 1,            // Счет с 0.
            .AR         = PERIOD_TOGGLE - 1,        // Счет с 0.
        } ) {}

template < TIM6_AND_7_COMP_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
void tim6_and_7_interrupt< TIM6_AND_7_COMP_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::reinit ( void ) const {
    memcpy( (void*)this->tim, &this->cfg, sizeof( tim_6_and_7_registers_struct ) );
}

template < TIM6_AND_7_COMP_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
void tim6_and_7_interrupt< TIM6_AND_7_COMP_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::on ( void ) const {
    this->tim->C1 |= M_EC_TO_U32( EC_TIM_6_AND_7_C1_REG_BIT_MSK::CEN );
}

template < TIM6_AND_7_COMP_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
void tim6_and_7_interrupt< TIM6_AND_7_COMP_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::off ( void ) const {
    this->tim->C1 &= ~M_EC_TO_U32( EC_TIM_6_AND_7_C1_REG_BIT_MSK::CEN );
}

template < TIM6_AND_7_COMP_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
void tim6_and_7_interrupt< TIM6_AND_7_COMP_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::clear_interrupt_flag ( void ) const {
    this->tim->S = 0;
}
