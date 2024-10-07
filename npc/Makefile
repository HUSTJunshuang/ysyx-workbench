# can be changed by make -e 'TOPNAME=<your_top_name>, BUT the #include <Vtop.h> in main.cpp should be changed too
TOPNAME = top
NXDC_FILES = constr/$(TOPNAME).nxdc
INC_PATH ?=

VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build --cc -O3 --x-assign fast --x-initial fast --noassert -Ivsrc

GTKWAVE = gtkwave

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
SIM_DIR = $(BUILD_DIR)/sim_dir
WAVES_DIR = ./waves
BIN = $(BUILD_DIR)/$(TOPNAME)
SIM = $(SIM_DIR)/V$(TOPNAME)

all: $(BIN)
	@echo "Finished compiling, run \"make sim\" to simulate."

# make the BUILD_DIR, excute in sequence?
$(shell mkdir -p $(BUILD_DIR))

# constraint file
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# project source
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v" -or -name "*.sv" -or -name "*.vh")
# the csrc need to use abspath, because the make will enter directory './build/obj_dir' and can't find csrc/*.c
CSRCS = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
SIMSRC = $(shell find $(abspath ./) -name "*sim.cpp")
CSRCS += $(SRC_AUTO_BIND)

# include rules for NVBoard
include $(NVBOARD_HOME)/scripts/nvboard.mk

# rules for verilator
INCFLAGS = $(addprefix -I , $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""

$(BIN): $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE)
	@rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

run: $(BIN)
	$(call git_commit, "run NVBoard") # DO NOT REMOVE THIS LINE!!!
	@$^

$(SIM): $(VSRCS) $(SIMSRC)
	$(VERILATOR) $(VERILATOR_CFLAGS) --top-module $(TOPNAME) --Mdir $(SIM_DIR) --exe --trace-fst $(SIMSRC) $(VSRCS)

sim: $(SIM)
	$(call git_commit, "sim RTL")
	@$^
	$(GTKWAVE) $(WAVES_DIR)

clean: clean_sta
	rm -rf $(BUILD_DIR) $(WAVES_DIR)

# include Makefile in ysyx-workbench, for the call of git_commit
include ../Makefile

# include rules for sta
include scripts/yosys-sta.mk

.PHONY: all sim clean
