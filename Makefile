# Directories
SRC_DIRS := . appTimer simulateLED
SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
REL_SRCS := $(patsubst ./%,%,$(SRCS))

# Includes
INCS := -I. -IappTimer -IsimulateLED

# Output folders
RELEASE_DIR := release
DEBUG_DIR := debug

# Compiler tools
HOST_CC := gcc
HOST_OBJD := objdump

RPI_CC := aarch64-linux-gnu-gcc
RPI_OBJD := aarch64-linux-gnu-objdump

# Executable names
RELEASE_EXE := $(RELEASE_DIR)/appTimerexecutable
DEBUG_EXE := $(DEBUG_DIR)/appTimerexecutable

# Object and assembly files
RELEASE_OBJS := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(REL_SRCS))
DEBUG_OBJS := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(REL_SRCS))
RELEASE_ASMS := $(patsubst %.c,$(RELEASE_DIR)/%.s,$(REL_SRCS))
DEBUG_ASMS := $(patsubst %.c,$(DEBUG_DIR)/%.s,$(REL_SRCS))

# Create output directories
RELEASE_OUT_DIRS := $(sort $(dir $(RELEASE_OBJS) $(RELEASE_ASMS)))
DEBUG_OUT_DIRS := $(sort $(dir $(DEBUG_OBJS) $(DEBUG_ASMS)))

$(RELEASE_OUT_DIRS) $(DEBUG_OUT_DIRS):
	@mkdir -p $@

# Pattern rules for objects and assembly
$(RELEASE_DIR)/%.o: %.c | $(RELEASE_OUT_DIRS)
	$(HOST_CC) -Wall -Wextra $(INCS) -O2 -c $< -o $@

$(DEBUG_DIR)/%.o: %.c | $(DEBUG_OUT_DIRS)
	$(HOST_CC) -Wall -Wextra $(INCS) -g -c $< -o $@

$(RELEASE_DIR)/%.s: %.c | $(RELEASE_OUT_DIRS)
	$(HOST_CC) $(INCS) -S -O2 $< -o $@

$(DEBUG_DIR)/%.s: %.c | $(DEBUG_OUT_DIRS)
	$(HOST_CC) $(INCS) -S -g $< -o $@

# Linking
$(RELEASE_EXE): $(RELEASE_OBJS)
	$(HOST_CC) $(INCS) $^ -o $@

$(DEBUG_EXE): $(DEBUG_OBJS)
	$(HOST_CC) $(INCS) $^ -o $@

# RPI rules
RPI_RELEASE_EXE := $(RELEASE_DIR)/appTimerexecutable_rpi
RPI_DEBUG_EXE := $(DEBUG_DIR)/appTimerexecutable_rpi
RPI_RELEASE_OBJS := $(patsubst %.c,$(RELEASE_DIR)/%.rpi.o,$(REL_SRCS))
RPI_DEBUG_OBJS := $(patsubst %.c,$(DEBUG_DIR)/%.rpi.o,$(REL_SRCS))
RPI_RELEASE_ASMS := $(patsubst %.c,$(RELEASE_DIR)/%.rpi.s,$(REL_SRCS))
RPI_DEBUG_ASMS := $(patsubst %.c,$(DEBUG_DIR)/%.rpi.s,$(REL_SRCS))

$(RELEASE_DIR)/%.rpi.o: %.c | $(RELEASE_OUT_DIRS)
	$(RPI_CC) -Wall -Wextra $(INCS) -O2 -c $< -o $@

$(DEBUG_DIR)/%.rpi.o: %.c | $(DEBUG_OUT_DIRS)
	$(RPI_CC) -Wall -Wextra $(INCS) -g -c $< -o $@

$(RELEASE_DIR)/%.rpi.s: %.c | $(RELEASE_OUT_DIRS)
	$(RPI_CC) $(INCS) -S -O2 $< -o $@

$(DEBUG_DIR)/%.rpi.s: %.c | $(DEBUG_OUT_DIRS)
	$(RPI_CC) $(INCS) -S -g $< -o $@

$(RPI_RELEASE_EXE): $(RPI_RELEASE_OBJS)
	$(RPI_CC) $(INCS) $^ -o $@

$(RPI_DEBUG_EXE): $(RPI_DEBUG_OBJS)
	$(RPI_CC) $(INCS) $^ -o $@

# Targets
.PHONY: linux linux-debug rpi rpi-debug all clean

linux: $(RELEASE_EXE) $(RELEASE_ASMS)
linux-debug: $(DEBUG_EXE) $(DEBUG_ASMS)
rpi: $(RPI_RELEASE_EXE) $(RPI_RELEASE_ASMS)
rpi-debug: $(RPI_DEBUG_EXE) $(RPI_DEBUG_ASMS)
all: linux rpi

clean:
	rm -rf release debug

