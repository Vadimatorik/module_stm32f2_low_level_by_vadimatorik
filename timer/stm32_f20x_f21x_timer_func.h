#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_TIMER

#include <cstdio>
#include <string.h>
#include "stm32_f20x_f21x_timer_struct.h"

template < TIM1_OR_TIM8 P_TIM, uint16_t PRESCALER, uint16_t PERIOD_TOGGLE, EC_TIM_CH_TOGGLE CH_TOGGLE, EC_TIM_CH_MODE MODE >
constexpr tim1_comp_one_channel_base< P_TIM, PRESCALER, PERIOD_TOGGLE, CH_TOGGLE, MODE >::tim1_comp_one_channel_base() :
    cfg_tim( {
        .C1         = 0,
        .C2         = 0,
        .SMC        = 0,
        .DIE        = 0,
        .S          = 0,
        .EG         = 0,
        .CCM1       = this->ccm1_reg_msk_get(),                  // Режим работы канала (нам нужен триггер).
        .CCM2       = this->ccm2_reg_msk_get(),
        .CCE        = this->cce_reg_msk_get(),                 // Включение-отключение выходных каналов.
        .CNT        = 0,
        .PSC        = PRESCALER,
        .AR         = PERIOD_TOGGLE,
        .RC         = 0,
        .CC1        = PERIOD_TOGGLE,    // Мы используем всего 1 канал. Остальные будут проигнорированы.
        .CC2        = PERIOD_TOGGLE,
        .CC3        = PERIOD_TOGGLE,
        .CC4        = PERIOD_TOGGLE,
        .BDT        = 0,
        .DC         = 0,
        .DMA        = 0
    } ) {}

/*
 * COnstexpr функции для формирования масивов.
 */
template < TIM1_OR_TIM8 P_TIM, uint16_t PRESCALER, uint16_t PERIOD_TOGGLE, EC_TIM_CH_TOGGLE CH_TOGGLE, EC_TIM_CH_MODE MODE >
constexpr uint32_t tim1_comp_one_channel_base< P_TIM, PRESCALER, PERIOD_TOGGLE, CH_TOGGLE, MODE >::ccm1_reg_msk_get ( void ) {
    uint32_t CCM1 = 0;    // В данном регистре для этого режима нас ничего не интересует.
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_1 ) {
        CCM1 |= M_EC_TO_U8(OCxM_MODE::TOGGLE) << M_EC_TO_U8(EC_TIM_1_8_CCM1_REG_BIT_FIELD_POS::OC1M);
    }
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_2 ) {
        CCM1 |= M_EC_TO_U8(OCxM_MODE::TOGGLE) << M_EC_TO_U8(EC_TIM_1_8_CCM1_REG_BIT_FIELD_POS::OC2M);
    }
    return CCM1;
}

template < TIM1_OR_TIM8 P_TIM, uint16_t PRESCALER, uint16_t PERIOD_TOGGLE, EC_TIM_CH_TOGGLE CH_TOGGLE, EC_TIM_CH_MODE MODE >
constexpr uint32_t tim1_comp_one_channel_base< P_TIM, PRESCALER, PERIOD_TOGGLE, CH_TOGGLE, MODE >::ccm2_reg_msk_get ( void ) {
    uint32_t CCM2 = 0;    // В данном регистре для этого режима нас ничего не интересует.
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_3 ) {
        CCM2 |= M_EC_TO_U8(OCxM_MODE::TOGGLE) << M_EC_TO_U8(EC_TIM_1_8_CCM2_REG_BIT_FIELD_POS::OC3M);
    }
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_4 ) {
        CCM2 |= M_EC_TO_U8(OCxM_MODE::TOGGLE) << M_EC_TO_U8(EC_TIM_1_8_CCM2_REG_BIT_FIELD_POS::OC4M);
    }
    return CCM2;
}

