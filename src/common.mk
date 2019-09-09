# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#   2019-08-04 - Modified to compile correctly 2 cores
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET_CM4 = TAStm32H745ZIT6_CM4
TARGET_CM7 = TAStm32H745ZIT6_CM7


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR_CM4 = build_cm4
BUILD_DIR_CM7 = build_cm7
OUT_DIR = out

######################################
# source
######################################
# C sources
C_SOURCES_COMMON = Common/Src/system_stm32h7xx_dualcore_boot_cm4_cm7.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_usb.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_sdmmc.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_delayblock.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c

C_SOURCES_CM4 =  \
$(C_SOURCES_COMMON) \
CM4/Src/main.c \
CM4/Src/stm32h7xx_it.c \
CM4/Src/stm32h7xx_hal_msp.c \
CM4/Src/sleep_us_cm4.c


C_SOURCES_CM7 =  \
$(C_SOURCES_COMMON) \
CM7/Src/main.c \
CM7/Src/usb_device.c \
CM7/Src/ra8875.c \
CM7/Src/usbd_conf.c \
CM7/Src/usbd_desc.c \
CM7/Src/usbd_cdc_if.c \
CM7/Src/stm32h7xx_it.c \
CM7/Src/stm32h7xx_hal_msp.c \
CM7/Src/sleep_us_cm7.c \
Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c \
Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c

# ASM sources
ASM_SOURCES_CM4 =  \
startup_stm32h745xx_CM4.s
ASM_SOURCES_CM7 =  \
startup_stm32h745xx_CM7.s


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU_CM4 = -mcpu=cortex-m4
CPU_CM7 = -mcpu=cortex-m7

# fpu
FPU_CM4 = -mfpu=fpv4-sp-d16
FPU_CM7 = -mfpu=fpv5-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU_CM4 = $(CPU_CM4) -mthumb $(FPU_CM4) $(FLOAT-ABI)
MCU_CM7 = $(CPU_CM7) -mthumb $(FPU_CM7) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS_COMMON =  \
-DUSE_HAL_DRIVER \
-DSTM32H745xx

C_DEFS_CM4 = \
$(C_DEFS_COMMON) \
-DCORE_CM4

C_DEFS_CM7 = \
$(C_DEFS_COMMON) \
-DCORE_CM7


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES_COMMON =  \
-IDrivers/STM32H7xx_HAL_Driver/Inc \
-IDrivers/STM32H7xx_HAL_Driver/Inc/Legacy \
-IDrivers/CMSIS/Device/ST/STM32H7xx/Include \
-IDrivers/CMSIS/Include

C_INCLUDES_CM4 =  \
$(C_INCLUDES_COMMON) \
-ICM4/Inc

C_INCLUDES_CM7 =  \
$(C_INCLUDES_COMMON) \
-ICM7/Inc \
-IMiddlewares/ST/STM32_USB_Device_Library/Core/Inc \
-IMiddlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc

# compile gcc flags
ASFLAGS_CM4 = $(MCU_CM4) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
ASFLAGS_CM7 = $(MCU_CM7) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS_CM4 = $(MCU_CM4) $(C_DEFS_CM4) $(C_INCLUDES_CM4) $(OPT) -Wall -fdata-sections -ffunction-sections
CFLAGS_CM7 = $(MCU_CM7) $(C_DEFS_CM7) $(C_INCLUDES_CM7) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT_CM4 = stm32h745xx_flash_CM4.ld
LDSCRIPT_CM7 = stm32h745xx_flash_CM7.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS_CM4 = $(MCU_CM4) -specs=nano.specs -T$(LDSCRIPT_CM4) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR_CM4)/$(TARGET_CM4).map,--cref -Wl,--gc-sections
LDFLAGS_CM7 = $(MCU_CM7) -specs=nano.specs -T$(LDSCRIPT_CM7) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR_CM7)/$(TARGET_CM7).map,--cref -Wl,--gc-sections

# list of objects
OBJECTS_CM4 = $(addprefix $(BUILD_DIR_CM4)/,$(notdir $(C_SOURCES_CM4:.c=.o)))

OBJECTS_CM7 = $(addprefix $(BUILD_DIR_CM7)/,$(notdir $(C_SOURCES_CM7:.c=.o)))
# list of ASM program objects
OBJECTS_CM4 += $(addprefix $(BUILD_DIR_CM4)/,$(notdir $(ASM_SOURCES_CM4:.s=.o)))
OBJECTS_CM7 += $(addprefix $(BUILD_DIR_CM7)/,$(notdir $(ASM_SOURCES_CM7:.s=.o)))
