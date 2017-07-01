#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_SPI

#include "stm32_f20x_f21x_spi_struct.h"

/**********************************************************************
 * Область template оболочек.
 **********************************************************************/
template < EC_SPI_CFG_MODE              MODE,           /*
                                                         * Мастер/ведомый.
                                                         */
           EC_SPI_CFG_CLK_POLARITY      POLAR,          /*
                                                         * Поляность сигнала.
                                                         */
           EC_SPI_CFG_CLK_PHASE         PHASE,          /*
                                                         * Фаза.
                                                         */
           EC_SPI_CFG_NUMBER_LINE       NUM_LINE,       /*
                                                         * SPI будет использовать 1 или 2
                                                         * линии.
                                                         */
           EC_SPI_CFG_ONE_LINE_MODE     ONE_LINE_MODE,  /*
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
           EC_SPI_CFG_FRAME_FORMAT      FORMAT,         /*
                                                         * Формат посылок.
                                                         */
           EC_SPI_CFG_BAUD_RATE_DEV     BR_DEV,         /*
                                                         * Определяет делитель частоты передачи.
                                                         */
           EC_SPI_CFG_INTERRUPT_TX      I_TX,           /*
                                                         * Вызывать ли прерывания, когда пустой буфер
                                                         * для передачи?
                                                         */
           EC_SPI_CFG_INTERRUPT_RX      I_RX,           /*
                                                         * Прерывание, когда буффер на прием не пуст.
                                                         */
           EC_SPI_CFG_INTERRUPT_ERROR   I_ER,           /*
                                                         * Прерывание при возникнавении ошибки.
                                                         */
           EC_SPI_CFG_DMA_TX_BUF        DMATX,          /* Буффер между DMA и SPI_D. */
           EC_SPI_CFG_DMA_RX_BUF        DMARX,

           /* Если у нас мастер */
           EC_SPI_CFG_CS                CS,             /*
                                                         * Использовать ли аппаратный CS в режиме мастера?
                                                         */

           /* Если SLAVE */
           EC_SPI_CFG_SSM               SSM,            /*
                                                         * Программное отслеживание CS в режиме ведомого.
                                                         */
           EC_SPI_CFG_SSM_MODE          SSM_MODE >      /*
                                                         * Параметр для отслеживания CS в режиме
                                                         * ведомого устройства (какой уровень считается
                                                         * игнорированием устройтсва).
                                                         */

class spi_cfg : public spi_cfg_struct {
public:
    constexpr spi_cfg();

private:
    constexpr uint32_t  c1_reg_msk_get              ( void );
    constexpr uint32_t  c2_reg_msk_get              ( void );
};

/*
 * Этот класс является чисто виртуальным базовым классом
 * для всех реализаций SPI.
 * Он содержит методы, которые обязательно должны быть в
 * классах-наследниках.
 */
class spi_base {
public:
    /*
     * p_array_tx   -   указатель на массив, который требуется передать
     *                  по spi. Указатель на 0-й передаваемый байт
     *                  ( байт, с которого будет начата передача ).
     * length       -   длина посылки. length != 0! length >= 1!
     *
     * ЗАМЕЧАНИЕ: входной прием не ведется!
     */

    virtual int tx ( uint8_t* p_array_tx, uint16_t length, uint32_t timeout_ms ) const = 0;

    /*
     * p_array_tx   -   указатель на массив, который требуется передать
     *                  по spi. Указатель на 0-й передаваемый байт
     *                  ( байт, с которого будет начата передача ).
     *
     * p_array_rx   -   указатель на массив, в который будет
     *                  осуществляться прием по spi.
     *                  Указатель на 0-й принемаемый байт
     *                  ( первый пришедший байт ).
     *
     * length       -   длина посылки. length != 0! length >= 1!
     *
     *
     * ЗАМЕЧАНИЕ: p_array_tx может быть равен p_array_rx. Тогда
     * принятые данные перезапишут входные.
     */

    virtual int tx ( uint8_t* p_array_tx, uint8_t* p_array_rx, uint16_t length, uint32_t timeout_ms ) const = 0;

   /*
    * p_array_rx    -   указатель на массив, в который будет
    *                   осуществляться прием по spi.
    *                   Указатель на 0-й принемаемый байт
    *                   ( первый пришедший байт ).
    *
    * length        -   колличество принемаемых байт.
    * value_out     -   значение, которое будет отправляться
    *                   ( в случае, если SPI мастер ).
    */
    virtual int rx ( uint8_t* p_array_rx, uint16_t length, uint32_t timeout_ms, uint8_t out_value = 0 ) const = 0;

