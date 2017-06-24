#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_PORT

#include "stm32_f20x_f21x_port_struct.h"
#include "stm32_f20x_f21x_port_constexpr_func.h"

/**********************************************************************
 * В данном файле содержатся классы, экземпляры которых нацелены
 * на работу с физическими линиями ввода-вывода портов
 * выбранного микроконтроллера.
 **********************************************************************/

/*
 * Класс объекта выхода порта (вывод уже должен быть настроен
 * как линия выхода в global_port).
 */

#include "stm32_f20x_f21x_port_struct_class_pin.h"

class pin {
public:
    constexpr pin ( const pin_config_t* const pin_cfg_array );

    void    set     ( void ) const;
    void    reset   ( void ) const;
    void    set     ( uint8_t state ) const;
    void    set     ( bool state ) const;
    void    set     ( int state ) const;
    void    invert  ( void ) const;
    int     read    ( void ) const;

private:
    constexpr uint32_t  p_bsr_get                ( const pin_config_t* const pin_cfg_array );
    constexpr uint32_t  set_msk_get              ( const pin_config_t* const pin_cfg_array );
    constexpr uint32_t  reset_msk_get            ( const pin_config_t* const pin_cfg_array );
    constexpr uint32_t  odr_bit_read_bb_p_get    ( const pin_config_t* const pin_cfg_array );
    constexpr uint32_t  bb_p_idr_read_get        ( const pin_config_t* const pin_cfg_array );


    const uint32_t  p_bsr;
    const uint32_t  bsr_set_msk, bsr_reset_msk;
    const uint32_t  p_bb_odr_read, p_bb_idr_read;
};

#include "stm32_f20x_f21x_port_constexpr_func_class_pin.h"

/*
 * Класс объекта вывода порта.
 * Базируется на классе pin, но в отличии от него может
 * переконфигурировать выводы.
 */

class many_configurations_pin : public pin {
public:
    constexpr many_configurations_pin ( const pin_config_t* const pin_cfg_array, uint8_t size = 1 );

    EC_ANSWER_PIN_REINIT    reinit  (uint8_t number_config) const;

private:
    constexpr uint32_t  bb_p_looking_bit_get     ( const pin_config_t* const pin_cfg_array );

    const uint32_t  p_port;
    const uint32_t  cfg_count;
    const uint32_t  p_bb_key_looking, p_bb_looking_bit;

    const pin_config_t  *cfg;
};

#include "stm32_f20x_f21x_port_constexpr_func_class_many_configurations_pin.h"

/*
 * Класс объекта "глобального порта".
 * Через него происходит управление выводами и сменой конфигурации.
 */

#include "stm32_f20x_f21x_port_struct_class_global_port.h"

class global_port {
public:
    constexpr   global_port ( const pin_config_t* const pin_cfg_array, const uint32_t pin_count );

    E_ANSWER_GP             reinit_all_ports            ( void ) const;
    E_ANSWER_GP             reinit_port                 ( EC_PORT_NAME port ) const;
    E_PORT_LOCKED_KEY       get_state_locked_key_port   ( EC_PORT_NAME port ) const;
    E_ANSWER_PORT_SET_LOCK  set_locked_key_port         ( EC_PORT_NAME port ) const;
    E_ANSWER_PORT_SET_LOCK  set_locked_keys_all_port    ( void ) const;

    uint32_t  msk_get ( void ) const;
private:
    constexpr uint32_t  moder_reg_reset_init_msk_get    ( EC_PORT_NAME port_name );
    constexpr uint32_t  reg_moder_init_msk              ( const pin_config_t* const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name );
    constexpr uint32_t  reg_otyper_init_msk             ( const pin_config_t* const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name );
    constexpr uint32_t  speed_reg_reset_init_msk_get    ( EC_PORT_NAME port_name );
    constexpr uint32_t  reg_speed_init_msk              ( const pin_config_t* const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name );
    constexpr uint32_t  pupd_reg_reset_init_msk_get     ( EC_PORT_NAME port_name );
    constexpr uint32_t  reg_pupd_init_msk               ( const pin_config_t* const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name );
    constexpr uint32_t  reg_lck_init_msk                ( const pin_config_t* const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name );
    constexpr uint32_t  reg_afl_init_msk                ( const pin_config_t* const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name );
    constexpr uint32_t  reg_afh_msk_init_get            ( const pin_config_t* const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name );
    constexpr uint32_t  reg_od_msk_init_get             ( const pin_config_t* const pin_cfg_array, const uint32_t pin_count, const EC_PORT_NAME port_name );
    constexpr uint32_t  clk_msk_get                     ( const pin_config_t* const pin_cfg_array, const uint32_t pin_count );

    constexpr global_port_msk_reg_struct        fill_out_mas_struct         ( const pin_config_t* const pin_cfg_array, const uint32_t pin_count );
    constexpr port_registers_flash_copy_struct  fill_out_one_port_struct    ( EC_PORT_NAME p_name, const pin_config_t* const pin_cfg_array, const uint32_t pin_count );

    void    write_image_port_in_registrs    ( uint8_t number ) const;

    const global_port_msk_reg_struct    gb_msk_struct;
};

#include "stm32_f20x_f21x_port_constexpr_func_class_global_port.h"

#endif
