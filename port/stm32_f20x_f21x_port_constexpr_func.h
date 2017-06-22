#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_PORT

#include "stm32_f20x_f21x_port_struct.h"

/*
 * Возвращает указатель на базовый адрес выбранного порта ввода-вывода
 * на карте памяти в соответствии с выбранным контроллером.
 */
constexpr uint32_t p_base_port_address_get( EC_PORT_NAME port_name ) {
    switch( port_name ){
#ifdef PORTA
    case EC_PORT_NAME::A:   return 0x40020000;
#endif
#ifdef PORTB
    case EC_PORT_NAME::B:   return 0x40020400;
#endif
#ifdef PORTC
    case EC_PORT_NAME::C:   return 0x40020800;
#endif
#ifdef PORTD
    case EC_PORT_NAME::D:   return 0x40020C00;
#endif
#ifdef PORTE
    case EC_PORT_NAME::E:   return 0x40021000;
#endif
#ifdef PORTF
    case EC_PORT_NAME::F:   return 0x40021400;
#endif
#ifdef PORTG
    case EC_PORT_NAME::G:   return 0x40021800;
#endif
#ifdef PORTH
    case EC_PORT_NAME::H:   return 0x40021C00;
#endif
#ifdef PORTI
    case EC_PORT_NAME::I:   return 0x40022000;
#endif
    }
}

/*
 * Указатель на bit_banding область памяти, в которой находится бит блокировки порта.
 */
constexpr uint32_t bb_p_port_look_key_get( EC_PORT_NAME port_name ) {
    uint32_t port_point = p_base_port_address_get( port_name ); // Получаем физический адрес порта вывода.
    port_point += 0x1C;                                         // Прибавляем смещение к IDR регистру.
    return M_GET_BB_P_PER( port_point, 16 );                    // Получаем адрес конкретного бита регистра IDR (состояние на входе).
}

#endif
