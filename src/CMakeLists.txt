cmake_minimum_required(VERSION 3.27)

include(nrf5/nrf5)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    main.cpp
    sys.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
    etl
)

### START NRF5 SDK ###
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # ${NRF5_SDK_PATH}/modules/nrfx/mdk/gcc_startup_nrf52.S
    # ${NRF5_SDK_PATH}/modules/nrfx/mdk/system_nrf52.c
    ${NRF5_SDK_PATH}/modules/nrfx/mdk/gcc_startup_nrf52840.S
    ${NRF5_SDK_PATH}/modules/nrfx/mdk/system_nrf52840.c
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    ${NRF5_SDK_PATH}/components/libraries/delay
    ${NRF5_SDK_PATH}/modules/nrfx
    ${NRF5_SDK_PATH}/modules/nrfx/hal
    ${NRF5_SDK_PATH}/modules/nrfx/mdk
    ${NRF5_SDK_PATH}/modules/nrfx/templates
    ${NRF5_SDK_PATH}/components/toolchain/cmsis/include
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC
    NRF52840_XXAA
)
### END NRF5 SDK ###

target_link_options(${CMAKE_PROJECT_NAME} PUBLIC
    "LINKER:-Map=${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME}.map,--cref"
    -T ${CMAKE_CURRENT_LIST_DIR}/generic_gcc_nrf52.ld
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/generic_gcc_nrf52.ld)
