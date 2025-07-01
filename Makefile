# TimerApp Simplified Makefile

# Directories
SRC_DIRS := . appTimer simulateLED
SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
REL_SRCS := $(patsubst ./%,%,$(SRCS))

# Includes
INCS := -I. -IappTimer -IsimulateLED

# Output directories
RELEASE_DIR := release
DEBUG_DIR := debug

# Compilers
HOST_CC := gcc
RPI_CC := aarch64-linux-gnu-gcc

# Executable names
EXE := appTimerexecutable
RPI_EXE := appTimerexecutable_rpi

# Generic build function
define build_template
# $1: Build type (RELEASE/DEBUG), $2: Compiler, $3: Flags, $4: Suffix (empty/_rpi)
$($1_DIR)/%.o$4: %.c | $$($1_DIR)
	$2 $(INCS) $3 -c $$< -o $$@

$($1_DIR)/%.s$4: %.c | $$($1_DIR)
	$2 $(INCS) $3 -S $$< -o $$@
endef

# Output directories
$(RELEASE_DIR) $(DEBUG_DIR):
	mkdir -p $@

# Object and assembly files
RELEASE_OBJS := $(addprefix $(RELEASE_DIR)/, $(REL_SRCS:.c=.o))
DEBUG_OBJS   := $(addprefix $(DEBUG_DIR)/,   $(REL_SRCS:.c=.o))
RELEASE_ASMS := $(addprefix $(RELEASE_DIR)/, $(REL_SRCS:.c=.s))
DEBUG_ASMS   := $(addprefix $(DEBUG_DIR)/,   $(REL_SRCS:.c=.s))

RPI_RELEASE_OBJS := $(addprefix $(RELEASE_DIR)/, $(REL_SRCS:.c=.rpi.o))
RPI_DEBUG_OBJS   := $(addprefix $(DEBUG_DIR)/,   $(REL_SRCS:.c=.rpi.o))
RPI_RELEASE_ASMS := $(addprefix $(RELEASE_DIR)/, $(REL_SRCS:.c=.rpi.s))
RPI_DEBUG_ASMS   := $(addprefix $(DEBUG_DIR)/,   $(REL_SRCS:.c=.rpi.s))

# Pattern rules for host and RPI
$(eval $(call build_template,RELEASE,$(HOST_CC),-Wall -Wextra -O2,))
$(eval $(call build_template,DEBUG,$(HOST_CC),-Wall -Wextra -g,))
$(eval $(call build_template,RELEASE,$(RPI_CC),-Wall -Wextra -O2,.rpi))
$(eval $(call build_template,DEBUG,$(RPI_CC),-Wall -Wextra -g,.rpi))

# Linking
$(RELEASE_DIR)/$(EXE): $(RELEASE_OBJS)
	$(HOST_CC) $(INCS) $^ -o $@

$(DEBUG_DIR)/$(EXE): $(DEBUG_OBJS)
	$(HOST_CC) $(INCS) $^ -o $@

$(RELEASE_DIR)/$(RPI_EXE): $(RPI_RELEASE_OBJS)
	$(RPI_CC) $(INCS) $^ -o $@

$(DEBUG_DIR)/$(RPI_EXE): $(RPI_DEBUG_OBJS)
	$(RPI_CC) $(INCS) $^ -o $@

# Targets
.PHONY: all linux linux-debug rpi rpi-debug clean

all: linux rpi

linux: $(RELEASE_DIR) $(RELEASE_DIR)/$(EXE) $(RELEASE_ASMS)
linux-debug: $(DEBUG_DIR) $(DEBUG_DIR)/$(EXE) $(DEBUG_ASMS)
rpi: $(RELEASE_DIR) $(RELEASE_DIR)/$(RPI_EXE) $(RPI_RELEASE_ASMS)
rpi-debug: $(DEBUG_DIR) $(DEBUG_DIR)/$(RPI_EXE) $(RPI_DEBUG_ASMS)

clean:
	rm -rf $(RELEASE_DIR) $(DEBUG_DIR)
