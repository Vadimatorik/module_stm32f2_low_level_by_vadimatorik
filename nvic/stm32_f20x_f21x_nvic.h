#pragma once

#include "stm32_f20x_f21x_conf.h"

/*
 * Номер позиции прерывания.
 */
enum class IRQ_NAME {
    SPI1        = 35
};

enum class IRQ_PRIO {
    PRIO_0      = 0,
    PRIO_1      = 1 << 4,
    PRIO_2      = 2 << 4,
    PRIO_3      = 3 << 4,
    PRIO_4      = 4 << 4,
    PRIO_5      = 5 << 4,
    PRIO_6      = 6 << 4,
    PRIO_7      = 7 << 4,
    PRIO_8      = 8 << 4,
    PRIO_9      = 9 << 4,
    PRIO_10     = 10 << 4,
    PRIO_11     = 11 << 4,
    PRIO_12     = 12 << 4,
    PRIO_13     = 13 << 4,
    PRIO_14     = 14 << 4,
    PRIO_15     = 15 << 4,
};


/**********************************************************************
 * Область упакованных структур.
 **********************************************************************/

/*
 * Регистры физического модуля NVIC.
 */
struct __attribute__((packed)) nvic_registers_struct {
    volatile uint32_t   ISER[3];
    volatile uint32_t   ICER[3];
    volatile uint32_t   ISPR[3];
    volatile uint32_t   ICPR[3];
    volatile uint32_t   IABR[3];
    volatile uint32_t   IPR[21];
};

#define NVIC            ( ( nvic_registers_struct* ) ( 0xE000E100 ) )

class nvic {
public:
    constexpr nvic() {}

    void    irq_enable             ( const IRQ_NAME IRQ ) const;
    void    irq_disable            ( const IRQ_NAME IRQ ) const;
    void    irq_set_priority       ( const IRQ_NAME IRQ, const IRQ_PRIO PRIO ) const;

private:

};
