#**********************************************************************
# Для сборки module_stm32f2_low_level.
#**********************************************************************
STM32_F2_API_H_FILE			:= $(shell find module_stm32f2_low_level/ -maxdepth 3 -type f -name "*.h" )
STM32_F2_API_CPP_FILE		:= $(shell find module_stm32f2_low_level/ -maxdepth 3 -type f -name "*.cpp" )
STM32_F2_API_DIR			:= $(shell find module_stm32f2_low_level/ -maxdepth 3 -type d -name "*" )
STM32_F2_API_PATH			:= $(addprefix -I, $(STM32_F2_API_DIR))
STM32_F2_API_OBJ_FILE		:= $(addprefix build/obj/, $(STM32_F2_API_CPP_FILE))
STM32_F2_API_OBJ_FILE		:= $(patsubst %.cpp, %.o, $(STM32_F2_API_OBJ_FILE))

build/obj/module_stm32f2_low_level/%.o:	module_stm32f2_low_level/%.cpp $(USER_CFG_H_FILE) $(MK_INTER_H_FILE)
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) $(STM32_F2_API_PATH) $(USER_CFG_PATH) $(STM32_F2_API_OPTIMIZATION) $(MK_INTER_PATH) $(FREE_RTOS_PATH) -c $< -o $@

# Добавляем к общим переменным проекта.
PROJECT_PATH			+= $(STM32_F2_API_PATH)
PROJECT_OBJ_FILE		+= $(STM32_F2_API_OBJ_FILE)