cmake_minimum_required(VERSION 3.27)

add_library(freertos_config INTERFACE)
target_compile_definitions(freertos_config INTERFACE projCOVERAGE_TEST=0)
set(FREERTOS_HEAP "4" CACHE STRING "" FORCE)
set(FREERTOS_PORT "GCC_ARM_CM4F" CACHE STRING "" FORCE)

CPMAddPackage("gh:FreeRTOS/FreeRTOS-Kernel#V11.1.0")
CPMAddPackage("gh:ETLCPP/etl#20.38.13")
