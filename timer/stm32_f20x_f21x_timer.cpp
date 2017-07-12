#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_TIMER

#include "stm32_f20x_f21x_timer.h"
#include <string.h>

void tim1_comp_one_channel::reinit ( void ) const {
    memcpy( (void*)this->tim, &this->cfg, sizeof( tim_1_or_8_registers_struct ) );
}

void tim1_comp_one_channel::on ( void ) const {
    this->tim->C1 |= M_EC_TO_U32(EC_TIM_1_8_C1_REG_BIT_MSK::CEN);
}

void tim1_comp_one_channel::off ( void ) const {
    this->tim->C1 &= ~M_EC_TO_U32(EC_TIM_1_8_C1_REG_BIT_MSK::CEN);
}

#endif
