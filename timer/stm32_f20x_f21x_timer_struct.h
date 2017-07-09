#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_TIMER

/**********************************************************************
 * Область enum class-ов.
 **********************************************************************/
enum class EC_TIM_1_8_C1_REG_BIT_FIELD_POS {
    CEN         = 0,
    UDIS        = 1,
    URS         = 2,
    OPM         = 3,
    DIR         = 4,
    CMS         = 5,    // [6:5]
    ARPE        = 7,
    CKD         = 8     // [9:8]
};

enum class EC_TIM_1_8_C1_REG_BIT_MSK {
    CEN         = 1     << M_EC_TO_U8(EC_TIM_1_8_C1_REG_BIT_FIELD_POS::CEN),
    UDIS        = 1     << M_EC_TO_U8(EC_TIM_1_8_C1_REG_BIT_FIELD_POS::UDIS),
    URS         = 1     << M_EC_TO_U8(EC_TIM_1_8_C1_REG_BIT_FIELD_POS::URS),
    OPM         = 1     << M_EC_TO_U8(EC_TIM_1_8_C1_REG_BIT_FIELD_POS::OPM),
    DIR         = 1     << M_EC_TO_U8(EC_TIM_1_8_C1_REG_BIT_FIELD_POS::DIR),
    CMS         = 0b11  << M_EC_TO_U8(EC_TIM_1_8_C1_REG_BIT_FIELD_POS::CMS),
    ARPE        = 1     << M_EC_TO_U8(EC_TIM_1_8_C1_REG_BIT_FIELD_POS::ARPE),
    CKD         = 0b11  << M_EC_TO_U8(EC_TIM_1_8_C1_REG_BIT_FIELD_POS::CKD)
};

enum class EC_TIM_1_8_C2_REG_BIT_FIELD_POS {
    CCPC        = 0,
    CCUS        = 2,
    CCDS        = 3,
    MMS         = 4,    // [6:4]
    TI1S        = 7,
    OIS1        = 8,
    OIS1N       = 9,
    OIS2        = 10,
    OIS2N       = 11,
    OIS3        = 12,
    OIS3N       = 13,
    OIS4        = 14
};

enum class EC_TIM_1_8_C2_REG_BIT_MSK {
    CCPC        = 1     << M_EC_TO_U8(EC_TIM_1_8_C2_REG_BIT_FIELD_POS::CCPC),
    CCUS        = 1     << M_EC_TO_U8(EC_TIM_1_8_C2_REG_BIT_FIELD_POS::CCUS),
    CCDS        = 1     << M_EC_TO_U8(EC_TIM_1_8_C2_REG_BIT_FIELD_POS::CCDS),
    MMS         = 0b111 << M_EC_TO_U8(EC_TIM_1_8_C2_REG_BIT_FIELD_POS::MMS),
    TI1S        = 1     << M_EC_TO_U8(EC_TIM_1_8_C2_REG_BIT_FIELD_POS::TI1S),
    OIS1        = 1     << M_EC_TO_U8(EC_TIM_1_8_C2_REG_BIT_FIELD_POS::OIS1),
    OIS1N       = 1     << M_EC_TO_U8(EC_TIM_1_8_C2_REG_BIT_FIELD_POS::OIS1N),
    OIS2        = 1     << M_EC_TO_U8(EC_TIM_1_8_C2_REG_BIT_FIELD_POS::OIS2),
    OIS2N       = 1     << M_EC_TO_U8(EC_TIM_1_8_C2_REG_BIT_FIELD_POS::OIS2N),
    OIS3        = 1     << M_EC_TO_U8(EC_TIM_1_8_C2_REG_BIT_FIELD_POS::OIS3),
    OIS3N       = 1     << M_EC_TO_U8(EC_TIM_1_8_C2_REG_BIT_FIELD_POS::OIS3N),
    OIS4        = 1     << M_EC_TO_U8(EC_TIM_1_8_C2_REG_BIT_FIELD_POS::OIS4)
};

enum class EC_TIM_1_8_BDT_REG_BIT_FIELD_POS {
    DTG         = 0,    // [7:0]
    LOOK        = 8,    // [9:8]
    OSS         = 10,
    OSSR        = 11,
    BKE         = 12,
    BKP         = 13,
    AOE         = 14,
    MOE         = 15

};
enum class EC_TIM_1_8_BDT_REG_BIT_MSK {
    DTG         = 0xFF     << M_EC_TO_U8(EC_TIM_1_8_BDT_REG_BIT_FIELD_POS::DTG),
    LOOK        = 0b11     << M_EC_TO_U8(EC_TIM_1_8_BDT_REG_BIT_FIELD_POS::LOOK),
    OSS         = 1        << M_EC_TO_U8(EC_TIM_1_8_BDT_REG_BIT_FIELD_POS::OSS),
    OSSR        = 1        << M_EC_TO_U8(EC_TIM_1_8_BDT_REG_BIT_FIELD_POS::OSSR),
    BKE         = 1        << M_EC_TO_U8(EC_TIM_1_8_BDT_REG_BIT_FIELD_POS::BKE),
    BKP         = 1        << M_EC_TO_U8(EC_TIM_1_8_BDT_REG_BIT_FIELD_POS::BKP),
    AOE         = 1        << M_EC_TO_U8(EC_TIM_1_8_BDT_REG_BIT_FIELD_POS::AOE),
    MOE         = 1        << M_EC_TO_U8(EC_TIM_1_8_BDT_REG_BIT_FIELD_POS::MOE)
};


