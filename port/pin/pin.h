#pragma once

#include "f2_api_conf.h"

#ifdef MODULE_PORT

#include "mc_hardware_interfaces_pin.h"
#include "pin_struct.h"


/*
 * Класс объекта выхода порта (вывод уже должен быть настроен
 * как линия выхода в global_port).
 */
template < EC_PORT_NAME PORT, EC_PORT_PIN_NAME PIN_NAM >
class pin : public pin_base {
public:
    pin ( void );

    void    set     ( void )                const;
    void    reset   ( void )                const;

    void    toggle  ( void )                const;

    void    set     ( uint8_t state )       const;
    void    set     ( bool state )          const;
    void    set     ( int state )           const;

    bool    read    ( void )                const;

private:
    constexpr uint32_t  p_bsr_get                ( void );
    constexpr uint32_t  set_msk_get              ( void );
    constexpr uint32_t  reset_msk_get            ( void );
    constexpr uint32_t  odr_bit_read_bb_p_get    ( void );
    constexpr uint32_t  bb_p_idr_read_get        ( void );

    const uint32_t  p_bsr;
    const uint32_t  bsr_set_msk, bsr_reset_msk;
    const uint32_t  p_bb_odr_read, p_bb_idr_read;
};

#include "pin_func.h"

#endif
