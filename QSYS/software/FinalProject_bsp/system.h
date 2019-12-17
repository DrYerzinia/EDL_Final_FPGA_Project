/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'cpu' in SOPC Builder design 'EDL_Final'
 * SOPC Builder design path: ../../EDL_Final.sopcinfo
 *
 * Generated: Mon Dec 16 20:41:39 MST 2019
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x08000820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 100000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1c
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x04000020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 100000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x1c
#define ALT_CPU_NAME "cpu"
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x02000000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x08000820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 100000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x1c
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x04000020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x1c
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x02000000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_UART
#define __ALTERA_NIOS2_GEN2
#define __ALTERA_ONCHIP_FLASH
#define __ALTERA_UP_AVALON_VIDEO_DMA_CONTROLLER


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "MAX 10"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart"
#define ALT_STDERR_BASE 0x8001090
#define ALT_STDERR_DEV jtag_uart
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart"
#define ALT_STDIN_BASE 0x8001090
#define ALT_STDIN_DEV jtag_uart
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart"
#define ALT_STDOUT_BASE 0x8001090
#define ALT_STDOUT_DEV jtag_uart
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "EDL_Final"


/*
 * ble_uart configuration
 *
 */

#define ALT_MODULE_CLASS_ble_uart altera_avalon_uart
#define BLE_UART_BASE 0x80000c0
#define BLE_UART_BAUD 9600
#define BLE_UART_DATA_BITS 8
#define BLE_UART_FIXED_BAUD 1
#define BLE_UART_FREQ 100000000
#define BLE_UART_IRQ 1
#define BLE_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define BLE_UART_NAME "/dev/ble_uart"
#define BLE_UART_PARITY 'N'
#define BLE_UART_SIM_CHAR_STREAM ""
#define BLE_UART_SIM_TRUE_BAUD 0
#define BLE_UART_SPAN 32
#define BLE_UART_STOP_BITS 1
#define BLE_UART_SYNC_REG_DEPTH 2
#define BLE_UART_TYPE "altera_avalon_uart"
#define BLE_UART_USE_CTS_RTS 0
#define BLE_UART_USE_EOP_REGISTER 0


/*
 * button configuration
 *
 */

#define ALT_MODULE_CLASS_button altera_avalon_pio
#define BUTTON_BASE 0x8001070
#define BUTTON_BIT_CLEARING_EDGE_REGISTER 0
#define BUTTON_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BUTTON_CAPTURE 0
#define BUTTON_DATA_WIDTH 2
#define BUTTON_DO_TEST_BENCH_WIRING 0
#define BUTTON_DRIVEN_SIM_VALUE 0
#define BUTTON_EDGE_TYPE "NONE"
#define BUTTON_FREQ 100000000
#define BUTTON_HAS_IN 1
#define BUTTON_HAS_OUT 0
#define BUTTON_HAS_TRI 0
#define BUTTON_IRQ -1
#define BUTTON_IRQ_INTERRUPT_CONTROLLER_ID -1
#define BUTTON_IRQ_TYPE "NONE"
#define BUTTON_NAME "/dev/button"
#define BUTTON_RESET_VALUE 0
#define BUTTON_SPAN 16
#define BUTTON_TYPE "altera_avalon_pio"


/*
 * encoder_left configuration
 *
 */

#define ALT_MODULE_CLASS_encoder_left altera_avalon_pio
#define ENCODER_LEFT_BASE 0x8001030
#define ENCODER_LEFT_BIT_CLEARING_EDGE_REGISTER 0
#define ENCODER_LEFT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ENCODER_LEFT_CAPTURE 0
#define ENCODER_LEFT_DATA_WIDTH 32
#define ENCODER_LEFT_DO_TEST_BENCH_WIRING 0
#define ENCODER_LEFT_DRIVEN_SIM_VALUE 0
#define ENCODER_LEFT_EDGE_TYPE "NONE"
#define ENCODER_LEFT_FREQ 100000000
#define ENCODER_LEFT_HAS_IN 1
#define ENCODER_LEFT_HAS_OUT 0
#define ENCODER_LEFT_HAS_TRI 0
#define ENCODER_LEFT_IRQ -1
#define ENCODER_LEFT_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ENCODER_LEFT_IRQ_TYPE "NONE"
#define ENCODER_LEFT_NAME "/dev/encoder_left"
#define ENCODER_LEFT_RESET_VALUE 0
#define ENCODER_LEFT_SPAN 16
#define ENCODER_LEFT_TYPE "altera_avalon_pio"


