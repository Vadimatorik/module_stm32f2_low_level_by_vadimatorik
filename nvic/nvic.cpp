#include "nvic.h"

void nvic::irq_spi1_enable ( void ) {
    NVIC->ISER1 = 1 << 3;
}

void nvic::irq_spi1_disable ( void ) {
    NVIC->ICER1 = 1 << 3;
}

void nvic::irq_spi1_set_priority ( uint8_t prio ) {
    (void)prio;
}
