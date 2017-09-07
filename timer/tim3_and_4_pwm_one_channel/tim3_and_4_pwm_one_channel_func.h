#include "tim_3_and_4_struct.h"
#include "string.h"

#define TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_HEADING     TIM3_OR_TIM4        P_TIM,              \
                                                            uint16_t            PRESCALER,          \
                                                            uint16_t            PERIOD_PWM_1,       \
                                                            EC_TIM_3_AND_4_CH   CH

#define TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_PARAM       P_TIM, PRESCALER,                       \
                                                            PERIOD_PWM_1, CH

template < TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
tim3_and_4_pwm_one_channel< TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::tim3_and_4_pwm_one_channel () :
    tim( ( tim_3_and_4_registers_struct* )P_TIM ),
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
            .AR         = PERIOD_PWM_1 - 1,                         // Счет с 0.
            .RES_1      = 0,
            .CC1        = 0,
            .CC2        = 0,
            .CC3        = 0,
            .CC4        = 0,
            .RES_2      = 0,
            .DC         = 0,
            .DMA        = 0,
            .O          = 0
        } ) {}

/*
 * COnstexpr функции для формирования масивов.
 */
template < TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
constexpr uint32_t tim3_and_4_pwm_one_channel< TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::ccm1_reg_msk_get ( void ) {
    uint32_t CCM1 = 0;
    if ( CH == EC_TIM_3_AND_4_CH::CH_1 ) {
        CCM1 |= M_EC_TO_U8(EC_TIM_3_AND_4_OCxM_MODE::PWM_1) << M_EC_TO_U8(EC_TIM_3_AND_4_CCM1_REG_BIT_FIELD_POS::OC1M);
    }
    if ( CH == EC_TIM_3_AND_4_CH::CH_2 ) {
        CCM1 |= M_EC_TO_U8(EC_TIM_3_AND_4_OCxM_MODE::PWM_1) << M_EC_TO_U8(EC_TIM_3_AND_4_CCM1_REG_BIT_FIELD_POS::OC2M);
    }
    return CCM1;
}

template < TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
constexpr uint32_t tim3_and_4_pwm_one_channel< TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::ccm2_reg_msk_get ( void ) {
    uint32_t CCM2 = 0;
    if ( CH == EC_TIM_3_AND_4_CH::CH_3 ) {
        CCM2 |= M_EC_TO_U8(EC_TIM_3_AND_4_OCxM_MODE::PWM_1) << M_EC_TO_U8(EC_TIM_3_AND_4_CCM2_REG_BIT_FIELD_POS::OC3M);
    }
    if ( CH == EC_TIM_3_AND_4_CH::CH_4 ) {
        CCM2 |= M_EC_TO_U8(EC_TIM_3_AND_4_OCxM_MODE::PWM_1) << M_EC_TO_U8(EC_TIM_3_AND_4_CCM2_REG_BIT_FIELD_POS::OC4M);
    }
    return CCM2;
}

template < TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
constexpr uint32_t tim3_and_4_pwm_one_channel< TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::cce_reg_msk_get ( void ) {
    uint32_t CCE = 0;    // В данном регистре для этого режима нас ничего не интересует.
    switch ( M_EC_TO_U32(CH) ) {
    case M_EC_TO_U32( EC_TIM_3_AND_4_CH::CH_1 ): CCE |= M_EC_TO_U32(EC_TIM_3_AND_4_CCE_REG_BIT_MSK::CC1E); break;
    case M_EC_TO_U32( EC_TIM_3_AND_4_CH::CH_2 ): CCE |= M_EC_TO_U32(EC_TIM_3_AND_4_CCE_REG_BIT_MSK::CC2E); break;
    case M_EC_TO_U32( EC_TIM_3_AND_4_CH::CH_3 ): CCE |= M_EC_TO_U32(EC_TIM_3_AND_4_CCE_REG_BIT_MSK::CC3E); break;
    case M_EC_TO_U32( EC_TIM_3_AND_4_CH::CH_4 ): CCE |= M_EC_TO_U32(EC_TIM_3_AND_4_CCE_REG_BIT_MSK::CC4E); break;
    }
    return CCE;
}

template < TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
void tim3_and_4_pwm_one_channel< TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::reinit ( void ) const {
    memcpy( (void*)this->tim, &this->cfg, sizeof( tim_3_and_4_registers_struct ) );
}

template < TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
void tim3_and_4_pwm_one_channel< TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::on ( void ) const {
    this->tim->C1 |= M_EC_TO_U32(EC_TIM_3_AND_4_C1_REG_BIT_MSK::CEN);
}

template < TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
void tim3_and_4_pwm_one_channel< TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::off ( void ) const {
    this->tim->C1 &= ~M_EC_TO_U32(EC_TIM_3_AND_4_C1_REG_BIT_MSK::CEN);
}

template < TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_HEADING >
void tim3_and_4_pwm_one_channel< TIM3_AND_4_PWM_ONE_CHANNEL_CFG_TEMPLATE_PARAM >::duty_set ( float duty ) const {
    switch ( M_EC_TO_U32(CH) ) {
    case M_EC_TO_U32( EC_TIM_3_AND_4_CH::CH_1 ): this->tim->CC1 = duty * PERIOD_PWM_1 - 1; break;
    case M_EC_TO_U32( EC_TIM_3_AND_4_CH::CH_2 ): this->tim->CC2 = duty * PERIOD_PWM_1 - 1; break;
    case M_EC_TO_U32( EC_TIM_3_AND_4_CH::CH_3 ): this->tim->CC3 = duty * PERIOD_PWM_1 - 1; break;
    case M_EC_TO_U32( EC_TIM_3_AND_4_CH::CH_4 ): this->tim->CC4 = duty * PERIOD_PWM_1 - 1; break;
    }
    this->tim->C1 &= ~M_EC_TO_U32(EC_TIM_3_AND_4_C1_REG_BIT_MSK::CEN);
}