/*
 * encoder_right configuration
 *
 */

#define ALT_MODULE_CLASS_encoder_right altera_avalon_pio
#define ENCODER_RIGHT_BASE 0x8001040
#define ENCODER_RIGHT_BIT_CLEARING_EDGE_REGISTER 0
#define ENCODER_RIGHT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ENCODER_RIGHT_CAPTURE 0
#define ENCODER_RIGHT_DATA_WIDTH 32
#define ENCODER_RIGHT_DO_TEST_BENCH_WIRING 0
#define ENCODER_RIGHT_DRIVEN_SIM_VALUE 0
#define ENCODER_RIGHT_EDGE_TYPE "NONE"
#define ENCODER_RIGHT_FREQ 100000000
#define ENCODER_RIGHT_HAS_IN 1
#define ENCODER_RIGHT_HAS_OUT 0
#define ENCODER_RIGHT_HAS_TRI 0
#define ENCODER_RIGHT_IRQ -1
#define ENCODER_RIGHT_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ENCODER_RIGHT_IRQ_TYPE "NONE"
#define ENCODER_RIGHT_NAME "/dev/encoder_right"
#define ENCODER_RIGHT_RESET_VALUE 0
#define ENCODER_RIGHT_SPAN 16
#define ENCODER_RIGHT_TYPE "altera_avalon_pio"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart altera_avalon_jtag_uart
#define JTAG_UART_BASE 0x8001090
#define JTAG_UART_IRQ 0
#define JTAG_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_NAME "/dev/jtag_uart"
#define JTAG_UART_READ_DEPTH 64
#define JTAG_UART_READ_THRESHOLD 8
#define JTAG_UART_SPAN 8
#define JTAG_UART_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_WRITE_DEPTH 64
#define JTAG_UART_WRITE_THRESHOLD 8


/*
 * led configuration
 *
 */

#define ALT_MODULE_CLASS_led altera_avalon_pio
#define LED_BASE 0x8001060
#define LED_BIT_CLEARING_EDGE_REGISTER 0
#define LED_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_CAPTURE 0
#define LED_DATA_WIDTH 10
#define LED_DO_TEST_BENCH_WIRING 0
#define LED_DRIVEN_SIM_VALUE 0
#define LED_EDGE_TYPE "NONE"
#define LED_FREQ 100000000
#define LED_HAS_IN 0
#define LED_HAS_OUT 1
#define LED_HAS_TRI 0
#define LED_IRQ -1
#define LED_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_IRQ_TYPE "NONE"
#define LED_NAME "/dev/led"
#define LED_RESET_VALUE 0
#define LED_SPAN 16
#define LED_TYPE "altera_avalon_pio"


/*
 * lidar_motor_en configuration
 *
 */

#define ALT_MODULE_CLASS_lidar_motor_en altera_avalon_pio
#define LIDAR_MOTOR_EN_BASE 0x8002040
#define LIDAR_MOTOR_EN_BIT_CLEARING_EDGE_REGISTER 0
#define LIDAR_MOTOR_EN_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LIDAR_MOTOR_EN_CAPTURE 0
#define LIDAR_MOTOR_EN_DATA_WIDTH 1
#define LIDAR_MOTOR_EN_DO_TEST_BENCH_WIRING 0
#define LIDAR_MOTOR_EN_DRIVEN_SIM_VALUE 0
#define LIDAR_MOTOR_EN_EDGE_TYPE "NONE"
#define LIDAR_MOTOR_EN_FREQ 100000000
#define LIDAR_MOTOR_EN_HAS_IN 0
#define LIDAR_MOTOR_EN_HAS_OUT 1
#define LIDAR_MOTOR_EN_HAS_TRI 0
#define LIDAR_MOTOR_EN_IRQ -1
#define LIDAR_MOTOR_EN_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LIDAR_MOTOR_EN_IRQ_TYPE "NONE"
#define LIDAR_MOTOR_EN_NAME "/dev/lidar_motor_en"
#define LIDAR_MOTOR_EN_RESET_VALUE 0
#define LIDAR_MOTOR_EN_SPAN 16
#define LIDAR_MOTOR_EN_TYPE "altera_avalon_pio"


