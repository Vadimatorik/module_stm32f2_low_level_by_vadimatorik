#ifndef STM32F2_API_PORT_STM32_F20X_F21X_PORT_CONSTEXPR_FUNC_CLASS_PIN_H_
#define STM32F2_API_PORT_STM32_F20X_F21X_PORT_CONSTEXPR_FUNC_CLASS_PIN_H_

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_PORT

#include "stm32_f20x_f21x_port_struct.h"
#include "stm32_f20x_f21x_port_struct_class_pin.h"

/**********************************************************************
 * Область constexpr конструкторов.
 **********************************************************************/

constexpr pin::pin ( const pin_config_t* const pin_cfg_array/*, uint8_t size*/ ):
    //cfg                 (pin_cfg_array),
    //cfg_count           (size),
    p_port              (p_base_port_address_get(pin_cfg_array->port)),
    //p_bb_key_looking    (bb_p_port_look_key_get(pin_cfg_array->port)),
    p_odr               (this->p_odr_get(pin_cfg_array)),
    p_bb_odr_read       (this->odr_bit_read_bb_p_get(pin_cfg_array)),
    odr_set_msk         (this->set_msk_get(pin_cfg_array)),
    odr_reset_msk       (this->reset_msk_get(pin_cfg_array)),
    p_bb_idr_read       (this->bb_p_idr_read_get(pin_cfg_array))
    //p_bb_looking_bit    (this->bb_p_looking_bit_get(pin_cfg_array)) {};
    {};
/**********************************************************************
 * Область constexpr функций.
 **********************************************************************/

/*
 * Метод возвращает маску установки выхода в "1" через регистр BSR.
 */
constexpr uint32_t pin::set_msk_get ( const pin_config_t* const pin_cfg_array ) {
    return 1 << M_EC_TO_U8(pin_cfg_array->pin_name);
}

/*
 * Метод возвращает маску установки выхода в "0" через регистр BSR.
 */
constexpr uint32_t pin::reset_msk_get ( const pin_config_t* const pin_cfg_array ) {
    return 1 << (M_EC_TO_U8(pin_cfg_array->pin_name) + 16);
}

/*
 * Метод возвращает указатель на bit_banding
 * область памяти, в которой находится бит состояния входа.
 */
constexpr uint32_t pin::bb_p_idr_read_get (const pin_config_t* const pin_cfg_array ) {
    uint32_t p_port = p_base_port_address_get(pin_cfg_array->port);     // Получаем физический адрес порта вывода.
    uint32_t p_idr  = p_port + 0x10;                                    // Прибавляем смещение к IDR регистру.
    return M_GET_BB_P_PER(p_idr, M_EC_TO_U8(pin_cfg_array->pin_name));  // Получаем адрес конкретного бита регистра IDR (состояние на входе).
}

/*
 * Метод возвращает указатель на регистр ODR, к которому относится вывод.
 */
constexpr uint32_t pin::p_odr_get( const pin_config_t* const pin_cfg_array ) {
    uint32_t p_port	= p_base_port_address_get(pin_cfg_array->port);	    // Получаем физический адрес порта вывода.
    return p_port + 0x14;                                               // 0x14 - смещение от начала порта.
}

/*
 * Метод возвращает указатель на bit banding область памяти,
 * с выставленным пользователем состоянием на выходе вывода.
 */
constexpr uint32_t pin::odr_bit_read_bb_p_get ( const pin_config_t* const pin_cfg_array ) {
    uint32_t p_port	= p_base_port_address_get(pin_cfg_array->port);             // Получаем физический адрес порта вывода.
    uint32_t p_reg_odr	= p_port + 0x14;                                        // Прибавляем смещение к ODR регистру.
    return M_GET_BB_P_PER(p_reg_odr, M_EC_TO_U8(pin_cfg_array->pin_name));      // Получаем адрес конкретного бита
                                                                                // регистра ODR (состояние на входе).
}

/*
 * Метод возвращает указатель на bit banding область
 * памяти бита блокировки конфигурации конкретного вывода.
 *//*
constexpr uint32_t pin::bb_p_looking_bit_get ( const pin_config_t* const pin_cfg_array ) {
    uint32_t p_port	= p_base_port_address_get(pin_cfg_array->port);             // Получаем физический адрес порта вывода.
    uint32_t p_looking_bit = p_port + 0x1C;                                     // Прибавляем смещение к LCKR регистру.
    return M_GET_BB_P_PER(p_looking_bit, M_EC_TO_U8(pin_cfg_array->pin_name));  // Получаем адрес конкретного бита регистра LCKR.
}*/

#endif
#endif
