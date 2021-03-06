cmake_minimum_required (VERSION 3.12)


set(MCU stm32h735xx)

# include other cmake modules as needed

message(FATAL_ERROR "Change the board project name - then delete this line")
project(Boardv4)


#Stratify Labs assigned hardware ID
message(FATAL_ERROR "Update the hardware id and kernel address - then delete this line")
set(HARDWARE_ID 0x00000031)
set(BOOT_START_ADDRESS 0x08000000)
set(KERNEL_START_ADDRESS 0x08040000)
set(BOOT_LINKER_FILE linker-rom.ld)
set(KERNEL_LINKER_FILE ${BOOT_LINKER_FILE})

set(DEFINITIONS
	__BOOT_START_ADDRESS=${BOOT_START_ADDRESS}
	__KERNEL_START_ADDRESS=${KERNEL_START_ADDRESS}
	__${MCU}
  MCU_ARCH_STM32
	)


message(FATAL_ERROR "Choose your boot libraries - then delete this line")

set(BOOT_LIBRARIES
	tinycrypt_kernel
	uECC_kernel
	StratifyOS_${MCU}
	StratifyOS_boot
	StratifyOS_usbd
	StratifyOS_${MCU})

message(FATAL_ERROR "Choose your kernel libraries - then delete this line")
set(KERNEL_LIBRARIES
	tinycrypt_kernel
	uECC_kernel
	fatfs
	StratifyOS_${MCU}
	StratifyOS_sys
	StratifyOS_usbd
	newlib_libc
	newlib_liba_vsprintf
	newlib_liba_vprintf
	newlib_liba_vsiprintf
	newlib_liba_viprintf
	newlib_libc
	newlib_libm
	StratifyOS_sys
	newlib_libc
	newlib_liba_vsprintf
	newlib_liba_vprintf
	newlib_liba_vsiprintf
	newlib_liba_viprintf
	newlib_libc
	newlib_libm
	StratifyOS_sys
	)

set(LDSCRIPT_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/ldscripts/stm32h735xg-rom.ld
	${CMAKE_CURRENT_SOURCE_DIR}/ldscripts/stm32h7xx.ld
	${CMAKE_CURRENT_SOURCE_DIR}/ldscripts/stm32-common.ld
	)

sos_sdk_add_subdirectory(KERNEL_SOURCELIST ${CMAKE_CURRENT_SOURCE_DIR}/src)
sos_sdk_add_subdirectory(BOOT_SOURCELIST ${CMAKE_CURRENT_SOURCE_DIR}/boot)

sos_sdk_bsp_target(RELEASE ${PROJECT_NAME} "" release ${SOS_ARCH})
sos_sdk_bsp_target(DEBUG ${PROJECT_NAME} "" debug ${SOS_ARCH})

add_executable(${RELEASE_TARGET})

message(FATAL_ERROR "Update compile options as needed - then delete this line")
target_include_directories(${RELEASE_TARGET}
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/src
	include
	)

target_compile_options(${RELEASE_TARGET} PUBLIC -Os)

target_link_directories(${RELEASE_TARGET}
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/ldscripts)

set_target_properties(${RELEASE_TARGET}
	PROPERTIES
	LINK_FLAGS
	"-u symbols_table -T${KERNEL_LINKER_FILE}"
	)

sos_sdk_bsp_target(BOOT_RELEASE ${PROJECT_NAME} boot release ${SOS_ARCH})
sos_sdk_bsp_target(BOOT_DEBUG ${PROJECT_NAME} boot debug ${SOS_ARCH})

add_executable(${BOOT_RELEASE_TARGET})
sos_sdk_copy_target(${RELEASE_TARGET} ${BOOT_RELEASE_TARGET})

target_sources(${RELEASE_TARGET}
	PUBLIC
	${KERNEL_SOURCELIST}
	${CMAKE_CURRENT_SOURCE_DIR}/sl_settings.json
	${CMAKE_CURRENT_SOURCE_DIR}/../README.md
	${LDSCRIPT_SOURCES}
	)


target_compile_definitions(${RELEASE_TARGET}
	PUBLIC
	${DEFINITIONS}
	VECTOR_TABLE_ADDRESS=${KERNEL_START_ADDRESS}
	_IS_BOOT=0
	)

add_executable(${DEBUG_TARGET})
sos_sdk_copy_target(${RELEASE_TARGET} ${DEBUG_TARGET})

target_compile_definitions(${BOOT_RELEASE_TARGET}
	PUBLIC
	${DEFINITIONS}
	VECTOR_TABLE_ADDRESS=${BOOT_START_ADDRESS}
	_IS_BOOT=1
	)

target_sources(${BOOT_RELEASE_TARGET}
	PUBLIC
	${BOOT_SOURCELIST}
	)


add_executable(${BOOT_DEBUG_TARGET})
sos_sdk_copy_target(${BOOT_RELEASE_TARGET} ${BOOT_DEBUG_TARGET})

sos_sdk_bsp("${BOOT_RELEASE_OPTIONS}" ${HARDWARE_ID} ${BOOT_START_ADDRESS} "${BOOT_LIBRARIES}")
sos_sdk_bsp("${BOOT_DEBUG_OPTIONS}" ${HARDWARE_ID} ${BOOT_START_ADDRESS} "${BOOT_LIBRARIES}")

sos_sdk_bsp("${RELEASE_OPTIONS}" ${HARDWARE_ID} ${KERNEL_START_ADDRESS} "${KERNEL_LIBRARIES}")
sos_sdk_bsp("${DEBUG_OPTIONS}" ${HARDWARE_ID} ${KERNEL_START_ADDRESS} "${KERNEL_LIBRARIES}")


