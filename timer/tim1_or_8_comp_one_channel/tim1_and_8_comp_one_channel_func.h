#include "tim_1_and_8_struct.h"
#include "string.h"

#define tim1_and_8_comp_one_channel_CFG_TEMPLATE_HEADING     TIM1_OR_TIM8        P_TIM,              \
                                                            uint16_t            PRESCALER,          \
                                                            uint16_t            PERIOD_TOGGLE,      \
                                                            EC_TIM_CH_TOGGLE    CH_TOGGLE,          \
                                                            EC_TIM_CH_MODE      MODE

#define tim1_and_8_comp_one_channel_CFG_TEMPLATE_PARAM       P_TIM, PRESCALER,                       \
                                                            PERIOD_TOGGLE, CH_TOGGLE, MODE

template < tim1_and_8_comp_one_channel_CFG_TEMPLATE_HEADING >
tim1_and_8_comp_one_channel< tim1_and_8_comp_one_channel_CFG_TEMPLATE_PARAM >::tim1_and_8_comp_one_channel () :
    tim( ( tim_1_and_8_registers_struct* )P_TIM ),
    cfg( {
            .C1         = 0,
            .C2         = 0,
            .SMC        = 0,
            .DIE        = 0,
            .S          = 0,
            .EG         = 0,
            .CCM1       = this->ccm1_reg_msk_get(),                 // Режим работы канала (нам нужен триггер).
            .CCM2       = this->ccm2_reg_msk_get(),
            .CCE        = this->cce_reg_msk_get(),                  // Включение-отключение выходных каналов.
            .CNT        = 0,
            .PSC        = PRESCALER - 1,                            // Счет с 0.
            .AR         = PERIOD_TOGGLE - 1,                        // Счет с 0.
            .RC         = 0,
            .CC1        = 0,
            .CC2        = 0,
            .CC3        = 0,
            .CC4        = 0,
            .BDT        = this->bdt_reg_msk_get(),                  // Общее разрешение выходных каналов.
            .DC         = 0,
            .DMA        = 0
        } ) {}

/*
 * COnstexpr функции для формирования масивов.
 */
template < tim1_and_8_comp_one_channel_CFG_TEMPLATE_HEADING >
constexpr uint32_t tim1_and_8_comp_one_channel< tim1_and_8_comp_one_channel_CFG_TEMPLATE_PARAM >::ccm1_reg_msk_get ( void ) {
    uint32_t CCM1 = 0;
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_1 ) {
        CCM1 |= M_EC_TO_U8(OCxM_MODE::TOGGLE) << M_EC_TO_U8(EC_TIM_1_AND_8_CCM1_REG_BIT_FIELD_POS::OC1M);
    }
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_2 ) {
        CCM1 |= M_EC_TO_U8(OCxM_MODE::TOGGLE) << M_EC_TO_U8(EC_TIM_1_AND_8_CCM1_REG_BIT_FIELD_POS::OC2M);
    }
    return CCM1;
}

template < tim1_and_8_comp_one_channel_CFG_TEMPLATE_HEADING >
constexpr uint32_t tim1_and_8_comp_one_channel< tim1_and_8_comp_one_channel_CFG_TEMPLATE_PARAM >::ccm2_reg_msk_get ( void ) {
    uint32_t CCM2 = 0;
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_3 ) {
        CCM2 |= M_EC_TO_U8(OCxM_MODE::TOGGLE) << M_EC_TO_U8(EC_TIM_1_AND_8_CCM2_REG_BIT_FIELD_POS::OC3M);
    }
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_4 ) {
        CCM2 |= M_EC_TO_U8(OCxM_MODE::TOGGLE) << M_EC_TO_U8(EC_TIM_1_AND_8_CCM2_REG_BIT_FIELD_POS::OC4M);
    }
    return CCM2;
}

