cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME st25tb_kameleon_stm32_hydrabus)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

set(ST25TB_DIRECTORY ../program)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ${ST25TB_DIRECTORY}/board.c
    ${ST25TB_DIRECTORY}/modes.c
    ${ST25TB_DIRECTORY}/leds.c
    ${ST25TB_DIRECTORY}/slots.c
    ${ST25TB_DIRECTORY}/references.c
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

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    ${ST25TB_DIRECTORY}
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.hex
    # COMMAND ${CMAKE_OBJCOPY} -O srec   $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.srec
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