template < TIM1_OR_TIM8 P_TIM, uint16_t PRESCALER, uint16_t PERIOD_TOGGLE, EC_TIM_CH_TOGGLE CH_TOGGLE, EC_TIM_CH_MODE MODE >
constexpr uint32_t tim1_comp_one_channel_base< P_TIM, PRESCALER, PERIOD_TOGGLE, CH_TOGGLE, MODE>::cce_reg_msk_get ( void ) {
    uint32_t CCE = 0;    // В данном регистре для этого режима нас ничего не интересует.
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_1 ) {
        if ( ( MODE == EC_TIM_CH_MODE::P ) || ( MODE == EC_TIM_CH_MODE::ALL ) ) {
            CCE |= M_EC_TO_U32(EC_TIM_1_8_CCE_REG_BIT_MSK::CC1E);
        }
        if ( ( MODE == EC_TIM_CH_MODE::N ) || ( MODE == EC_TIM_CH_MODE::ALL ) ) {
            CCE |= M_EC_TO_U32(EC_TIM_1_8_CCE_REG_BIT_MSK::CC1NE);
        }
    }
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_2 ) {
        if ( ( MODE == EC_TIM_CH_MODE::P ) || ( MODE == EC_TIM_CH_MODE::ALL ) ) {
            CCE |= M_EC_TO_U32(EC_TIM_1_8_CCE_REG_BIT_MSK::CC2E);
        }
        if ( ( MODE == EC_TIM_CH_MODE::N ) || ( MODE == EC_TIM_CH_MODE::ALL ) ) {
            CCE |= M_EC_TO_U32(EC_TIM_1_8_CCE_REG_BIT_MSK::CC2NE);
        }
    }
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_3 ) {
        if ( ( MODE == EC_TIM_CH_MODE::P ) || ( MODE == EC_TIM_CH_MODE::ALL ) ) {
            CCE |= M_EC_TO_U32(EC_TIM_1_8_CCE_REG_BIT_MSK::CC3E);
        }
        if ( ( MODE == EC_TIM_CH_MODE::N ) || ( MODE == EC_TIM_CH_MODE::ALL ) ) {
            CCE |= M_EC_TO_U32(EC_TIM_1_8_CCE_REG_BIT_MSK::CC3NE);
        }
    }
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_4 ) {
        if ( ( MODE == EC_TIM_CH_MODE::P ) || ( MODE == EC_TIM_CH_MODE::ALL ) ) {
            CCE |= M_EC_TO_U32(EC_TIM_1_8_CCE_REG_BIT_MSK::CC4E);
        }
        static_assert( !( (MODE == EC_TIM_CH_MODE::N) && (CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_4) ), "Channel 4 not have N out!");
    }
    return CCE;
}


template < TIM1_OR_TIM8 P_TIM, uint16_t PRESCALER, uint16_t PERIOD_TOGGLE, EC_TIM_CH_TOGGLE CH_TOGGLE, EC_TIM_CH_MODE MODE >
void tim1_comp_one_channel_base< P_TIM, PRESCALER, PERIOD_TOGGLE, CH_TOGGLE, MODE >::reinit ( void ) const {
    tim_1_or_8_registers_struct* tim = ( tim_1_or_8_registers_struct* )P_TIM;
    memcpy( (void*)tim, &this->cfg_tim, sizeof( tim_1_or_8_registers_struct ) );
}

template < TIM1_OR_TIM8 P_TIM, uint16_t PRESCALER, uint16_t PERIOD_TOGGLE, EC_TIM_CH_TOGGLE CH_TOGGLE, EC_TIM_CH_MODE MODE >
void tim1_comp_one_channel_base< P_TIM, PRESCALER, PERIOD_TOGGLE, CH_TOGGLE, MODE >::on ( void ) const {
    tim_1_or_8_registers_struct* tim = ( tim_1_or_8_registers_struct* )P_TIM;
    tim->C1 |= M_EC_TO_U32(EC_TIM_1_8_C1_REG_BIT_MSK::CEN);
}

template < TIM1_OR_TIM8 P_TIM, uint16_t PRESCALER, uint16_t PERIOD_TOGGLE, EC_TIM_CH_TOGGLE CH_TOGGLE, EC_TIM_CH_MODE MODE >
void tim1_comp_one_channel_base< P_TIM, PRESCALER, PERIOD_TOGGLE, CH_TOGGLE, MODE >::off ( void ) const {
    tim_1_or_8_registers_struct* tim = ( tim_1_or_8_registers_struct* )P_TIM;
    tim->C1 &= ~M_EC_TO_U32(EC_TIM_1_8_C1_REG_BIT_MSK::CEN);
}

#endif
