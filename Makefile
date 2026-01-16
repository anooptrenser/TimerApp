# Directories and source files
SRC_DIRS := . appTimer simulateLED
SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

RELEASE_DIR := release
DEBUG_DIR := debug

# Compilers and flags
HOST_CC := gcc
RPI_CC := aarch64-linux-gnu-gcc
CFLAGS := -Wall -Wextra
RELEASE_FLAGS := -O2
DEBUG_FLAGS := -g -O0
INCS := -I. -IappTimer -IsimulateLED

# Raspberry Pi libgpiod paths
RPI_GPIOD_INC := -I/opt/gpiod-v1-arm/include
RPI_GPIOD_LIB := -L/opt/gpiod-v1-arm/lib -Wl,-rpath=/opt/gpiod-v1-arm/lib -lgpiod

# Executable names
EXE := appTimerexecutable
RPI_EXE := appTimerexecutable_rpi
RPI_LED_EXE := appTimerexecutable_rpi_led

# Object and assembly files (preserve subdirectory structure)
OBJS := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(SRCS))
ASMS := $(patsubst %.c,$(RELEASE_DIR)/%.s,$(SRCS))
DBG_OBJS := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(SRCS))
DBG_ASMS := $(patsubst %.c,$(DEBUG_DIR)/%.s,$(SRCS))
RPI_OBJS := $(patsubst %.c,$(RELEASE_DIR)/%.rpi.o,$(SRCS))
RPI_ASMS := $(patsubst %.c,$(RELEASE_DIR)/%.rpi.s,$(SRCS))
RPI_LED_OBJS := $(patsubst %.c,$(RELEASE_DIR)/%.rpi-led.o,$(SRCS))
RPI_LED_ASMS := $(patsubst %.c,$(RELEASE_DIR)/%.rpi-led.s,$(SRCS))

.PHONY: linux rpi rpi-led debug all clean dirs

dirs:
	@mkdir -p $(RELEASE_DIR) $(DEBUG_DIR)
	@for dir in $(SRC_DIRS); do mkdir -p $(RELEASE_DIR)/$$dir $(DEBUG_DIR)/$$dir; done

# Host build rules (release)
$(RELEASE_DIR)/%.o: %.c | dirs
	@mkdir -p $(dir $@)
	$(HOST_CC) $(CFLAGS) $(RELEASE_FLAGS) $(INCS) -c $< -o $@

$(RELEASE_DIR)/%.s: %.c | dirs
	@mkdir -p $(dir $@)
	$(HOST_CC) $(CFLAGS) $(RELEASE_FLAGS) $(INCS) -S $< -o $@

# Host build rules (debug)
$(DEBUG_DIR)/%.o: %.c | dirs
	@mkdir -p $(dir $@)
	$(HOST_CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCS) -c $< -o $@

$(DEBUG_DIR)/%.s: %.c | dirs
	@mkdir -p $(dir $@)
	$(HOST_CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCS) -S $< -o $@

# Raspberry Pi cross-build rules (release only)
$(RELEASE_DIR)/%.rpi.o: %.c | dirs
	@mkdir -p $(dir $@)
	$(RPI_CC) $(CFLAGS) $(RELEASE_FLAGS) $(INCS) -c $< -o $@

$(RELEASE_DIR)/%.rpi.s: %.c | dirs
	@mkdir -p $(dir $@)
	$(RPI_CC) $(CFLAGS) $(RELEASE_FLAGS) $(INCS) -S $< -o $@

# Raspberry Pi cross-build rules (with USE_RASPI)
$(RELEASE_DIR)/%.rpi-led.o: %.c | dirs
	@mkdir -p $(dir $@)
	$(RPI_CC) $(CFLAGS) $(RELEASE_FLAGS) $(INCS) $(RPI_GPIOD_INC) -DUSE_RASPI -c $< -o $@

$(RELEASE_DIR)/%.rpi-led.s: %.c | dirs
	@mkdir -p $(dir $@)
	$(RPI_CC) $(CFLAGS) $(RELEASE_FLAGS) $(INCS) $(RPI_GPIOD_INC) -DUSE_RASPI -S $< -o $@

# Targets
linux: $(OBJS) $(ASMS)
	$(HOST_CC) $(CFLAGS) $(RELEASE_FLAGS) $(INCS) $(OBJS) -o $(RELEASE_DIR)/$(EXE)

debug: $(DBG_OBJS) $(DBG_ASMS)
	$(HOST_CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCS) $(DBG_OBJS) -o $(DEBUG_DIR)/$(EXE)

rpi: $(RPI_OBJS) $(RPI_ASMS)
	$(RPI_CC) $(CFLAGS) $(RELEASE_FLAGS) $(INCS) $(RPI_OBJS) -o $(RELEASE_DIR)/$(RPI_EXE)

rpi-led: $(RPI_LED_OBJS) $(RPI_LED_ASMS)
	$(RPI_CC) $(CFLAGS) $(RELEASE_FLAGS) $(INCS) $(RPI_GPIOD_INC) -DUSE_RASPI $(RPI_LED_OBJS) $(RPI_GPIOD_LIB) -o $(RELEASE_DIR)/$(RPI_LED_EXE)

all: linux rpi rpi-led

clean:
	rm -rf $(RELEASE_DIR) $(DEBUG_DIR)
