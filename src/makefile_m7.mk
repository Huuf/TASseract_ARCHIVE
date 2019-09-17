-include common.mk

# default action: build all
all: $(BUILD_DIR_CM7)/$(TARGET_CM7).elf $(BUILD_DIR_CM7)/$(TARGET_CM7).hex $(BUILD_DIR_CM7)/$(TARGET_CM7).bin copy_cm7

#######################################
# build the M7 Core
#######################################
vpath %.c $(sort $(dir $(C_SOURCES_CM7)))
vpath %.s $(sort $(dir $(ASM_SOURCES_CM7)))

copy_cm7: $(OUT_DIR)
ifeq ($(OS),Windows_NT)
	copy $(BUILD_DIR_CM7)\$(TARGET_CM7).elf out\$(TARGET_CM7).elf
	copy $(BUILD_DIR_CM7)\$(TARGET_CM7).hex out\$(TARGET_CM7).hex
	copy $(BUILD_DIR_CM7)\$(TARGET_CM7).bin out\$(TARGET_CM7).bin
	copy $(BUILD_DIR_CM7)\$(TARGET_CM7).map out\$(TARGET_CM7).map
else
	cp -f $(BUILD_DIR_CM7)/$(TARGET_CM7).elf out/$(TARGET_CM7).elf
	cp -f $(BUILD_DIR_CM7)/$(TARGET_CM7).hex out/$(TARGET_CM7).hex
	cp -f $(BUILD_DIR_CM7)/$(TARGET_CM7).bin out/$(TARGET_CM7).bin
	cp -f $(BUILD_DIR_CM7)/$(TARGET_CM7).map out/$(TARGET_CM7).map
endif

#######################################
# build the application
#######################################

$(BUILD_DIR_CM7)/%.o: %.c makefile_m7.mk | $(BUILD_DIR_CM7) 
	$(CC) -c $(CFLAGS_CM7) $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR_CM7)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR_CM7)/%.o: %.s makefile_m7.mk | $(BUILD_DIR_CM7)
	$(AS) -c $(CFLAGS_CM7) $(CFLAGS) $< -o $@

$(BUILD_DIR_CM7)/$(TARGET_CM7).elf: $(OBJECTS_CM7) makefile_m7.mk
	$(CC) $(OBJECTS_CM7) $(LDFLAGS_CM7) -o $@
	$(SZ) $@

$(BUILD_DIR_CM7)/%.hex: $(BUILD_DIR_CM7)/%.elf | $(BUILD_DIR_CM7)
	$(HEX) $< $@
	
$(BUILD_DIR_CM7)/%.bin: $(BUILD_DIR_CM7)/%.elf | $(BUILD_DIR_CM7)
	$(BIN) $< $@
	
$(BUILD_DIR_CM7):
	mkdir $@

#######################################
# clean up
#######################################
clean:
ifeq ($(OS),Windows_NT)
	-rmdir /S /Q $(BUILD_DIR_CM7)
else
	-rm -fR $(BUILD_DIR_CM7)
endif

-include common_after.mk

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR_CM7)/*.d)

# *** EOF ***