/*
 * lidar_uart configuration
 *
 */

#define ALT_MODULE_CLASS_lidar_uart altera_avalon_uart
#define LIDAR_UART_BASE 0x80010e0
#define LIDAR_UART_BAUD 115200
#define LIDAR_UART_DATA_BITS 8
#define LIDAR_UART_FIXED_BAUD 1
#define LIDAR_UART_FREQ 100000000
#define LIDAR_UART_IRQ 2
#define LIDAR_UART_IRQ_INTERRUPT_CONTROLLER_ID 0
#define LIDAR_UART_NAME "/dev/lidar_uart"
#define LIDAR_UART_PARITY 'N'
#define LIDAR_UART_SIM_CHAR_STREAM ""
#define LIDAR_UART_SIM_TRUE_BAUD 0
#define LIDAR_UART_SPAN 32
#define LIDAR_UART_STOP_BITS 1
#define LIDAR_UART_SYNC_REG_DEPTH 2
#define LIDAR_UART_TYPE "altera_avalon_uart"
#define LIDAR_UART_USE_CTS_RTS 0
#define LIDAR_UART_USE_EOP_REGISTER 0


/*
 * line_detect configuration
 *
 */

#define ALT_MODULE_CLASS_line_detect altera_avalon_pio
#define LINE_DETECT_BASE 0x80010a0
#define LINE_DETECT_BIT_CLEARING_EDGE_REGISTER 0
#define LINE_DETECT_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LINE_DETECT_CAPTURE 0
#define LINE_DETECT_DATA_WIDTH 4
#define LINE_DETECT_DO_TEST_BENCH_WIRING 0
#define LINE_DETECT_DRIVEN_SIM_VALUE 0
#define LINE_DETECT_EDGE_TYPE "NONE"
#define LINE_DETECT_FREQ 100000000
#define LINE_DETECT_HAS_IN 1
#define LINE_DETECT_HAS_OUT 0
#define LINE_DETECT_HAS_TRI 0
#define LINE_DETECT_IRQ -1
#define LINE_DETECT_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LINE_DETECT_IRQ_TYPE "NONE"
#define LINE_DETECT_NAME "/dev/line_detect"
#define LINE_DETECT_RESET_VALUE 0
#define LINE_DETECT_SPAN 16
#define LINE_DETECT_TYPE "altera_avalon_pio"


/*
 * motor_direction configuration
 *
 */

#define ALT_MODULE_CLASS_motor_direction altera_avalon_pio
#define MOTOR_DIRECTION_BASE 0x8001020
#define MOTOR_DIRECTION_BIT_CLEARING_EDGE_REGISTER 0
#define MOTOR_DIRECTION_BIT_MODIFYING_OUTPUT_REGISTER 0
#define MOTOR_DIRECTION_CAPTURE 0
#define MOTOR_DIRECTION_DATA_WIDTH 4
#define MOTOR_DIRECTION_DO_TEST_BENCH_WIRING 0
#define MOTOR_DIRECTION_DRIVEN_SIM_VALUE 0
#define MOTOR_DIRECTION_EDGE_TYPE "NONE"
#define MOTOR_DIRECTION_FREQ 100000000
#define MOTOR_DIRECTION_HAS_IN 0
#define MOTOR_DIRECTION_HAS_OUT 1
#define MOTOR_DIRECTION_HAS_TRI 0
#define MOTOR_DIRECTION_IRQ -1
#define MOTOR_DIRECTION_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MOTOR_DIRECTION_IRQ_TYPE "NONE"
#define MOTOR_DIRECTION_NAME "/dev/motor_direction"
#define MOTOR_DIRECTION_RESET_VALUE 0
#define MOTOR_DIRECTION_SPAN 16
#define MOTOR_DIRECTION_TYPE "altera_avalon_pio"


/*
 * on_button configuration
 *
 */

