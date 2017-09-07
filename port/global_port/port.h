#pragma once

#include "f2_api_conf.h"

#ifdef MODULE_PORT

#include "port_struct.h"

/*
 * Класс объекта "глобального порта".
 * Через него происходит управление выводами и сменой конфигурации.
 */

class global_port {
public:
    constexpr   global_port ( const pin_config_t* const pin_cfg_array, const uint32_t pin_count );

    EC_ANSWER_GP             reinit_all_ports            ( void ) const;
    EC_ANSWER_GP             reinit_port                 ( EC_PORT_NAME port ) const;
    EC_PORT_LOCKED_KEY       get_state_locked_key_port   ( EC_PORT_NAME port ) const;
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

#include "port_func.h"

#endif
