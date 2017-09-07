#pragma once

#include "f2_api_conf.h"

#ifdef MODULE_TIMER

enum class TIM6_OR_TIM7 {
    TIM6 = 0x40001000,
    TIM7 = 0x40001400
};

struct __attribute__ ( ( packed ) ) tim_6_and_7_registers_struct {
    uint32_t   C1;
    uint32_t   C2;
    uint32_t   RES_0;   // Зарезервировано.
    uint32_t   DIE;
    uint32_t   S;
    uint32_t   EG;
    uint32_t   RES_1;   // Зарезервировано.
    uint32_t   RES_2;   // Зарезервировано.
    uint32_t   RES_3;   // Зарезервировано.
    uint32_t   CNT;
    uint32_t   PSC;
    uint32_t   AR;
};

enum class EC_TIM_6_AND_7_C1_REG_BIT_FIELD_POS {
    CEN         = 0,
    UDIS        = 1,
    URS         = 2,
    OPM         = 3,
    ARPE        = 7
};

enum class EC_TIM_6_AND_7_C1_REG_BIT_MSK {
    CEN         = 1     << M_EC_TO_U8( EC_TIM_6_AND_7_C1_REG_BIT_FIELD_POS::CEN ),
    UDIS        = 1     << M_EC_TO_U8( EC_TIM_6_AND_7_C1_REG_BIT_FIELD_POS::UDIS ),
    URS         = 1     << M_EC_TO_U8( EC_TIM_6_AND_7_C1_REG_BIT_FIELD_POS::URS ),
    OPM         = 1     << M_EC_TO_U8( EC_TIM_6_AND_7_C1_REG_BIT_FIELD_POS::OPM ),
    ARPE        = 1     << M_EC_TO_U8( EC_TIM_6_AND_7_C1_REG_BIT_FIELD_POS::ARPE )
};

enum class EC_TIM_6_AND_7_DIE_REG_BIT_FIELD_POS {
    UIE         = 0,
    UDE         = 1
};

enum class EC_TIM_6_AND_7_DIE_REG_BIT_MSK {
    UIE         = 1     << M_EC_TO_U8( EC_TIM_6_AND_7_DIE_REG_BIT_FIELD_POS::UIE ),
    UDE         = 1     << M_EC_TO_U8( EC_TIM_6_AND_7_DIE_REG_BIT_FIELD_POS::UDE )
};

#endif
