#pragma once

#include "stm32_f20x_f21x_conf.h"

/**********************************************************************
 * Область упакованных структур.
 **********************************************************************/

/*
 * Регистры физического модуля NVIC.
 */
struct __attribute__((packed)) nvic_registers_struct {
    volatile uint32_t   ISER0;
    volatile uint32_t   ISER1;
    volatile uint32_t   ISER2;
    volatile uint32_t   ICER0;
    volatile uint32_t   ICER1;
    volatile uint32_t   ICER2;
    volatile uint32_t   ISPR0;
    volatile uint32_t   ISPR1;
    volatile uint32_t   ISPR2;
    volatile uint32_t   ICPR0;
    volatile uint32_t   ICPR1;
    volatile uint32_t   ICPR2;
    volatile uint32_t   IABR0;
    volatile uint32_t   IABR1;
    volatile uint32_t   IABR2;
    volatile uint32_t   IPR0;
    volatile uint32_t   IPR1;
    volatile uint32_t   IPR2;
    volatile uint32_t   IPR3;
    volatile uint32_t   IPR4;
    volatile uint32_t   IPR5;
    volatile uint32_t   IPR6;
    volatile uint32_t   IPR7;
    volatile uint32_t   IPR8;
    volatile uint32_t   IPR9;
    volatile uint32_t   IPR10;
    volatile uint32_t   IPR11;
    volatile uint32_t   IPR12;
    volatile uint32_t   IPR13;
    volatile uint32_t   IPR14;
    volatile uint32_t   IPR15;
    volatile uint32_t   IPR16;
    volatile uint32_t   IPR17;
    volatile uint32_t   IPR18;
    volatile uint32_t   IPR19;
    volatile uint32_t   IPR20;
};
