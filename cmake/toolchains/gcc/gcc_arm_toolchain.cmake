cmake_minimum_required(VERSION 3.23)

message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

include(CMakeForceCompiler)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

option(GCC_TOOLCHAIN_PATH "Location of GCC toolchain" "")
option(TOOLCHAIN_ENABLE_LTO "Use Linker Time Optimization globally" OFF)

if(NOT "${GCC_TOOLCHAIN_PATH}" STREQUAL "")
  set(ENV{GCC_TOOLCHAIN_PATH} "${GCC_TOOLCHAIN_PATH}")
endif()

if(${TOOLCHAIN_ENABLE_LTO})
  set(ENV{_TOOLCHAIN_ENABLE_LTO} "${TOOLCHAIN_ENABLE_LTO}")
endif()

# Find GCC for ARM
include("${CMAKE_CURRENT_LIST_DIR}/find_gcc.cmake")
find_gcc_compiler(GCC_COMPILER_CC arm-none-eabi-gcc)
find_gcc_compiler(GCC_COMPILER_CXX arm-none-eabi-g++)
find_gcc_compiler(GCC_COMPILER_ASM arm-none-eabi-gcc)

get_filename_component(GCC_TOOLCHAIN_PATH "${GCC_COMPILER_CC}" DIRECTORY)

# Specify the compiler
set(CMAKE_C_COMPILER ${GCC_COMPILER_CC} CACHE FILEPATH "GCC C compiler" FORCE)
set(CMAKE_CXX_COMPILER ${GCC_COMPILER_CXX} CACHE FILEPATH "GCC C++ compiler" FORCE)
set(CMAKE_ASM_COMPILER ${GCC_COMPILER_ASM} -x assembler-with-cpp CACHE FILEPATH "GCC ASM compiler" FORCE)

# Add compiler tools
set(GCC_OBJCOPY ${GCC_TOOLCHAIN_PATH}/arm-none-eabi-objcopy CACHE INTERNAL "GCC objcopy tool")
set(GCC_OBJDUMP ${GCC_TOOLCHAIN_PATH}/arm-none-eabi-objdump CACHE INTERNAL "GCC objdump tool")
set(GCC_NM ${GCC_TOOLCHAIN_PATH}/arm-none-eabi-nm CACHE INTERNAL "GCC nm tool")
set(GCC_SIZE ${GCC_TOOLCHAIN_PATH}/arm-none-eabi-size CACHE INTERNAL "GCC size tool")

# Add target system root to cmake find path
set(CMAKE_SYSROOT ${GCC_TOOLCHAIN_PATH}/../arm-none-eabi)
get_filename_component(CMAKE_FIND_ROOT_PATH "${GCC_TOOLCHAIN_PATH}" DIRECTORY)

# Don't look for executable in target system prefix
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# If the user specifies to use Linker Time optimization, enable it globally
if(DEFINED ENV{_TOOLCHAIN_ENABLE_LTO})
  cmake_policy(SET CMP0069 NEW)
  set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

# -m = ARM GCC Flags https://gcc.gnu.org/onlinedocs/gcc/ARM-Options.html
# -D preprocessor #define
# -f = GCC Flags
# https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html
# https://gcc.gnu.org/onlinedocs/gcc/Code-Gen-Options.html
# https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#Optimize-Options
# https://gcc.gnu.org/onlinedocs/gcc/C-Dialect-Options.html#C-Dialect-Options
# https://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html
set(GCC_ASM_FLAGS ${GCC_ASM_FLAGS}
#   "-D__STARTUP_CLEAR_BSS"
#   "-mapcs" # Synonym for -mapcs-frame, generate stack frame that is compliant with the ARM procedure call standard for all functions
#   "-fno-common" # Default setting, specifies compiler placement for uninitialized global variables to be in BSS
#   "-ffunction-sections" # Place each function item into its own section in the output file, this helps the linker optimize code
#   "-ffreestanding" # Asserts that the target is a freestanding environment, ie one which the standard lib may not exist
#   "-fno-builtin" # Do not recognize built in function that do not begin with __buildin_ as prefix
)

set(GCC_C_FLAGS ${GCC_C_FLAGS}
#   "-DPRINTF_FLOAT_ENABLE=0"
#   "-DSCANF_FLOAT_ENABLE=0"
#   "-DPRINTF_ADVANCED_ENABLE=0"
#   "-DSCANF_ADVANCED_ENABLE=0"
)

set(GCC_CXX_FLAGS ${GCC_CXX_FLAGS}
#   "-Wno-register"
#   "-fno-threadsafe-statics" # reduce flash by making statics/singleton not thread safe, since we arent using a threaded system
    "-fpermissive"
)

