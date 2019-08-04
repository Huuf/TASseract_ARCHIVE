-include common.mk

# default action: build all
all: $(BUILD_DIR_CM4)/$(TARGET_CM4).elf $(BUILD_DIR_CM4)/$(TARGET_CM4).hex $(BUILD_DIR_CM4)/$(TARGET_CM4).bin copy_cm4

#######################################
# build the M4 Core
#######################################
vpath %.c $(sort $(dir $(C_SOURCES_CM4)))
vpath %.s $(sort $(dir $(ASM_SOURCES_CM4)))

copy_cm4: $(OUT_DIR)
ifeq ($(OS),Windows_NT)
	copy $(BUILD_DIR_CM4)\\$(TARGET_CM4).elf out\\$(TARGET_CM4).elf
	copy $(BUILD_DIR_CM4)\\$(TARGET_CM4).hex out\\$(TARGET_CM4).hex
	copy $(BUILD_DIR_CM4)\\$(TARGET_CM4).bin out\\$(TARGET_CM4).bin
	copy $(BUILD_DIR_CM4)\\$(TARGET_CM4).map out\\$(TARGET_CM4).map
else
	cp -f $(BUILD_DIR_CM4)/$(TARGET_CM4).elf out/$(TARGET_CM4).elf
	cp -f $(BUILD_DIR_CM4)/$(TARGET_CM4).hex out/$(TARGET_CM4).hex
	cp -f $(BUILD_DIR_CM4)/$(TARGET_CM4).bin out/$(TARGET_CM4).bin
	cp -f $(BUILD_DIR_CM4)/$(TARGET_CM4).map out/$(TARGET_CM4).map
endif

#######################################
# build the application
#######################################

$(BUILD_DIR_CM4)/%.o: %.c makefile_m4.mk | $(BUILD_DIR_CM4) 
	$(CC) -c $(CFLAGS_CM4) $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR_CM4)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR_CM4)/%.o: %.s makefile_m4.mk | $(BUILD_DIR_CM4)
	$(AS) -c $(CFLAGS_CM4) $(CFLAGS) $< -o $@

$(BUILD_DIR_CM4)/$(TARGET_CM4).elf: $(OBJECTS_CM4) makefile_m4.mk
	$(CC) $(OBJECTS_CM4) $(LDFLAGS_CM4) -o $@
	$(SZ) $@

$(BUILD_DIR_CM4)/%.hex: $(BUILD_DIR_CM4)/%.elf | $(BUILD_DIR_CM4)
	$(HEX) $< $@
	
$(BUILD_DIR_CM4)/%.bin: $(BUILD_DIR_CM4)/%.elf | $(BUILD_DIR_CM4)
	$(BIN) $< $@
	
$(BUILD_DIR_CM4):
	mkdir $@

#######################################
# clean up
#######################################
clean:
ifeq ($(OS),Windows_NT)
	-rmdir /S /Q $(BUILD_DIR_CM4)
else
	-rm -fR $(BUILD_DIR_CM4)
endif

-include common_after.mk

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR_CM4)/*.d)

 # *** EOF ***
