cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(VibrationMonitor ASM C CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(CPM)

add_subdirectory(third_party)
add_subdirectory(src)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/zephyr/out DESTINATION ${CMAKE_SOURCE_DIR}/build/out)

add_custom_command(TARGET app POST_BUILD
    COMMAND "${CMAKE_COMMAND}" --install "${CMAKE_BINARY_DIR}"
    COMMENT "Running post-build install"
)