#define ALT_MODULE_CLASS_on_button altera_avalon_pio
#define ON_BUTTON_BASE 0x8001010
#define ON_BUTTON_BIT_CLEARING_EDGE_REGISTER 0
#define ON_BUTTON_BIT_MODIFYING_OUTPUT_REGISTER 0
#define ON_BUTTON_CAPTURE 0
#define ON_BUTTON_DATA_WIDTH 1
#define ON_BUTTON_DO_TEST_BENCH_WIRING 0
#define ON_BUTTON_DRIVEN_SIM_VALUE 0
#define ON_BUTTON_EDGE_TYPE "NONE"
#define ON_BUTTON_FREQ 100000000
#define ON_BUTTON_HAS_IN 1
#define ON_BUTTON_HAS_OUT 0
#define ON_BUTTON_HAS_TRI 0
#define ON_BUTTON_IRQ -1
#define ON_BUTTON_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ON_BUTTON_IRQ_TYPE "NONE"
#define ON_BUTTON_NAME "/dev/on_button"
#define ON_BUTTON_RESET_VALUE 0
#define ON_BUTTON_SPAN 16
#define ON_BUTTON_TYPE "altera_avalon_pio"


/*
 * onchip_flash_csr configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_flash_csr altera_onchip_flash
#define ONCHIP_FLASH_CSR_BASE 0x8002050
#define ONCHIP_FLASH_CSR_BYTES_PER_PAGE 8192
#define ONCHIP_FLASH_CSR_IRQ -1
#define ONCHIP_FLASH_CSR_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_FLASH_CSR_NAME "/dev/onchip_flash_csr"
#define ONCHIP_FLASH_CSR_READ_ONLY_MODE 0
#define ONCHIP_FLASH_CSR_SECTOR1_ENABLED 1
#define ONCHIP_FLASH_CSR_SECTOR1_END_ADDR 0x7fff
#define ONCHIP_FLASH_CSR_SECTOR1_START_ADDR 0
#define ONCHIP_FLASH_CSR_SECTOR2_ENABLED 1
#define ONCHIP_FLASH_CSR_SECTOR2_END_ADDR 0xffff
#define ONCHIP_FLASH_CSR_SECTOR2_START_ADDR 0x8000
#define ONCHIP_FLASH_CSR_SECTOR3_ENABLED 1
#define ONCHIP_FLASH_CSR_SECTOR3_END_ADDR 0x6ffff
#define ONCHIP_FLASH_CSR_SECTOR3_START_ADDR 0x10000
#define ONCHIP_FLASH_CSR_SECTOR4_ENABLED 0
#define ONCHIP_FLASH_CSR_SECTOR4_END_ADDR 0xffffffff
#define ONCHIP_FLASH_CSR_SECTOR4_START_ADDR 0xffffffff
#define ONCHIP_FLASH_CSR_SECTOR5_ENABLED 0
#define ONCHIP_FLASH_CSR_SECTOR5_END_ADDR 0xffffffff
#define ONCHIP_FLASH_CSR_SECTOR5_START_ADDR 0xffffffff
#define ONCHIP_FLASH_CSR_SPAN 8
#define ONCHIP_FLASH_CSR_TYPE "altera_onchip_flash"


/*
 * onchip_flash_data configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_flash_data altera_onchip_flash
#define ONCHIP_FLASH_DATA_BASE 0x2000000
#define ONCHIP_FLASH_DATA_BYTES_PER_PAGE 8192
#define ONCHIP_FLASH_DATA_IRQ -1
#define ONCHIP_FLASH_DATA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_FLASH_DATA_NAME "/dev/onchip_flash_data"
#define ONCHIP_FLASH_DATA_READ_ONLY_MODE 0
#define ONCHIP_FLASH_DATA_SECTOR1_ENABLED 1
#define ONCHIP_FLASH_DATA_SECTOR1_END_ADDR 0x7fff
#define ONCHIP_FLASH_DATA_SECTOR1_START_ADDR 0
#define ONCHIP_FLASH_DATA_SECTOR2_ENABLED 1
#define ONCHIP_FLASH_DATA_SECTOR2_END_ADDR 0xffff
#define ONCHIP_FLASH_DATA_SECTOR2_START_ADDR 0x8000
#define ONCHIP_FLASH_DATA_SECTOR3_ENABLED 1
#define ONCHIP_FLASH_DATA_SECTOR3_END_ADDR 0x6ffff
#define ONCHIP_FLASH_DATA_SECTOR3_START_ADDR 0x10000
#define ONCHIP_FLASH_DATA_SECTOR4_ENABLED 0
#define ONCHIP_FLASH_DATA_SECTOR4_END_ADDR 0xffffffff
#define ONCHIP_FLASH_DATA_SECTOR4_START_ADDR 0xffffffff
#define ONCHIP_FLASH_DATA_SECTOR5_ENABLED 0
#define ONCHIP_FLASH_DATA_SECTOR5_END_ADDR 0xffffffff
#define ONCHIP_FLASH_DATA_SECTOR5_START_ADDR 0xffffffff
#define ONCHIP_FLASH_DATA_SPAN 458752
#define ONCHIP_FLASH_DATA_TYPE "altera_onchip_flash"


/*
 * peak_1 configuration
 *
 */