template < tim1_and_8_comp_one_channel_CFG_TEMPLATE_HEADING >
constexpr uint32_t tim1_and_8_comp_one_channel< tim1_and_8_comp_one_channel_CFG_TEMPLATE_PARAM >::bdt_reg_msk_get ( void ) {
    uint32_t BDT = 0;
    BDT |= M_EC_TO_U32(EC_TIM_1_AND_8_BDT_REG_BIT_MSK::MOE);        // Общее разрешение выходных каналов.
    return BDT;
}


template < tim1_and_8_comp_one_channel_CFG_TEMPLATE_HEADING >
constexpr uint32_t tim1_and_8_comp_one_channel< tim1_and_8_comp_one_channel_CFG_TEMPLATE_PARAM >::cce_reg_msk_get ( void ) {
    uint32_t CCE = 0;    // В данном регистре для этого режима нас ничего не интересует.
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_1 ) {
        if ( ( MODE == EC_TIM_CH_MODE::P ) || ( MODE == EC_TIM_CH_MODE::ALL ) ) {
            CCE |= M_EC_TO_U32(EC_TIM_1_AND_8_CCE_REG_BIT_MSK::CC1E);
        }
        if ( ( MODE == EC_TIM_CH_MODE::N ) || ( MODE == EC_TIM_CH_MODE::ALL ) ) {
            CCE |= M_EC_TO_U32(EC_TIM_1_AND_8_CCE_REG_BIT_MSK::CC1NE);
        }
    }
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_2 ) {
        if ( ( MODE == EC_TIM_CH_MODE::P ) || ( MODE == EC_TIM_CH_MODE::ALL ) ) {
            CCE |= M_EC_TO_U32(EC_TIM_1_AND_8_CCE_REG_BIT_MSK::CC2E);
        }
        if ( ( MODE == EC_TIM_CH_MODE::N ) || ( MODE == EC_TIM_CH_MODE::ALL ) ) {
            CCE |= M_EC_TO_U32(EC_TIM_1_AND_8_CCE_REG_BIT_MSK::CC2NE);
        }
    }
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_3 ) {
        if ( ( MODE == EC_TIM_CH_MODE::P ) || ( MODE == EC_TIM_CH_MODE::ALL ) ) {
            CCE |= M_EC_TO_U32(EC_TIM_1_AND_8_CCE_REG_BIT_MSK::CC3E);
        }
        if ( ( MODE == EC_TIM_CH_MODE::N ) || ( MODE == EC_TIM_CH_MODE::ALL ) ) {
            CCE |= M_EC_TO_U32(EC_TIM_1_AND_8_CCE_REG_BIT_MSK::CC3NE);
        }
    }
    if ( CH_TOGGLE == EC_TIM_CH_TOGGLE::CH_4 ) {
        if ( ( MODE == EC_TIM_CH_MODE::P ) || ( MODE == EC_TIM_CH_MODE::ALL ) ) {
            CCE |= M_EC_TO_U32(EC_TIM_1_AND_8_CCE_REG_BIT_MSK::CC4E);
        }
    }
    return CCE;
}

template < tim1_and_8_comp_one_channel_CFG_TEMPLATE_HEADING >
void tim1_and_8_comp_one_channel< tim1_and_8_comp_one_channel_CFG_TEMPLATE_PARAM >::reinit ( void ) const {
    memcpy( (void*)this->tim, &this->cfg, sizeof( tim_1_and_8_registers_struct ) );
}

template < tim1_and_8_comp_one_channel_CFG_TEMPLATE_HEADING >
void tim1_and_8_comp_one_channel< tim1_and_8_comp_one_channel_CFG_TEMPLATE_PARAM >::on ( void ) const {
    this->tim->C1 |= M_EC_TO_U32(EC_TIM_1_AND_8_C1_REG_BIT_MSK::CEN);
}

template < tim1_and_8_comp_one_channel_CFG_TEMPLATE_HEADING >
void tim1_and_8_comp_one_channel< tim1_and_8_comp_one_channel_CFG_TEMPLATE_PARAM >::off ( void ) const {
    this->tim->C1 &= ~M_EC_TO_U32(EC_TIM_1_AND_8_C1_REG_BIT_MSK::CEN);
}
