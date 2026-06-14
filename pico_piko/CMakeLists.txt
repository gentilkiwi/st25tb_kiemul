# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 15_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

set(PROJECT_NAME st25tb_kameleon_pico_piko)
set(PROG_VERSION "0.1")

set(ST25TB_DIRECTORY ../program)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(st25tb_kameleon_pico_piko C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_compile_options(-Werror -Wall -Wextra -Wnull-dereference)

# Add executable. Default name is the project name, version 0.1

add_executable(${PROJECT_NAME} kmain.c
    ${ST25TB_DIRECTORY}/board.c
    ${ST25TB_DIRECTORY}/modes.c
    ${ST25TB_DIRECTORY}/leds.c
    ${ST25TB_DIRECTORY}/slots.c
    ${ST25TB_DIRECTORY}/trf7970a.c
    ${ST25TB_DIRECTORY}/uart.c
    
    ${ST25TB_DIRECTORY}/modes/cli.c
    ${ST25TB_DIRECTORY}/modes/detect.c
    ${ST25TB_DIRECTORY}/modes/emulate.c
    ${ST25TB_DIRECTORY}/modes/field.c
    ${ST25TB_DIRECTORY}/modes/learn.c
    ${ST25TB_DIRECTORY}/modes/rewrite.c
    ${ST25TB_DIRECTORY}/modes/select.c
    ${ST25TB_DIRECTORY}/modes/tear.c
    ${ST25TB_DIRECTORY}/modes/unk.c
    
    ${ST25TB_DIRECTORY}/modes/cli/cli_14a.c
    ${ST25TB_DIRECTORY}/modes/cli/cli_card.c
    ${ST25TB_DIRECTORY}/modes/cli/cli_config.c
    ${ST25TB_DIRECTORY}/modes/cli/cli_data.c
    ${ST25TB_DIRECTORY}/modes/cli/cli_dump.c
    ${ST25TB_DIRECTORY}/modes/cli/cli_ref.c
    ${ST25TB_DIRECTORY}/modes/cli/cli_slot.c
    ${ST25TB_DIRECTORY}/modes/cli/cli_std.c
    
    ${ST25TB_DIRECTORY}/st25tb/st25tb.c
    ${ST25TB_DIRECTORY}/st25tb/st25tb_initiator.c
    ${ST25TB_DIRECTORY}/st25tb/st25tb_target.c
    ${ST25TB_DIRECTORY}/st25tb/st25tb_utils.c
    
    ${ST25TB_DIRECTORY}/14a/14a.c
    ${ST25TB_DIRECTORY}/14a/14a3_initiator.c
    ${ST25TB_DIRECTORY}/14a/14a4_initiator.c
    ${ST25TB_DIRECTORY}/14a/14a3_target.c
)

pico_set_program_name(${PROJECT_NAME} ${PROJECT_NAME})
pico_set_program_description(${PROJECT_NAME} "st25tb_kameleon on Raspberry Pi Pico")
pico_set_program_version(${PROJECT_NAME} ${PROG_VERSION})
pico_set_program_url(${PROJECT_NAME} "https://github.com/gentilkiwi/st25tb_kiemul")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(${PROJECT_NAME} false)
pico_enable_stdio_usb(${PROJECT_NAME} true)

pico_set_linker_script(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/memmap_rp2040_2M_reserved.ld)

# Add the standard library to the build
target_link_libraries(${PROJECT_NAME}
        pico_stdlib
        pico_unique_id
        hardware_spi
        hardware_flash
        hardware_adc
        pico_rand
)

# Add the standard include files to the build
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${ST25TB_DIRECTORY}
)

if(PROJECT_NAME)
    target_compile_definitions(${PROJECT_NAME} PRIVATE PROG_NAME="${PROJECT_NAME}")
endif()

if(PROG_VERSION)
    target_compile_definitions(${PROJECT_NAME} PRIVATE PROG_VERSION="${PROG_VERSION}")
endif()

# pico_add_extra_outputs(${PROJECT_NAME})
pico_add_hex_output(${PROJECT_NAME})
pico_add_uf2_output(${PROJECT_NAME})
