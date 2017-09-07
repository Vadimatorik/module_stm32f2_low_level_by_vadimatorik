#include <stdint.h>

#include "f2_api_conf.h"

struct __attribute__( ( packed ) ) iwdg_struct {
    uint32_t    K;
    uint32_t    P;
    uint32_t    RL;
    uint32_t    S;
};

#define IWDG        ( ( iwdg_struct* )( 0x40003000 ) )

enum class EC_WDT_S_POS {
    PVU         = 0,
    RVU         = 1
};

enum class EC_WDT_S_MSK {
    PVU         = 0b111     << M_EC_TO_U8( EC_WDT_S_POS::PVU ),
    RVU         = 1         << M_EC_TO_U8( EC_WDT_S_POS::RVU )
};
