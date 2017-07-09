#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_TIMER

#include "stm32_f20x_f21x_timer_struct.h"


constexpr tim1_comp_one_channel::tim1_comp_one_channel ( const tim1_comp_one_channel_cfg_t* const cfg ) :
    tim( ( tim_1_or_8_registers_struct* )cfg->p_tim ),
    cfg( {
            .C1         = 0,
            .C2         = 0,
            .SMC        = 0,
            .DIE        = 0,
            .S          = 0,
            .EG         = 0,
            .CCM1       = this->ccm1_reg_msk_get( cfg->ch_toggle ),           // Режим работы канала (нам нужен триггер).
            .CCM2       = this->ccm2_reg_msk_get( cfg->ch_toggle ),
            .CCE        = this->cce_reg_msk_get( cfg->ch_toggle, cfg->mode ), // Включение-отключение выходных каналов.
            .CNT        = 0,
            .PSC        = ( uint16_t )( cfg->prescaler - 1 ),                        // Счет с 0.
            .AR         = ( uint16_t )( cfg->period_toggle - 1 ),                    // Счет с 0.
            .RC         = 0,
            .CC1        = 0,
            .CC2        = 0,
            .CC3        = 0,
            .CC4        = 0,
            .BDT        = this->bdt_reg_msk_get(),                   // Общее разрешение выходных каналов.
            .DC         = 0,
            .DMA        = 0
        } ) {}

/*
 * COnstexpr функции для формирования масивов.
 */
constexpr uint32_t tim1_comp_one_channel::ccm1_reg_msk_get ( const EC_TIM_CH_TOGGLE CH ) {
    uint32_t CCM1 = 0;
    if ( CH == EC_TIM_CH_TOGGLE::CH_1 ) {
        CCM1 |= M_EC_TO_U8(OCxM_MODE::TOGGLE) << M_EC_TO_U8(EC_TIM_1_8_CCM1_REG_BIT_FIELD_POS::OC1M);
    }
    if ( CH == EC_TIM_CH_TOGGLE::CH_2 ) {
        CCM1 |= M_EC_TO_U8(OCxM_MODE::TOGGLE) << M_EC_TO_U8(EC_TIM_1_8_CCM1_REG_BIT_FIELD_POS::OC2M);
    }
    return CCM1;
}

constexpr uint32_t tim1_comp_one_channel::ccm2_reg_msk_get ( const EC_TIM_CH_TOGGLE CH_TOGGLE ) {
    uint32_t CCM2 = 0;
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_3 ) {
        CCM2 |= M_EC_TO_U8(OCxM_MODE::TOGGLE) << M_EC_TO_U8(EC_TIM_1_8_CCM2_REG_BIT_FIELD_POS::OC3M);
    }
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_4 ) {
        CCM2 |= M_EC_TO_U8(OCxM_MODE::TOGGLE) << M_EC_TO_U8(EC_TIM_1_8_CCM2_REG_BIT_FIELD_POS::OC4M);
    }
    return CCM2;
}

constexpr uint32_t tim1_comp_one_channel::bdt_reg_msk_get( void ) {
    uint32_t BDT = 0;
    BDT |= M_EC_TO_U32(EC_TIM_1_8_BDT_REG_BIT_MSK::MOE);        // Общее разрешение выходных каналов.
    return BDT;
}


constexpr uint32_t tim1_comp_one_channel::cce_reg_msk_get ( const EC_TIM_CH_TOGGLE CH_TOGGLE, const EC_TIM_CH_MODE MODE ) {
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
    }
    return CCE;
}


#endif