    virtual ~spi_base() {}
};

/**********************************************************************
 * Область class-ов.
 **********************************************************************/
template <  EC_SPI_NAME                  SPIx,
            EC_SPI_CFG_CLK_POLARITY      POLAR,          /*
                                                          * Поляность сигнала.
                                                          */
            EC_SPI_CFG_CLK_PHASE         PHASE,          /*
                                                          * Фаза.
                                                          */
            EC_SPI_CFG_NUMBER_LINE       NUM_LINE,       /*
                                                          * SPI будет использовать 1 или 2
                                                          * линии.
                                                          */
            EC_SPI_CFG_ONE_LINE_MODE     ONE_LINE_MODE,  /*
                                                          * Задает режим работы для одной линии
                                                          * ( используется только в случае, если
                                                          * выбран режим работы для одной линии ).
                                                          */
            EC_SPI_CFG_DATA_FRAME        FRAME,          /*
                                                          * Размер кадра посылки.
                                                          */
            EC_SPI_CFG_FRAME_FORMAT      FORMAT,         /*
                                                          * Формат посылок.
                                                          */
            EC_SPI_CFG_BAUD_RATE_DEV     BR_DEV,         /*
                                                          * Определяет делитель частоты передачи.
                                                          */
            EC_SPI_CFG_CS                CS >            /*
                                                          * Использовать ли аппаратный CS в режиме мастера?
                                                          */
class spi_master_hardware : public spi_base {
public:
    constexpr spi_master_hardware ( void );

    int     reinit                  ( void ) const;
    int     tx                      ( uint8_t* p_array_tx, uint16_t length, uint32_t timeout_ms ) const;
    int     tx                      ( uint8_t* p_array_tx, uint8_t* p_array_rx, uint16_t length, uint32_t timeout_ms ) const;
    int     rx                      ( uint8_t* p_array_rx, uint16_t length, uint32_t timeout_ms, uint8_t out_value = 0 ) const;

    void   on   ( void ) const;
    void   off  ( void ) const;

private:
    mutable USER_OS_MUTEX       mutex       = USER_OS_CREATE_MUTEX_FUNC();              // Для предотвращения попытки использовать
                                                                                        // 1 SPI из разных потоков одновременно.
    mutable USER_OS_SEMAPHORE   semaphore   = USER_OS_CREATE_SEMAPHORE_FUNC();          // Сигнализирует об успешной передаче или
                                                                                        // приеме ).

    const spi_cfg< EC_SPI_CFG_MODE::MASTER,
                   POLAR, PHASE, NUM_LINE, ONE_LINE_MODE, FRAME,
                   EC_SPI_CFG_RECEIVE_MODE    :: FULL_DUPLEX,
                   FORMAT, BR_DEV,

                   /*
                    * Выставляем разрешение прерывания по опустошению выходного буффера, если
                    * у нас используются обе линии или же одна в режиме выхода.
                    */
                   ( ( NUM_LINE == EC_SPI_CFG_NUMBER_LINE::LINE_2 ) ||
                        ( ( NUM_LINE == EC_SPI_CFG_NUMBER_LINE::LINE_1 ) && ( ONE_LINE_MODE == EC_SPI_CFG_ONE_LINE_MODE::TRANSMIT_ONLY ) ) ) ?
                            EC_SPI_CFG_INTERRUPT_TX::ON : EC_SPI_CFG_INTERRUPT_TX::OFF,

                   // Та же тема и с RX.
                   ( ( NUM_LINE == EC_SPI_CFG_NUMBER_LINE::LINE_2 ) ||
                        ( ( NUM_LINE == EC_SPI_CFG_NUMBER_LINE::LINE_1 ) && ( ONE_LINE_MODE == EC_SPI_CFG_ONE_LINE_MODE::RECEIVE_ONLY ) ) ) ?
                            EC_SPI_CFG_INTERRUPT_RX::ON : EC_SPI_CFG_INTERRUPT_RX::OFF,

                   EC_SPI_CFG_INTERRUPT_ERROR :: ON,
                   EC_SPI_CFG_DMA_TX_BUF      :: DISABLED,
                   EC_SPI_CFG_DMA_RX_BUF      :: DISABLED,
                   CS,
                   EC_SPI_CFG_SSM             :: SSM_OFF,
                   EC_SPI_CFG_SSM_MODE        :: NO_USE > cfg;
};

#include "stm32_f20x_f21x_spi_func.h"

#endif
