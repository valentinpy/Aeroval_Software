# Makefile to compile Aeroval manually
# Valentin Py - Aeroval
# 02.11.15
# You need an arm-non-eabi toolchain (available with Kinetis-Design-Studio for example.)
# The file you'll have to load to the microcontroller is the *.elf, fount in ./build/
#
# This makefile is inspired from https://github.com/phantax/stm32f4/blob/master/makefile



# Copyright (C) 2015 Valentin Py
#
# This file is part of Aeroval.
#
# Aeroval is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Aeroval is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


#Project's name
PROJ_NAME = aeroval

#PROJ_DIR = /Users/valentinpy/workspace/Aeroval-2
PROJ_DIR =

#List of source files
SRC_FILES = $(PROJ_DIR)Project_Settings/Startup_Code/startup_MK64F12.S
SRC_FILES += $(PROJ_DIR)Project_Settings/Startup_Code/system_MK64F12.c
SRC_FILES += $(PROJ_DIR)Sources/*.c
SRC_FILES += $(PROJ_DIR)Sources/*/*.c

#List of includes directories
INC_DIRS  = $(PROJ_DIR)Includes
INC_DIRS += $(PROJ_DIR)Sources
INC_DIRS += $(PROJ_DIR)Sources/*

#Prefix
C_PREFIX = arm-none-eabi-


#Linker script
LD_SCRIPT = $(PROJ_DIR)Project_settings/Linker_Files/MK64FN1M0xxx12_flash.ld

#Build directory
BUILD_DIR = build

#
CC 	= $(C_PREFIX)gcc
CXX 	= $(C_PREFIX)g++
OBJCOPY = $(C_PREFIX)objcopy
OBJDUMP = $(C_PREFIX)objdump
SIZE	= $(C_PREFIX)size

#
FLAGS	=  -mcpu=cortex-m4
FLAGS	+= -mthumb
FLAGS	+= -mfloat-abi=hard
FLAGS	+= -mfpu=fpv4-sp-d16

#
CFLAGS	= $(FLAGS)
CFLAGS	+= -c
CFLAGS	+= -g3
CFLAGS  += -O0
CFLAGS  += -std=c99

CFLAGS  += -fdata-sections
CFLAGS  += -ffunction-sections

CFLAGS  += -Wall
CFLAGS  += -Wuninitialized
CFLAGS  += -Wextra
CFLAGS  += -Wmissing-declarations
CFLAGS  += -Wshadow
CFLAGS  += -Wdeclaration-after-statement
CFLAGS  += -Wfloat-equal
CFLAGS  += -Wcast-align
CFLAGS  += -Wbad-function-cast
CFLAGS  += -Wstrict-prototypes
CFLAGS  += -Wmissing-prototypes
CFLAGS  += -Wsign-compare
CFLAGS  += -Wno-unused-parameter

CFLAGS  += $(foreach d, $(INC_DIRS), -I$d)

#
LDFLAGS= $(FLAGS)
LDFLAGS += $(foreach d, $(LD_SCRIPT), -T$d)
LDFLAGS += -Xlinker --gc-sections
LDFLAGS += -Wl,-Map=$(BUILD_DIR)/$(PROJ_NAME).map
LDFLAGS += --specs=nano.specs
LDFLAGS += --specs=nosys.specs

#
OBJ_BASE_DIR  = $(BUILD_DIR)/obj
PREP_BASE_DIR = $(BUILD_DIR)/prep
ASM_BASE_DIR  = $(BUILD_DIR)/asm

EXECUTABLE    = $(BUILD_DIR)/$(PROJ_NAME).elf
BINARY        = $(BUILD_DIR)/$(PROJ_NAME).bin

SOURCES       = $(foreach d, $(SRC_FILES), $(shell ls -1 $d))
OBJECTS       = $(addprefix $(OBJ_BASE_DIR)/, $(addsuffix .o, $(SOURCES)))
PREPS         = $(addprefix $(PREP_BASE_DIR)/, $(SOURCES))
ASMS          = $(patsubst $(OBJ_BASE_DIR)/%, $(ASM_BASE_DIR)/%.s, $(OBJECTS))

all: bin size

exec: $(EXECUTABLE) 

bin: $(BINARY) 

prep: $(PREPS) 

obj: $(OBJECTS)

asm: $(ASMS)

$(EXECUTABLE): obj
	@echo "\033[01;33m==> Linking files -> '$@':\033[00;00m"
	@mkdir -p $(dir $@)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	@echo ""

$(BINARY): $(EXECUTABLE)
	@echo "\033[01;33m==> Creating binary '$(EXECUTABLE)' -> '$@':\033[00;00m"
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O binary $(EXECUTABLE) $@
	
list: $(EXECUTABLE)
	@echo "\033[01;33m==> Creating listing for '$(EXECUTABLE)' :\033[00;00m"
	$(OBJDUMP) --source --all-headers --demangle --line-number $(EXECUTABLE) > $(EXECUTABLE).lst
	
size : $(EXECUTABLE)
	@echo "\033[01;33m==> Printing size for '$(EXECUTABLE)':\033[00;00m"
	$(SIZE) --format=berkley $(EXECUTABLE)
	
$(OBJ_BASE_DIR)/%.c.o: %.c
	@echo "\033[01;32m==> Compiling C '$<' -> '$@':\033[00;00m"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@
	@echo ""
	
$(OBJ_BASE_DIR)/%.S.o: %.S
	@echo "\033[01;32m==> Compiling assembler '$<' -> '$@':\033[00;00m"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@
	@echo ""
	
$(OBJ_BASE_DIR)/%.cpp.o: %.cpp
	@echo "\033[01;32m==> Compiling C++ '$<' -> '$@':\033[00;00m"
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo ""
	
$(PREP_BASE_DIR)/%: %
	@echo "\033[01;32m==> Preprocessing '$<' -> '$@':\033[00;00m"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -E > $@
	@echo ""
	
$(ASM_BASE_DIR)/%.S: $(OBJ_BASE_DIR)/%
	@echo "\033[01;32m==> Disassembling '$<' -> '$@':\033[00;00m"
	@mkdir -p $(dir $@)
	$(OBJDUMP) -d -S $< > $@
	@echo ""
	
clean:
	@echo "\033[01;31m==> Cleaning directories:\033[00;00m"
	rm -rf $(BUILD_DIR)/
	@echo ""

