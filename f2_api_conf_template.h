#pragma once
// BIT_FIELD BF
// R REG
/*
 * В данном файле происходит настройка всех параметров бибилиотеки.
 */
#include <stdint.h>

/*
 * Раскомментируйте строку с выбранным вами контроллером.
 */
// #define STM32F205RB
// #define STM32F205RC
// #define STM32F205RE
// #define STM32F205RF
// #define STM32F205RG
// #define STM32F205VB
// #define STM32F205VC
// #define STM32F205VE
// #define STM32F205VF
// #define STM32F205VG
// #define STM32F205ZC
// #define STM32F205ZE
// #define STM32F205ZF
// #define STM32F205ZG

// #define STM32F207IC
// #define STM32F207IE
// #define STM32F207IF
// #define STM32F207IG
// #define STM32F207VC
// #define STM32F207VE
// #define STM32F207VF
// #define STM32F207VG
// #define STM32F207ZC
// #define STM32F207ZE
// #define STM32F207ZF
// #define STM32F207ZG

// Частота внешнего кварцевого генератора (если таковой будет использован).
#define	HSE_VALUE							16000000

//**********************************************************************
// Модули, которые планируется использовать в проекте.
// Для того, чтобы библиотека могла использовать модуль -
// - раскомментируйте строчку с требуемым модулем.
//**********************************************************************
//#define MODULE_PORT
//#define MODULE_RCC
//#define MODULE_SPI



//**********************************************************************
//								Определения, не касающиеся основных модулей.
//**********************************************************************
#define BIT_BAND_SRAM_REF   0x20000000
#define BIT_BAND_SRAM_BASE  0x22000000

//Получаем адрес бита RAM в Bit Banding области.
#define MACRO_GET_BB_P_SRAM(reg, bit) ((BIT_BAND_SRAM_BASE + (reg - BIT_BAND_SRAM_REF)*32 + (bit * 4)))

#define BIT_BAND_PER_REF    ((uint32_t)0x40000000)
#define BIT_BAND_PER_BASE   ((uint32_t)0x42000000)

// Получаем адрес бита периферии в Bit Banding области.
#define M_GET_BB_P_PER(ADDRESS,BIT) ((BIT_BAND_PER_BASE + (ADDRESS - BIT_BAND_PER_REF)*32 + (BIT * 4)))

// Преобразует число в uint32_t переменной в указатель на uint32_t.
// Причем запрещает переписывать то, что по указателю (только чтение).
#define M_U32_TO_P_CONST(point)         ( ( const uint32_t *const )( point ) )

// Преобразует число в uint32_t переменной в указатель на uint32_t.
// Данные по указателю можно изменять.
#define M_U32_TO_P(point)               ( ( uint32_t * )point )

// Преобразует enum class в uint8_t.
#define M_EC_TO_U8(ENUM_VALUE)          ( ( uint8_t )ENUM_VALUE )

// Преобразует enum class в uint32_t.
#define M_EC_TO_U32(ENUM_VALUE)         ( ( uint32_t )ENUM_VALUE )


// Возвращаем размер массива.
#define M_SIZE_ARRAY(ARRAY)             (sizeof(ARRAY)/sizeof(ARRAY[0]))

// Служит для записи таблицы векторов прерываний.
#define M_ISR_TO_CONST_P_VOID(POINT)    ((void*)(POINT))

//**********************************************************************
//                    Для связи с используемой OS.
//**********************************************************************

// Тип переменной-буфера, в которую будет создан mutex.
#define USER_OS_STATIC_MUTEX_BUFFER                         StaticSemaphore_t
// Данные, которыми будет заполнена переменная-буффер при старте.
#define USER_OS_STATIC_MUTEX_BUFFER_INIT_VALUE                  \
{                                                               \
    .pvDummy1 = {nullptr, nullptr, nullptr},                    \
    .u = {                                                      \
        .pvDummy2 = NULL,                                       \
    },                                                          \
    .xDummy3 = { { 0,nullptr, { 0,{ nullptr, nullptr } } },     \
                 { 0,nullptr, { 0,{ nullptr, nullptr } } } },   \
    .uxDummy4 = { 0, 0, 0 },                                    \
    .ucDummy5 = { 0, 0},                                        \
    .ucDummy6 = 0                                               \
}