enum class EC_TIM_1_8_CCM1_REG_BIT_FIELD_POS {
    CC1S        = 0,    // [1:0]
    OC1FE       = 2,
    OC1PE       = 3,
    OC1M        = 4,    // [6:4]
    OC1CE       = 7,
    CC2S        = 8,    // [9:8]
    OC2FE       = 10,
    OC2PE       = 11,
    OC2M        = 12,   // [14:12]
    OC2CE       = 15,
};

enum class EC_TIM_1_8_CCM2_REG_BIT_FIELD_POS {
    CC3S        = 0,    // [1:0]
    OC3FE       = 2,
    OC3PE       = 3,
    OC3M        = 4,    // [6:4]
    OC3CE       = 7,
    CC4S        = 8,    // [9:8]
    OC4FE       = 10,
    OC4PE       = 11,
    OC4M        = 12,   // [14:12]
    OC4CE       = 15,
};

enum class EC_TIM_1_8_CCE_REG_BIT_FIELD_POS {
    CC1E        = 0,
    CC1P        = 1,
    CC1NE       = 2,
    CC1NP       = 3,
    CC2E        = 4,
    CC2P        = 5,
    CC2NE       = 6,
    CC2NP       = 7,
    CC3E        = 8,
    CC3P        = 9,
    CC3NE       = 10,
    CC3NP       = 11,
    CC4E        = 12,
    CC4P        = 13
};

enum class EC_TIM_1_8_CCE_REG_BIT_MSK {
    CC1E        = 1     << M_EC_TO_U8(EC_TIM_1_8_CCE_REG_BIT_FIELD_POS::CC1E),
    CC1P        = 1     << M_EC_TO_U8(EC_TIM_1_8_CCE_REG_BIT_FIELD_POS::CC1P),
    CC1NE       = 1     << M_EC_TO_U8(EC_TIM_1_8_CCE_REG_BIT_FIELD_POS::CC1NE),
    CC1NP       = 1     << M_EC_TO_U8(EC_TIM_1_8_CCE_REG_BIT_FIELD_POS::CC1NP),
    CC2E        = 1     << M_EC_TO_U8(EC_TIM_1_8_CCE_REG_BIT_FIELD_POS::CC2E),
    CC2P        = 1     << M_EC_TO_U8(EC_TIM_1_8_CCE_REG_BIT_FIELD_POS::CC2P),
    CC2NE       = 1     << M_EC_TO_U8(EC_TIM_1_8_CCE_REG_BIT_FIELD_POS::CC2NE),
    CC2NP       = 1     << M_EC_TO_U8(EC_TIM_1_8_CCE_REG_BIT_FIELD_POS::CC2NP),
    CC3E        = 1     << M_EC_TO_U8(EC_TIM_1_8_CCE_REG_BIT_FIELD_POS::CC3E),
    CC3P        = 1     << M_EC_TO_U8(EC_TIM_1_8_CCE_REG_BIT_FIELD_POS::CC3P),
    CC3NE       = 1     << M_EC_TO_U8(EC_TIM_1_8_CCE_REG_BIT_FIELD_POS::CC3NE),
    CC3NP       = 1     << M_EC_TO_U8(EC_TIM_1_8_CCE_REG_BIT_FIELD_POS::CC3NP),
    CC4E        = 1     << M_EC_TO_U8(EC_TIM_1_8_CCE_REG_BIT_FIELD_POS::CC4E),
    CC4P        = 1     << M_EC_TO_U8(EC_TIM_1_8_CCE_REG_BIT_FIELD_POS::CC4P),
};


enum class TIM1_OR_TIM8 {
    TIM1 = 0x40010000,
    TIM8 = 0x40010400
};

/*
 * Для выбора режима канала таймера (регистр CCMx, битовое поле OCx)
 */
enum class OCxM_MODE {
    FROZEN      = 0,        // Холостой ход.
    HIGH_MATH   = 1,        // 1, когда CNT == CCRx.
    LOW_MATH    = 2,        // 0, когда CNT == CCRx.
    TOGGLE      = 3,        // Когда CNT == CCRx состояние на выходе инвертируется.
    FORCE_LOW   = 4,        // OCxREF в 0,
    FORCE_HIGH  = 5,        // OCxREF в 1,
    PWM_1       = 6,        // CNT < CCRx - вывод в 1.
    PWM_2       = 7         // CNT < CCRx - вывод в 0.
};

/**********************************************************************
 * Область упакованных структур.
 **********************************************************************/
struct __attribute__((packed)) tim_1_or_8_registers_struct {
    uint32_t   C1;
    uint32_t   C2;
    uint32_t   SMC;
    uint32_t   DIE;
    uint32_t   S;
    uint32_t   EG;
    uint32_t   CCM1;
    uint32_t   CCM2;
    uint32_t   CCE;
    uint32_t   CNT;
    uint32_t   PSC;
    uint32_t   AR;
    uint32_t   RC;
    uint32_t   CC1;
    uint32_t   CC2;
    uint32_t   CC3;
    uint32_t   CC4;
    uint32_t   BDT;
    uint32_t   DC;
    uint32_t   DMA;
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

/*
 * Конкретные реализации интерфейсов.
 */
struct tim1_comp_one_channel_cfg_t {
    const TIM1_OR_TIM8        p_tim;
    const uint16_t            prescaler;
    const uint16_t            period_toggle;
    const EC_TIM_CH_TOGGLE    ch_toggle;
    const EC_TIM_CH_MODE      mode;
};


#endif
