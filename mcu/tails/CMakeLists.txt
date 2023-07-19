cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/usr/share/pico-sdk")
set(PICO_BOARD pico_w CACHE STRING "Board type")
# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(picow-ludeled C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)
set(PICO_CXX_ENABLE_RTTI 1)
pico_sdk_init()

add_executable(picow-ludeled)

# Build ws2812 PIO
pico_generate_pio_header(picow-ludeled
	${CMAKE_CURRENT_LIST_DIR}/ws2812/ws2812.pio
	OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/ws2812/generated
)

# Build application
target_sources(picow-ludeled PRIVATE
	src/main.cpp
	ws2812/ws281x.cpp
	ws2812/led_matrix.cpp
	# dhcpserver/dhcpserver.c
)

target_include_directories(picow-ludeled PRIVATE
	inc
	ws2812
	ws2812/generated
)

# Debug output - Enable for USB CDC and disable for on-board UART
# You can change these around (or even have both active) by changing the 1s and 0s
pico_enable_stdio_usb(picow-ludeled 1)
pico_enable_stdio_uart(picow-ludeled 1)

# Build dependencies and link application
pico_add_extra_outputs(picow-ludeled)
target_link_libraries(picow-ludeled
	pico_stdlib
	hardware_pio
	pico_cyw43_arch_lwip_threadsafe_background
)