#define ALT_MODULE_CLASS_peak_1 altera_avalon_pio
#define PEAK_1_BASE 0x8002000
#define PEAK_1_BIT_CLEARING_EDGE_REGISTER 0
#define PEAK_1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PEAK_1_CAPTURE 0
#define PEAK_1_DATA_WIDTH 32
#define PEAK_1_DO_TEST_BENCH_WIRING 0
#define PEAK_1_DRIVEN_SIM_VALUE 0
#define PEAK_1_EDGE_TYPE "NONE"
#define PEAK_1_FREQ 100000000
#define PEAK_1_HAS_IN 1
#define PEAK_1_HAS_OUT 0
#define PEAK_1_HAS_TRI 0
#define PEAK_1_IRQ 3
#define PEAK_1_IRQ_INTERRUPT_CONTROLLER_ID 0
#define PEAK_1_IRQ_TYPE "LEVEL"
#define PEAK_1_NAME "/dev/peak_1"
#define PEAK_1_RESET_VALUE 0
#define PEAK_1_SPAN 16
#define PEAK_1_TYPE "altera_avalon_pio"


/*
 * peak_2 configuration
 *
 */

#define ALT_MODULE_CLASS_peak_2 altera_avalon_pio
#define PEAK_2_BASE 0x8002010
#define PEAK_2_BIT_CLEARING_EDGE_REGISTER 0
#define PEAK_2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PEAK_2_CAPTURE 0
#define PEAK_2_DATA_WIDTH 32
#define PEAK_2_DO_TEST_BENCH_WIRING 0
#define PEAK_2_DRIVEN_SIM_VALUE 0
#define PEAK_2_EDGE_TYPE "NONE"
#define PEAK_2_FREQ 100000000
#define PEAK_2_HAS_IN 1
#define PEAK_2_HAS_OUT 0
#define PEAK_2_HAS_TRI 0
#define PEAK_2_IRQ -1
#define PEAK_2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PEAK_2_IRQ_TYPE "NONE"
#define PEAK_2_NAME "/dev/peak_2"
#define PEAK_2_RESET_VALUE 0
#define PEAK_2_SPAN 16
#define PEAK_2_TYPE "altera_avalon_pio"


/*
 * peak_3 configuration
 *
 */

#define ALT_MODULE_CLASS_peak_3 altera_avalon_pio
#define PEAK_3_BASE 0x8002020
#define PEAK_3_BIT_CLEARING_EDGE_REGISTER 0
#define PEAK_3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PEAK_3_CAPTURE 0
#define PEAK_3_DATA_WIDTH 32
#define PEAK_3_DO_TEST_BENCH_WIRING 0
#define PEAK_3_DRIVEN_SIM_VALUE 0
#define PEAK_3_EDGE_TYPE "NONE"
#define PEAK_3_FREQ 100000000
#define PEAK_3_HAS_IN 1
#define PEAK_3_HAS_OUT 0
#define PEAK_3_HAS_TRI 0
#define PEAK_3_IRQ -1
#define PEAK_3_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PEAK_3_IRQ_TYPE "NONE"
#define PEAK_3_NAME "/dev/peak_3"
#define PEAK_3_RESET_VALUE 0
#define PEAK_3_SPAN 16
#define PEAK_3_TYPE "altera_avalon_pio"


/*
 * peak_reset configuration
 *
 */

