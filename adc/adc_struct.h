#pragma once

#include "f2_api_conf.h"

#ifdef MODULE_ADC

namespace ADC {

enum class S_R_BF_POS {
    AWD         = 0,
    EOC         = 1,
    JEOC        = 2,
    JSTRT       = 3,
    STRT        = 4,
    OVR         = 5
};

enum class S_R_BF_MSK {
    AWD         = 1 << M_EC_TO_U8( S_R_BF_POS::AWD ),
    EOC         = 1 << M_EC_TO_U8( S_R_BF_POS::EOC ),
    JEOC        = 1 << M_EC_TO_U8( S_R_BF_POS::JEOC ),
    JSTRT       = 1 << M_EC_TO_U8( S_R_BF_POS::JSTRT ),
    STRT        = 1 << M_EC_TO_U8( S_R_BF_POS::STRT ),
    OVR         = 1 << M_EC_TO_U8( S_R_BF_POS::OVR )
};

enum class C1_R_BF_POS {
    AWDCH       = 0,
    EOCIE       = 5,
    AWDIE       = 6,
    JEOCIE      = 7,
    SCAN        = 8,
    AWDSGL      = 9,
    JAUTO       = 10,
    DISCEN      = 11,
    JDISCEN     = 12,
    DISCNUM     = 13,
    JAWDEN      = 22,
    AWDEN       = 23,
    RES         = 24,
    OVRIE       = 25,
};

enum class C1_R_BF_MSK {
    AWDCH       = 0b11111 << M_EC_TO_U8( C1_R_BF_POS::AWDCH ),
    EOCIE       = 1       << M_EC_TO_U8( C1_R_BF_POS::EOCIE ),
    AWDIE       = 1       << M_EC_TO_U8( C1_R_BF_POS::AWDIE ),
    JEOCIE      = 1       << M_EC_TO_U8( C1_R_BF_POS::JEOCIE ),
    SCAN        = 1       << M_EC_TO_U8( C1_R_BF_POS::SCAN ),
    AWDSGL      = 1       << M_EC_TO_U8( C1_R_BF_POS::AWDSGL ),
    JAUTO       = 1       << M_EC_TO_U8( C1_R_BF_POS::JAUTO ),
    DISCEN      = 1       << M_EC_TO_U8( C1_R_BF_POS::DISCEN ),
    JDISCEN     = 1       << M_EC_TO_U8( C1_R_BF_POS::JDISCEN ),
    DISCNUM     = 0b111   << M_EC_TO_U8( C1_R_BF_POS::DISCNUM ),
    JAWDEN      = 1       << M_EC_TO_U8( C1_R_BF_POS::JAWDEN ),
    AWDEN       = 1       << M_EC_TO_U8( C1_R_BF_POS::AWDEN ),
    RES         = 0b11    << M_EC_TO_U8( C1_R_BF_POS::RES ),
    OVRIE       = 1       << M_EC_TO_U8( C1_R_BF_POS::OVRIE ),
};

enum class C2_R_BF_POS {
    ADON        = 0,
    CONT        = 1,
    DMA         = 8,
    DDS         = 9,
    EOCS        = 10,
    ALIGN       = 11,
    JEXTSEL     = 16,
    JEXTEN      = 20,
    JSWSTART    = 22,
    EXTSEL      = 24,
    EXTEN       = 28,
    SWSTART     = 30
};

enum class C2_R_BF_MSK {
    ADON        = 0b1       << M_EC_TO_U8( C2_R_BF_POS::ADON ),
    CONT        = 0b1       << M_EC_TO_U8( C2_R_BF_POS::CONT ),
    DMA         = 0b1       << M_EC_TO_U8( C2_R_BF_POS::DMA ),
    DDS         = 0b1       << M_EC_TO_U8( C2_R_BF_POS::DDS ),
    EOCS        = 0b1       << M_EC_TO_U8( C2_R_BF_POS::EOCS ),
    ALIGN       = 0b1       << M_EC_TO_U8( C2_R_BF_POS::ALIGN ),
    JEXTSEL     = 0b1111    << M_EC_TO_U8( C2_R_BF_POS::JEXTSEL ),
    JEXTEN      = 0b11      << M_EC_TO_U8( C2_R_BF_POS::JEXTEN ),
    JSWSTART    = 0b1       << M_EC_TO_U8( C2_R_BF_POS::JSWSTART ),
    EXTSEL      = 0b1111    << M_EC_TO_U8( C2_R_BF_POS::EXTSEL ),
    EXTEN       = 0b11      << M_EC_TO_U8( C2_R_BF_POS::EXTEN ),
    SWSTART     = 0b1       << M_EC_TO_U8( C2_R_BF_POS::SWSTART )
};

namespace CFG {

enum class NAME {
    ADC1         = 0x40012000,
    ADC2         = 0x40012100,
    ADC3         = 0x40012200
};

enum class RES {
    R_12BIT      = 0,
    R_10BIT      = 1,
    R_8BIT       = 2,
    R_6BIT       = 3
};

enum class SAMPLING_TIME {
    C_3          = 0,
    C_15         = 1,
    C_28         = 2,
    C_56         = 3,
    C_84         = 4,
    C_112        = 5,
    C_144        = 6,
    C_480        = 7
};
}

struct __attribute__((packed)) R_STRUCT {
    uint32_t   S;
    uint32_t   C1;
    uint32_t   C2;
    uint32_t   SMP[2];
    uint32_t   JOF[4];
    uint32_t   HT;
    uint32_t   LT;
    uint32_t   SQ[3];
    uint32_t   JSQ;
    uint32_t   JDR[4];
    uint32_t   D;
};

}

namespace ADC_COM {

struct __attribute__((packed)) R_STRUCT {
    uint32_t    CS;
    uint32_t    CC;
    uint32_t    CD;
};

enum class CC_R_BF_POS {
    MULTI       = 0,
    DELAY       = 8,
    DDS         = 13,
    DMA         = 14,
    ADCPRE      = 16,
    VBATE       = 22,
    TSVREFE     = 23
};

enum class CC_R_BF_MSK {
    MULTI        = 0b11111       << M_EC_TO_U8( CC_R_BF_POS::MULTI ),
    DELAY        = 0b1111        << M_EC_TO_U8( CC_R_BF_POS::DELAY ),
    DDS          = 1             << M_EC_TO_U8( CC_R_BF_POS::DDS ),
    DMA          = 0b11          << M_EC_TO_U8( CC_R_BF_POS::DMA ),
    ADCPRE       = 0b11          << M_EC_TO_U8( CC_R_BF_POS::ADCPRE ),
    VBATE        = 1             << M_EC_TO_U8( CC_R_BF_POS::VBATE ),
    TSVREFE      = 1             << M_EC_TO_U8( CC_R_BF_POS::TSVREFE )
};

}

#define ADC_COM_CFG         ( ADC_COM::R_STRUCT* )0x40012300;

#endif
