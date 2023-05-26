# Benchmark specific flags
WASMCFLAGS+= -I.

# Output
OUT_DIR=$(ROOT_WASM_DIR)/sod
DATA_DIR=$(ROOT_DATA_DIR)/sod
COMMON_DIR=$(ROOT_WASM_DIR)/sod/common

# Common files
COMMON = sod.wasm

BENCHMARKS := $(shell ls samples/*.c)
WASM := $(BENCHMARKS:.c=.wasm)

.PHONY: all clean dir

all: dir $(WASM) data

dir:
	mkdir -p $(OUT_DIR)
	mkdir -p $(DATA_DIR)
	mkdir -p $(COMMON_DIR)

$(COMMON) : %.wasm : %.c
	$(WASMCC) $(WASMCFLAGS) -D_WASI_EMULATED_MMAN -c $^ -o $(COMMON_DIR)/$@

$(WASM): %.wasm : %.c $(COMMON)
	$(eval INT_FILE = $(shell mktemp))
	$(WASMCC) $(WASMCFLAGS) $< -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_DIR)/sod.wasm \
		$(INT_FILE) -o $(OUT_DIR)/$(notdir $(basename $@)).wasm
	rm $(INT_FILE)

data:
	cp -r images/* $(DATA_DIR)