set(GCC_COMMON_C_CXX_FLAGS
#   # "--specs=nosys.specs"
#   "--specs=nano.specs"
#   "-mapcs" # Synonym for -mapcs-frame, generate stack frame that is compliant with the ARM procedure call standard for all functions
#   "-MMD"
#   "-MP" # This option instructs CPP to add a phony target for each dependency other than the main file
#   "-fno-common" # Default setting, specifies compiler placement for uninitialized global variables to be in BSS
#   "-ffunction-sections" # Place each function item into its own section in the output file, this helps the linker optimize code
#   "-fdata-sections" # Place each data item into its own section in the output file, this helps the linker optimize code
#   "-ffreestanding" # Asserts that the target is a freestanding environment, ie one which the standard lib may not exist
#   "-fno-builtin" # Do not recognize built in function that do not begin with __buildin_ as prefix
)

list(APPEND GCC_C_FLAGS ${GCC_COMMON_C_CXX_FLAGS})
list(APPEND GCC_CXX_FLAGS ${GCC_COMMON_C_CXX_FLAGS})

# # Debug only flags for ASM
# set(GCC_ASM_DEBUG_FLAGS ${GCC_ASM_DEBUG_FLAGS}
#   "-g"
# )

# # Debug only flags for C and CXX
# set(GCC_COMMON_C_CXX_DEBUG_FLAGS ${GCC_COMMON_C_CXX_DEBUG_FLAGS}
#   "-g"
# )

# # Release only flags for ASM
# set(GCC_ASM_RELEASE_FLAGS ${GCC_ASM_RELEASE_FLAGS}
# )

# # Release only flags for C and CXX
# set(GCC_COMMON_C_CXX_RELEASE_FLAGS ${GCC_COMMON_C_CXX_RELEASE_FLAGS}
# )

# add_compile_definitions(
#   "$<$<CONFIG:DEBUG>:DEBUG>"
#   "$<$<CONFIG:RELEASE>:NDEBUG>"
# )

add_compile_options(
  "$<$<COMPILE_LANGUAGE:ASM>:${GCC_ASM_FLAGS}>" # Add ASM flags
  "$<$<COMPILE_LANGUAGE:C>:${GCC_C_FLAGS}>" # Add C flags
  "$<$<COMPILE_LANGUAGE:CXX>:${GCC_CXX_FLAGS}>" # Add CXX flags
  "$<$<AND:$<CONFIG:DEBUG>,$<COMPILE_LANGUAGE:ASM>>:${GCC_ASM_DEBUG_FLAGS}>" # Add ASM debug flags
  "$<$<AND:$<CONFIG:DEBUG>,$<COMPILE_LANGUAGE:C,CXX>>:${GCC_COMMON_C_CXX_DEBUG_FLAGS}>" # Add common C/CXX debug flags
  "$<$<AND:$<CONFIG:RELEASE>,$<COMPILE_LANGUAGE:ASM>>:${GCC_ASM_RELEASE_FLAGS}>" # Add ASM release flags
  "$<$<AND:$<CONFIG:RELEASE>,$<COMPILE_LANGUAGE:C,CXX>>:${GCC_COMMON_C_CXX_RELEASE_FLAGS}>" # Add common C/CXX release flags
)

# # GCC Link options https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html
# # LINKER inserts a -Wl,option where needed
# # Spec files, --specs:  https://gcc.gnu.org/onlinedocs/gcc/Spec-Files.html
add_link_options(
#   "--specs=nano.specs"
#   # "--specs=nosys.specs"
#   # "LINKER:--start-group"
#   "-lc" # link with libc.a, the standard c lib
#   "-lm" # link with libm.a, the math lib
#   "-lnosys" # link against stub version of std/posix functions
#   # "LINKER:--end-group"
#   "-fno-common" # Default setting, specifies compiler placement for uninitialized global variables to be in BSS
#   "-ffunction-sections" # Place each function item into its own section in the output file, this helps the linker optimize code
#   "-fdata-sections" # Place each data item into its own section in the output file, this helps the linker optimize code
#   "-ffreestanding" # Asserts that the target is a freestanding environment, ie one which the standard lib may not exist
#   "-fno-builtin" # Do not recognize built in function that do not begin with __buildin_ as prefix
#   "-static" # prevents linking with shared libraries, only allow static linking
#   "-mapcs"
#   "LINKER:--print-memory-usage"
#   "LINKER:--gc-sections"
#   "LINKER:--allow-multiple-definition"
  "LINKER:--no-warn-rwx-segments" # Disable "has a LOAD segment with RWX permissions" warning, only in gcc 12 or greater
)

# add_link_options(
#   "$<$<CONFIG:Debug>:-g>"
# )
