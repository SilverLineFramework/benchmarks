LIB_DIR=libs
export WALI_DIR= $(ROOT_WASM_DIR)
export WALI_LIB_DIR= $(WALI_DIR)/$(LIB_DIR)

# Allow tests to use all compiled libs
export WASMCFLAGS+= -I$(WALI_LIB_DIR)/inc
export WASMCFLAGS+= -L$(WALI_LIB_DIR)/lib
export WASMCLFLAGS+= -I$(WALI_LIB_DIR)/inc
export WASMCLFLAGS+= -L$(WALI_LIB_DIR)/lib

DIRECTORIES := $(wildcard */)
SUITES := $(filter-out $(LIB_DIR), $(DIRECTORIES:/=))

.PHONY: all clean default $(LIB_DIR) $(SUITES)

default: all

$(LIB_DIR):
	make -C $(LIB_DIR)

define SUITE_BUILD
$(SUITE):
	make -C $(SUITE)
endef

$(foreach SUITE,$(SUITES),$(eval $(SUITE_BUILD)))

all: $(LIB_DIR) $(SUITES)
	@echo "Suites: $(SUITES)"

clean:
	make -C $(LIB_DIR) clean
