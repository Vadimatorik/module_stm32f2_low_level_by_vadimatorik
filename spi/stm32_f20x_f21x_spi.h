#pragma once

#include "stm32_f20x_f21x_conf.h"

#ifdef MODULE_SPI

#include "mk_hardware_interfaces_spi.h"
#include "stm32_f20x_f21x_spi_struct.h"

//**********************************************************************
// Создание масок регистров SPI по параметрам.
//**********************************************************************
template < EC_SPI_CFG_MODE              MODE,           // Мастер/ведомый.
           EC_SPI_CFG_CLK_POLARITY      POLAR,          // Поляность сигнала.
           EC_SPI_CFG_CLK_PHASE         PHASE,          // Фаза.
           EC_SPI_CFG_NUMBER_LINE       NUM_LINE,       // SPI будет использовать 1 или 2 линии.
           // Задает режим работы для одной линии ( используется только в случае, если
           // выбран режим работы для одной линии ).
           EC_SPI_CFG_ONE_LINE_MODE     ONE_LINE_MODE,
           EC_SPI_CFG_DATA_FRAME        FRAME,          // Размер кадра посылки.
           EC_SPI_CFG_RECEIVE_MODE      R_MODE,         // Использовать полый дуплекс или только прием.
           EC_SPI_CFG_FRAME_FORMAT      FORMAT,         // Формат посылок.
           EC_SPI_CFG_BAUD_RATE_DEV     BR_DEV,         // Определяет делитель частоты передачи.
           EC_SPI_CFG_INTERRUPT_TX      I_TX,           // Вызывать ли прерывания, когда пуст буфер для передачи?
           EC_SPI_CFG_INTERRUPT_RX      I_RX,           // Вызывать ли прерывания, когда буффер на прием не пуст?
           EC_SPI_CFG_INTERRUPT_ERROR   I_ER,           // Прерывание при возникнавении ошибки.
           EC_SPI_CFG_DMA_TX_BUF        DMATX,          // Буффер между DMA и SPI->D.
           EC_SPI_CFG_DMA_RX_BUF        DMARX,

           // Если у нас MASTER:
           EC_SPI_CFG_CS                CS,             // Использовать ли аппаратный CS в режиме мастера?

           // Если SLAVE:
           EC_SPI_CFG_SSM               SSM,            // Программное отслеживание CS в режиме ведомого.
           // Отслеживания CS в режиме ведомого устройства ( какой уровень считается
           // игнорированием устройтсва ).
           EC_SPI_CFG_SSM_MODE          SSM_MODE >
class spi_cfg : public spi_cfg_struct {
public:
    constexpr spi_cfg();

private:
    constexpr uint32_t  c1_reg_msk_get              ( void );
    constexpr uint32_t  c2_reg_msk_get              ( void );
};

struct spi_master_8bit_hardware_os_cfg_t {
    USER_OS_STATIC_MUTEX*       mutex;      // Для предотвращения попытки использовать 1 SPI из разных потоков одновременно.
};

//**********************************************************************
// Конфигурация SPI в режиме мастера, посылки по 8 бит.
//
// Внимание! Аппаратное переключение CS всегда работает
// ( вы можете не подключать его к линии PORT-а, если он не требуется ).
//**********************************************************************
template <  EC_SPI_NAME                  SPIx,           // SPI1, SPI2...
            EC_SPI_CFG_CLK_POLARITY      POLAR,          // Поляность сигнала.
            EC_SPI_CFG_CLK_PHASE         PHASE,          // Фаза.
            EC_SPI_CFG_NUMBER_LINE       NUM_LINE,       // SPI будет использовать 1 или 2 линии.
            // Задает режим работы для одной линии ( используется только в случае, если
            // выбран режим работы для одной линии ).
            EC_SPI_CFG_ONE_LINE_MODE     ONE_LINE_MODE,
            EC_SPI_CFG_FRAME_FORMAT      FORMAT,         // Формат посылок.
            EC_SPI_CFG_BAUD_RATE_DEV     BR_DEV >        // Определяет делитель частоты передачи.
class spi_master_8bit_hardware_os : public spi_master_8bit_base {
public:
    constexpr spi_master_8bit_hardware_os ( const spi_master_8bit_hardware_os_cfg_t* const cfg );

    void    reinit                  ( void ) const;

    EC_SPI_BASE_RESULT tx           ( const uint8_t* const  p_array_tx, const uint16_t& length, const uint32_t& timeout_ms ) const;
    EC_SPI_BASE_RESULT tx           ( const uint8_t* const  p_array_tx, uint8_t* p_array_rx, const uint16_t& length, const uint32_t& timeout_ms ) const;
    EC_SPI_BASE_RESULT tx_one_item  ( const uint8_t p_item_tx, const uint16_t count, const uint32_t timeout_ms ) const;
    EC_SPI_BASE_RESULT rx           ( uint8_t* p_array_rx, const uint16_t& length, const uint32_t& timeout_ms, const uint8_t& out_value = 0xFF ) const;

    void    on                      ( void ) const;
    void    off                     ( void ) const;

private:
    const spi_master_8bit_hardware_os_cfg_t* const cfg;

    const spi_cfg< EC_SPI_CFG_MODE::MASTER,
                   POLAR, PHASE, NUM_LINE, ONE_LINE_MODE,
                   EC_SPI_CFG_DATA_FRAME      :: FRAME_8_BIT,
                   EC_SPI_CFG_RECEIVE_MODE    :: FULL_DUPLEX,
                   FORMAT, BR_DEV,

                   // Прерывания не используются из-за их глючности (или у меня руки кривые...)
                   EC_SPI_CFG_INTERRUPT_TX::OFF,
                   EC_SPI_CFG_INTERRUPT_RX::OFF,

                   EC_SPI_CFG_INTERRUPT_ERROR :: OFF,               // Пока режимы, где бы нужен был реально этот флаг - не поддерживаются.
                   EC_SPI_CFG_DMA_TX_BUF      :: DISABLED,
                   EC_SPI_CFG_DMA_RX_BUF      :: DISABLED,
                   EC_SPI_CFG_CS              :: ENABLED,
                   EC_SPI_CFG_SSM             :: SSM_OFF,
                   EC_SPI_CFG_SSM_MODE        :: NO_USE > cfg_low;
};

#include "stm32_f20x_f21x_spi_func.h"

#endif