// Тип переменной mutex-а, который будет создан статически и в него будут помещены данные.
#define USER_OS_STATIC_MUTEX                                SemaphoreHandle_t
// Метод должен создать в заранее выделенной переменной-буфере mutex.
#define USER_OS_STATIC_MUTEX_CREATE(P_BUF)                  xSemaphoreCreateMutexStatic( P_BUF )
// Метод должен принять mutex в потоке.
// Вне зависимости от успеха операции возвращается код окончания операции.
// Параметр EXPECTATION (ожидание mutex-а) выставляется в системных тиках операционной системы.
// Должно вернуть true если успех и false - есл провал.
#define USER_OS_TAKE_MUTEX(MUTEX,EXPECTATION)               xSemaphoreTake( MUTEX, ( TickType_t )EXPECTATION )
// Метод должен отдать mutex в потоке.
// Метод ничего не возвращает.
#define USER_OS_GIVE_MUTEX(MUTEX)                           xSemaphoreGive( MUTEX )


// Тип переменной-буфера, в которую будет создан бинарный semaphore.
#define USER_OS_STATIC_BIN_SEMAPHORE_BUFFER                 StaticSemaphore_t
// Данные, которыми будет заполнена переменная-буффер при старте.
#define USER_OS_STATIC_BIN_SEMAPHORE_BUFFER_INIT_VALUE      USER_OS_STATIC_MUTEX_BUFFER_INIT_VALUE
// Тип переменной бинарного semaphore-а, который будет создан статически и в него будут помещены данные.
#define USER_OS_STATIC_BIN_SEMAPHORE                        SemaphoreHandle_t
// Метод должен создать в заранее выделенной переменной-буфере бинарный semaphore.
#define USER_OS_STATIC_BIN_SEMAPHORE_CREATE(P_BUF)          xSemaphoreCreateBinaryStatic( P_BUF )
// Тип переменной, которая содержит в себе указания для метода выдачи семафора и прерывания о том,
// стоит ли удерживать данную задачу от вытеснения разблокированной с большим приоритетом (
// если вдруг симафор таковую разблокирует) или нет.
#define USER_OS_PRIO_TASK_WOKEN                             BaseType_t
// Метод должен выдать семафор из прерывания.
#define USER_OS_GIVE_BIN_SEMAPHORE_FROM_ISR(P_BUF,P_PRIO)   xSemaphoreGiveFromISR( P_BUF, P_PRIO )
// Метод должен принять симафор в потоке.
// Вне зависимости от успеха операции возвращается код окончания операции.
// Параметр EXPECTATION (ожидание семафора) выставляется в системных тиках операционной системы.
// Должно вернуть true если успех и false - есл провал.
#define USER_OS_TAKE_BIN_SEMAPHORE(SEMAPHORE,EXPECTATION)   (bool)( xSemaphoreTake( SEMAPHORE, ( TickType_t )EXPECTATION ) )

#define USER_OS_DELAY_MS(DELAY_MS)                          vTaskDelay( (TickType_t)DELAY_MS )
//**********************************************************************
//                          Для модуля PORT.
//**********************************************************************

/*
 * Раскомментировать данный define, если требуется в случае наличия блокировки порта пропустить повторную
 * переинициализацию.
 * Без данного define, при обнаружении флага блокировки порта, повторная переинициализация производится, т.к.,
 * возможно, пользователь хочет переинициализировать не заблокированные выводы.
 */
//#define NO_REINIT_PORT_AFTER_LOOKING

#if defined(STM32F205RB)|defined(STM32F205RC)|defined(STM32F205RE)\
	|defined(STM32F205RF)|defined(STM32F205RG)
#define PORTA
#define PORTB
#define PORTC
#define PORTD
#define PORTH
#define STM32_F2_PORT_COUNT				5
#else
	#error Не выбран микроконтроллер. Выбирете модель микрококнтроллера. Например, STM32F205RC.
#endif