#define ALT_MODULE_CLASS_peak_reset altera_avalon_pio
#define PEAK_RESET_BASE 0x8002030
#define PEAK_RESET_BIT_CLEARING_EDGE_REGISTER 0
#define PEAK_RESET_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PEAK_RESET_CAPTURE 0
#define PEAK_RESET_DATA_WIDTH 1
#define PEAK_RESET_DO_TEST_BENCH_WIRING 0
#define PEAK_RESET_DRIVEN_SIM_VALUE 0
#define PEAK_RESET_EDGE_TYPE "NONE"
#define PEAK_RESET_FREQ 100000000
#define PEAK_RESET_HAS_IN 0
#define PEAK_RESET_HAS_OUT 1
#define PEAK_RESET_HAS_TRI 0
#define PEAK_RESET_IRQ -1
#define PEAK_RESET_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PEAK_RESET_IRQ_TYPE "NONE"
#define PEAK_RESET_NAME "/dev/peak_reset"
#define PEAK_RESET_RESET_VALUE 0
#define PEAK_RESET_SPAN 16
#define PEAK_RESET_TYPE "altera_avalon_pio"


/*
 * pwm configuration
 *
 */

#define ALT_MODULE_CLASS_pwm altera_avalon_pio
#define PWM_BASE 0x8001050
#define PWM_BIT_CLEARING_EDGE_REGISTER 0
#define PWM_BIT_MODIFYING_OUTPUT_REGISTER 0
#define PWM_CAPTURE 0
#define PWM_DATA_WIDTH 16
#define PWM_DO_TEST_BENCH_WIRING 0
#define PWM_DRIVEN_SIM_VALUE 0
#define PWM_EDGE_TYPE "NONE"
#define PWM_FREQ 100000000
#define PWM_HAS_IN 0
#define PWM_HAS_OUT 1
#define PWM_HAS_TRI 0
#define PWM_IRQ -1
#define PWM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PWM_IRQ_TYPE "NONE"
#define PWM_NAME "/dev/pwm"
#define PWM_RESET_VALUE 0
#define PWM_SPAN 16
#define PWM_TYPE "altera_avalon_pio"


/*
 * sdram configuration
 *
 */

#define ALT_MODULE_CLASS_sdram altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x4000000
#define SDRAM_CAS_LATENCY 3
#define SDRAM_CONTENTS_INFO
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/sdram"
#define SDRAM_POWERUP_DELAY 100.0
#define SDRAM_REFRESH_PERIOD 15.625
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x19
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 10
#define SDRAM_SDRAM_DATA_WIDTH 16
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 13
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 0
#define SDRAM_SPAN 67108864
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_T_AC 5.5
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 20.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 20.0
#define SDRAM_T_WR 14.0


/*
 * uptime configuration
 *
 */

#define ALT_MODULE_CLASS_uptime altera_avalon_pio
#define UPTIME_BASE 0x8001000
#define UPTIME_BIT_CLEARING_EDGE_REGISTER 0
#define UPTIME_BIT_MODIFYING_OUTPUT_REGISTER 0
#define UPTIME_CAPTURE 0
#define UPTIME_DATA_WIDTH 32
#define UPTIME_DO_TEST_BENCH_WIRING 0
#define UPTIME_DRIVEN_SIM_VALUE 0
#define UPTIME_EDGE_TYPE "NONE"
#define UPTIME_FREQ 100000000
#define UPTIME_HAS_IN 1
#define UPTIME_HAS_OUT 0
#define UPTIME_HAS_TRI 0
#define UPTIME_IRQ -1
#define UPTIME_IRQ_INTERRUPT_CONTROLLER_ID -1
#define UPTIME_IRQ_TYPE "NONE"
#define UPTIME_NAME "/dev/uptime"
#define UPTIME_RESET_VALUE 0
#define UPTIME_SPAN 16
#define UPTIME_TYPE "altera_avalon_pio"


/*
 * video_dma_controller configuration
 *
 */

#define ALT_MODULE_CLASS_video_dma_controller altera_up_avalon_video_dma_controller
#define VIDEO_DMA_CONTROLLER_BASE 0x8001080
#define VIDEO_DMA_CONTROLLER_IRQ -1
#define VIDEO_DMA_CONTROLLER_IRQ_INTERRUPT_CONTROLLER_ID -1
#define VIDEO_DMA_CONTROLLER_NAME "/dev/video_dma_controller"
#define VIDEO_DMA_CONTROLLER_SPAN 16
#define VIDEO_DMA_CONTROLLER_TYPE "altera_up_avalon_video_dma_controller"

#endif /* __SYSTEM_H_ */
