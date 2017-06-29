#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_PORT

#include "stm32_f20x_f21x_port.h"

/**********************************************************************
 * Область constexpr конструкторов.
 **********************************************************************/

constexpr many_configurations_pin::many_configurations_pin ( const pin_config_t* const pin_cfg_array, uint8_t size ) : pin( pin_cfg_array ),
    p_port              ( p_base_port_address_get( pin_cfg_array->port ) ),
    cfg_count           ( size ),
    p_bb_key_looking    ( bb_p_port_look_key_get( pin_cfg_array->port ) ),
    p_bb_looking_bit    ( this->bb_p_looking_bit_get( pin_cfg_array ) ),
    cfg                 ( pin_cfg_array ) {};

/**********************************************************************
 * Область constexpr функций.
 **********************************************************************/

/*
 * Метод возвращает указатель на bit banding область
 * памяти бита блокировки конфигурации конкретного вывода.
 */
constexpr uint32_t many_configurations_pin::bb_p_looking_bit_get ( const pin_config_t* const pin_cfg_array ) {
    uint32_t p_port	= p_base_port_address_get(pin_cfg_array->port);             // Получаем физический адрес порта вывода.
    uint32_t p_looking_bit = p_port + 0x1C;                                     // Прибавляем смещение к LCKR регистру.
    return M_GET_BB_P_PER(p_looking_bit, M_EC_TO_U8(pin_cfg_array->pin_name));  // Получаем адрес конкретного бита регистра LCKR.
}

#endif
