#pragma once

#include "pin_struct.h"


#define PIN_CFG_TEMPLATE_HEADING            EC_PORT_NAME PORT, EC_PORT_PIN_NAME PIN_NAME
#define PIN_CFG_TEMPLATE_PARAM              PORT, PIN_NAME


template < PIN_CFG_TEMPLATE_HEADING >
pin< PIN_CFG_TEMPLATE_PARAM >::pin ( void ):
    p_bsr               ( this->p_bsr_get() ),
    bsr_set_msk         ( this->set_msk_get() ),
    bsr_reset_msk       ( this->reset_msk_get() ),
    p_bb_odr_read       ( this->odr_bit_read_bb_p_get() ),
    p_bb_idr_read       ( this->bb_p_idr_read_get() ) {}

// ********************************************************************
// * Область constexpr функций.
// *********************************************************************

//
// Метод возвращает маску установки выхода в "1" через регистр BSR.
//
template < PIN_CFG_TEMPLATE_HEADING >
constexpr uint32_t pin< PIN_CFG_TEMPLATE_PARAM >::set_msk_get ( void ) {
    return 1 << ( M_EC_TO_U8( PIN_NAME ) );
}

//
// Метод возвращает маску установки выхода в "0" через регистр BSR.
//
template < PIN_CFG_TEMPLATE_HEADING >
constexpr uint32_t pin< PIN_CFG_TEMPLATE_PARAM >::reset_msk_get ( void ) {
    return 1 << ( M_EC_TO_U8( PIN_NAME ) + 16 );
}

//
// Метод возвращает указатель на регистр BSR, к которому относится вывод.
//
template < PIN_CFG_TEMPLATE_HEADING >
constexpr uint32_t pin< PIN_CFG_TEMPLATE_PARAM >::p_bsr_get( void ) {
    uint32_t p_port = p_base_port_address_get( PORT );
    return p_port + 0x18;
}

//
// Метод возвращает указатель на bit_banding
// область памяти, в которой находится бит состояния входа.
//
template < PIN_CFG_TEMPLATE_HEADING >
constexpr uint32_t pin< PIN_CFG_TEMPLATE_PARAM >::bb_p_idr_read_get ( void ) {
    uint32_t p_port = p_base_port_address_get( PORT );
    uint32_t p_idr  = p_port + 0x10;
    return M_GET_BB_P_PER(p_idr, M_EC_TO_U8( PIN_NAME ));
}
//
// Метод возвращает указатель на bit banding область памяти,
// с выставленным пользователем состоянием на выходе вывода.
//
template < PIN_CFG_TEMPLATE_HEADING >
constexpr uint32_t pin< PIN_CFG_TEMPLATE_PARAM >::odr_bit_read_bb_p_get ( void ) {
    uint32_t p_port     = p_base_port_address_get( PORT );
    uint32_t p_reg_odr  = p_port + 0x14;
    return M_GET_BB_P_PER(p_reg_odr, M_EC_TO_U8( PIN_NAME ));
}

//
// Метод устанавливает вывод порта в <<1>>,
// если вывод настроен как выход.
template < PIN_CFG_TEMPLATE_HEADING >
void pin< PIN_CFG_TEMPLATE_PARAM >::set ( void ) const {
    *M_U32_TO_P(this->p_bsr) = this->bsr_set_msk;
}


// Метод устанавливает вывод порта в <<0>>,
// если вывод настроен как выход.
template < PIN_CFG_TEMPLATE_HEADING >
void pin< PIN_CFG_TEMPLATE_PARAM >::reset ( void ) const {
    *M_U32_TO_P(this->p_bsr) = this->bsr_reset_msk;
}


// Метод выставляет на выход заданное состояние,
// если вывод настроен как выход.
template < PIN_CFG_TEMPLATE_HEADING >
void pin< PIN_CFG_TEMPLATE_PARAM >::set ( uint8_t state ) const {
    if ( state ) {
        this->set();
    } else {
        this->reset();
    }
}

template < PIN_CFG_TEMPLATE_HEADING >
void pin< PIN_CFG_TEMPLATE_PARAM >::set ( bool state ) const {
    this->set( static_cast< uint8_t >( state ) );
}

template < PIN_CFG_TEMPLATE_HEADING >
void pin< PIN_CFG_TEMPLATE_PARAM >::set ( int state ) const {
    this->set( static_cast< uint8_t >( state ) );
}


// Метод инвертирует состояние на выходе вывода,
//  если вывод настроен как выход.
template < PIN_CFG_TEMPLATE_HEADING >
void pin< PIN_CFG_TEMPLATE_PARAM >::toggle( void ) const {
    if (*M_U32_TO_P_CONST(p_bb_odr_read)) {			// Если был 1, то выставляем 0.
        this->reset();
    } else {
        this->set();
    }
}


// Метод возвращает состояние на входе вывода.
template < PIN_CFG_TEMPLATE_HEADING >
bool pin< PIN_CFG_TEMPLATE_PARAM >::read() const {
    return *M_U32_TO_P_CONST(p_bb_idr_read);
}
