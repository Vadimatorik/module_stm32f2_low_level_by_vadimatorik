/* 
 * В данный файл описывает порядок расположения секций в памяти
 * микроконтроллера.
 */
/* Вершина стека (этот адрес будет размещен в таблице векторов прерываний). */
_stack = ORIGIN(RAM1) + LENGTH(RAM1) - 1;

SECTIONS
{
  /* Таблица векторов прерываний, выравниванная по 4 байта (во flash). */
  .irq_table :
  {
    . = ALIGN(4);               /* Задаем счетчику адрес кратный 4-м байтам. */
    KEEP(*(.irq_table))         /* Отключаем оптимизацию сборщика мусора (KEEP). */
    /* Иначе говоря, даже если массив векторов прерываний
       не используется программой, его обязательно следует разместить во flash. */	
    . = ALIGN(4);
  } >FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text)                    /* Основная программа во flash + что-то служебное. */
    *(.text*)          
    *(.glue_7)        
    *(.glue_7t)        
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);	
    _etext = .;                 /* Обозначение окончания секции кода. */
  } >FLASH

  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         		/* Осходные данные глобальных элементов с начальными не нулевыми значениями.*/
    *(.rodata*)        
    . = ALIGN(4);
  } >FLASH

  /* ARM magic sections */
  /* Не ясно, для чего нужная секция, но без нее не собирается. */
  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH

  /* Данные для служебных библиотек и инициализаторов C++ */
  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

  /* Изменяемые данные, в RAM1 (копируются из flash). */
  _sidata = LOADADDR(.data);           /* Получаем адрес дубликата исходных значений изменяемых данных (расположенных в RAM1). */
                   
 .data : 
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RAM1 AT> FLASH

  /* Данные в RAM1, изначально 0 (заполняются нулями при инициализации). */
  .bss (NOLOAD) :
  {
    . = ALIGN(4);
    __bss_start__ = .;          /* Получаем указатели на .bss область памяти в RAM1. */
    *(.bss_begin .bss_begin.*)
    *(.bss .bss.*)
    *(.bss_end .bss_end.*)
    *(.noinit .noinit.*) 
    *(COMMON)			/* Не инициализированные глобальные переменных тоже пусть в bss будут. */
    . = ALIGN(4);
    __bss_end__ = .;
  } >RAM1

  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}


