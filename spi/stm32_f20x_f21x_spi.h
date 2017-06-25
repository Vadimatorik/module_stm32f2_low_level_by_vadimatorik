#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_SPI

#include "stm32_f20x_f21x_spi_struct.h"

/**********************************************************************
 * Область template оболочек.
 **********************************************************************/
template < EC_SPI_CFG_MODE              MODE,           /*
                                                         * SPI будет использовать 1 или 2
                                                         * линии.
                                                         */
           EC_SPI_CFG_ONE_LINE_MODE     LINE_MODE,      /*
                                                         * Задает режим работы для одной линии
                                                         * ( используется только в случае, если
                                                         * выбран режим работы для одной линии ).
                                                         */
           EC_SPI_CFG_DATA_FRAME        FRAME,          /*
                                                         * Размер кадра посылки.
                                                         */
           EC_SPI_CFG_RECEIVE_MODE      R_MODE,         /*
                                                         * Использовать полый дуплекс
                                                         * или только прием.
                                                         */
           EC_SPI_CFG_CS                CS,             /*
                                                         * Использовать ли аппаратный CS или нет.
                                                         */
           EC_SPI_CFG_CS_MODE           CS_M,           /*
                                                         * Если аппаратный CS используется, то
                                                         * в режиме простоя будет это состояние.
                                                         */
           EC_SPI_CFG_BAUD_RATE_DEV     BR_DEV >        /*
                                                         * Определяет делитель частоты передачи.
                                                         */
class spi_cfg : public spi_cfg_struct {
public:
    constexpr spi_cfg();

private:
    constexpr uint32_t  c1_reg_msk_get              ( void );
    constexpr uint32_t  с2_msk_get                  ( void );
};




/**********************************************************************
 * Область class-ов.
 **********************************************************************/

class spi {
public:
    constexpr spi( const spi_cfg_struct* const cfg );
private:
    const spi_cfg_struct* const cfg;
}
