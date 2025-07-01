# TimerApp Makefile (auto-creates subdirectories)

SRC_DIRS := . appTimer simulateLED
SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
REL_SRCS := $(patsubst ./%,%,$(SRCS))

INCS := -I. -IappTimer -IsimulateLED

RELEASE_DIR := release
DEBUG_DIR := debug

HOST_CC := gcc
RPI_CC := aarch64-linux-gnu-gcc

EXE := appTimerexecutable
RPI_EXE := appTimerexecutable_rpi

# Object and assembly files
RELEASE_OBJS := $(patsubst %.c,$(RELEASE_DIR)/%.o,$(REL_SRCS))
DEBUG_OBJS := $(patsubst %.c,$(DEBUG_DIR)/%.o,$(REL_SRCS))
RELEASE_ASMS := $(patsubst %.c,$(RELEASE_DIR)/%.s,$(REL_SRCS))
DEBUG_ASMS := $(patsubst %.c,$(DEBUG_DIR)/%.s,$(REL_SRCS))

RPI_RELEASE_OBJS := $(patsubst %.c,$(RELEASE_DIR)/%.rpi.o,$(REL_SRCS))
RPI_DEBUG_OBJS := $(patsubst %.c,$(DEBUG_DIR)/%.rpi.o,$(REL_SRCS))
RPI_RELEASE_ASMS := $(patsubst %.c,$(RELEASE_DIR)/%.rpi.s,$(REL_SRCS))
RPI_DEBUG_ASMS := $(patsubst %.c,$(DEBUG_DIR)/%.rpi.s,$(REL_SRCS))

# Pattern rules for objects and assembly with directory creation
$(RELEASE_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(HOST_CC) -Wall -Wextra $(INCS) -O2 -c $< -o $@

$(DEBUG_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(HOST_CC) -Wall -Wextra $(INCS) -g -c $< -o $@

$(RELEASE_DIR)/%.s: %.c
	mkdir -p $(dir $@)
	$(HOST_CC) $(INCS) -S -O2 $< -o $@

$(DEBUG_DIR)/%.s: %.c
	mkdir -p $(dir $@)
	$(HOST_CC) $(INCS) -S -g $< -o $@

$(RELEASE_DIR)/%.rpi.o: %.c
	mkdir -p $(dir $@)
	$(RPI_CC) -Wall -Wextra $(INCS) -O2 -c $< -o $@

$(DEBUG_DIR)/%.rpi.o: %.c
	mkdir -p $(dir $@)
	$(RPI_CC) -Wall -Wextra $(INCS) -g -c $< -o $@

$(RELEASE_DIR)/%.rpi.s: %.c
	mkdir -p $(dir $@)
	$(RPI_CC) $(INCS) -S -O2 $< -o $@

$(DEBUG_DIR)/%.rpi.s: %.c
	mkdir -p $(dir $@)
	$(RPI_CC) $(INCS) -S -g $< -o $@

# Linking
$(RELEASE_DIR)/$(EXE): $(RELEASE_OBJS)
	$(HOST_CC) $(INCS) $^ -o $@

$(DEBUG_DIR)/$(EXE): $(DEBUG_OBJS)
	$(HOST_CC) $(INCS) $^ -o $@

$(RELEASE_DIR)/$(RPI_EXE): $(RPI_RELEASE_OBJS)
	$(RPI_CC) $(INCS) $^ -o $@

$(DEBUG_DIR)/$(RPI_EXE): $(RPI_DEBUG_OBJS)
	$(RPI_CC) $(INCS) $^ -o $@

.PHONY: linux linux-debug rpi rpi-debug all clean

linux: $(RELEASE_DIR)/$(EXE) $(RELEASE_ASMS)
linux-debug: $(DEBUG_DIR)/$(EXE) $(DEBUG_ASMS)
rpi: $(RELEASE_DIR)/$(RPI_EXE) $(RPI_RELEASE_ASMS)
rpi-debug: $(DEBUG_DIR)/$(RPI_EXE) $(RPI_DEBUG_ASMS)
all: linux rpi

clean:
	rm -rf $(RELEASE_DIR) $(DEBUG_DIR)
