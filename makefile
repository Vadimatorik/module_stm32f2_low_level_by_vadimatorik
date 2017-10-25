#**********************************************************************
# Для сборки stm32f2_api.
#**********************************************************************
STM32_F2_API_H_FILE	:= $(shell find stm32f2_api/ -maxdepth 3 -type f -name "*.h" )
STM32_F2_API_CPP_FILE	:= $(shell find stm32f2_api/ -maxdepth 3 -type f -name "*.cpp" )
STM32_F2_API_DIR	:= $(shell find stm32f2_api/ -maxdepth 3 -type d -name "*" )
STM32_F2_API_PATH	:= $(addprefix -I, $(STM32_F2_API_DIR))
STM32_F2_API_OBJ_FILE	:= $(addprefix build/obj/, $(STM32_F2_API_CPP_FILE))
STM32_F2_API_OBJ_FILE	:= $(patsubst %.cpp, %.o, $(STM32_F2_API_OBJ_FILE))

build/obj/stm32f2_api/%.o:	stm32f2_api/%.cpp $(USER_CFG_H_FILE) $(FREE_RTOS_H_FILE) $(MK_INTER_H_FILE)
	@echo [CPP] $<
	@mkdir -p $(dir $@)
	@$(CPP) $(CPP_FLAGS) $(STM32_F2_API_PATH) $(USER_CFG_PATH) $(FREE_RTOS_PATH) $(STM32_F2_API_OPTIMIZATION) $(MK_INTER_PATH) -c $< -o $@

# Добавляем к общим переменным проекта.
PROJECT_PATH			+= $(STM32_F2_API_PATH)
PROJECT_OBJ_FILE		+= $(STM32_F2_API_OBJ_FILE)