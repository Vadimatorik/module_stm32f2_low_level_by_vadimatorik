#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_PORT

#include "stm32_f20x_f21x_port.h"

/*
 * Метод устанавливает вывод порта в <<1>>,
 * если вывод настроен как выход.
 */
void pin::set ( void ) const {
    *M_U32_TO_P(this->p_bsr) = this->bsr_set_msk;
}

/*
 * Метод устанавливает вывод порта в <<0>>,
 * если вывод настроен как выход.
 */
void pin::reset ( void ) const {
    *M_U32_TO_P(this->p_bsr) = this->bsr_reset_msk;
}

/*
 * Метод выставляет на выход заданное состояние,
 * если вывод настроен как выход.
 */
void pin::set ( uint8_t state ) const {
    if ( state ) {
        this->set();
    } else {
        this->reset();
    }
}

void pin::set ( bool state ) const {
    this->set( static_cast< uint8_t >( state ) );
}

void pin::set ( int state ) const {
    this->set( static_cast< uint8_t >( state ) );
}

/*
 * Метод инвертирует состояние на выходе вывода,
 * если вывод настроен как выход.
 */
void pin::invert( void ) const {
    if (*M_U32_TO_P_CONST(p_bb_odr_read)) {			// Если был 1, то выставляем 0.
        this->reset();
    } else {
        this->set();
    }
}

/*
 * Метод возвращает состояние на входе вывода.
 */
int pin::read() const {
    return *M_U32_TO_P_CONST(p_bb_idr_read);
}

#endif
