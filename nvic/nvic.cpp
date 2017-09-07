#include "nvic.h"

void nvic::irq_enable ( const IRQ_NAME IRQ ) const {
    NVIC->ISER[ M_EC_TO_U8(IRQ) / 32 ] =
            1 << M_EC_TO_U8(IRQ) % 32;
}

void nvic::irq_disable ( const IRQ_NAME IRQ ) const {
    NVIC->ICER[ M_EC_TO_U8(IRQ) / 32 ] =
            1 << M_EC_TO_U8(IRQ) % 32;
}

void nvic::irq_set_priority ( const IRQ_NAME IRQ, const IRQ_PRIO PRIO ) const {
     NVIC->IPR[ M_EC_TO_U8(IRQ) / 4 ] = M_EC_TO_U8(PRIO) << ( M_EC_TO_U8(IRQ) % 4 );
}

