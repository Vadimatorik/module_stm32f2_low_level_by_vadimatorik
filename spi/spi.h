#pragma once

#include "f2_api_conf.h"

#ifdef MODULE_SPI

#include "mk_hardware_interfaces_spi.h"
#include "spi_struct.h"

//**********************************************************************
// Создание масок регистров SPI по параметрам.
//**********************************************************************
template < SPI::CFG::MODE              MODE,           // Мастер/ведомый.
           SPI::CFG::CLK_POLARITY      POLAR,          // Поляность сигнала.
           SPI::CFG::CLK_PHASE         PHASE,          // Фаза.
           SPI::CFG::NUMBER_LINE       NUM_LINE,       // SPI будет использовать 1 или 2 линии.
           // Задает режим работы для одной линии ( используется только в случае, если
           // выбран режим работы для одной линии ).
           SPI::CFG::ONE_LINE_MODE     ONE_LINE_MODE,
           SPI::CFG::DATA_FRAME        FRAME,          // Размер кадра посылки.
           SPI::CFG::RECEIVE_MODE      R_MODE,         // Использовать полый дуплекс или только прием.
           SPI::CFG::FRAME_FORMAT      FORMAT,         // Формат посылок.
           SPI::CFG::BAUDRATE_DEV      BR_DEV,         // Определяет делитель частоты передачи.
           SPI::CFG::INTERRUPT_TX      I_TX,           // Вызывать ли прерывания, когда пуст буфер для передачи?
           SPI::CFG::INTERRUPT_RX      I_RX,           // Вызывать ли прерывания, когда буффер на прием не пуст?
           SPI::CFG::INTERRUPT_ERROR   I_ER,           // Прерывание при возникнавении ошибки.
           SPI::CFG::DMA_TX_BUF        DMATX,          // Буффер между DMA и SPI->D.
           SPI::CFG::DMA_RX_BUF        DMARX,

           // Если у нас MASTER:
           SPI::CFG::CS                CS,             // Использовать ли аппаратный CS в режиме мастера?

           // Если SLAVE:
           SPI::CFG::SSM               SSM,            // Программное отслеживание CS в режиме ведомого.
           // Отслеживания CS в режиме ведомого устройства ( какой уровень считается
           // игнорированием устройтсва ).
           SPI::CFG::SSM_MODE          SSM_MODE >
class spi_cfg : public SPI::CFG::STRUCT {
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
template <  SPI::CFG::NAME              SPIx,           // SPI1, SPI2...
            SPI::CFG::CLK_POLARITY      POLAR,          // Поляность сигнала.
            SPI::CFG::CLK_PHASE         PHASE,          // Фаза.
            SPI::CFG::NUMBER_LINE       NUM_LINE,       // SPI будет использовать 1 или 2 линии.
            // Задает режим работы для одной линии ( используется только в случае, если
            // выбран режим работы для одной линии ).
            SPI::CFG::ONE_LINE_MODE     ONE_LINE_MODE,
            SPI::CFG::FRAME_FORMAT      FORMAT,         // Формат посылок.
            SPI::CFG::BAUDRATE_DEV      BR_DEV >        // Определяет делитель частоты передачи.
class spi_master_8bit_hardware_os : public spi_master_8bit_base {
public:
    constexpr spi_master_8bit_hardware_os ( const spi_master_8bit_hardware_os_cfg_t* const cfg );

    void    reinit                  ( void ) const;

    SPI::BASE_RESULT tx           ( const uint8_t* const  p_array_tx, const uint16_t& length, const uint32_t& timeout_ms ) const;
    SPI::BASE_RESULT tx           ( const uint8_t* const  p_array_tx, uint8_t* p_array_rx, const uint16_t& length, const uint32_t& timeout_ms ) const;
    SPI::BASE_RESULT tx_one_item  ( const uint8_t p_item_tx, const uint16_t count, const uint32_t timeout_ms ) const;
    SPI::BASE_RESULT rx           ( uint8_t* p_array_rx, const uint16_t& length, const uint32_t& timeout_ms, const uint8_t& out_value = 0xFF ) const;

    void    on                      ( void ) const;
    void    off                     ( void ) const;

private:
    const spi_master_8bit_hardware_os_cfg_t* const cfg;

    const spi_cfg< SPI::CFG::MODE::MASTER,
                   POLAR, PHASE, NUM_LINE, ONE_LINE_MODE,
                   SPI::CFG::DATA_FRAME      :: FRAME_8_BIT,
                   SPI::CFG::RECEIVE_MODE    :: FULL_DUPLEX,
                   FORMAT, BR_DEV,

                   // Прерывания не используются из-за их глючности (или у меня руки кривые...)
                   SPI::CFG::INTERRUPT_TX::OFF,
                   SPI::CFG::INTERRUPT_RX::OFF,

                   SPI::CFG::INTERRUPT_ERROR :: OFF,               // Пока режимы, где бы нужен был реально этот флаг - не поддерживаются.
                   SPI::CFG::DMA_TX_BUF      :: DISABLED,
                   SPI::CFG::DMA_RX_BUF      :: DISABLED,
                   SPI::CFG::CS              :: ENABLED,
                   SPI::CFG::SSM             :: SSM_OFF,
                   SPI::CFG::SSM_MODE        :: NO_USE > cfg_low;
};

#include "spi_func.h"

#endif
