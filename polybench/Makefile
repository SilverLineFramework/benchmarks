# Output
OUT_DIR=../wasm/polybench
COMMON_DIR=$(OUT_DIR)/common

# COMMON= polybench.c ../common/active.c ../common/dp.c

# Folders must start with pb_; pulls all .c files in that directory.
BENCHMARKS := $(shell ls benchmarks/*.c)
WASM := $(BENCHMARKS:.c=.wasm)

.PHONY: all clean dir

all: dir $(WASM)

dir:
	mkdir -p $(OUT_DIR)
	mkdir -p $(COMMON_DIR)

polybench: polybench.c
	$(WASMCC) $(WASMCFLAGS) -D SMALL_DATASET -c $^ -o $(COMMON_DIR)/polybench_s.wasm
	$(WASMCC) $(WASMCFLAGS) -D MEDIUM_DATASET -c $^ -o $(COMMON_DIR)/polybench_m.wasm

$(WASM): %.wasm : %.c polybench
	$(eval INT_FILE = $(shell mktemp))
	$(WASMCC) $(WASMCFLAGS) $< -c -o $(INT_FILE)
	wasm-ld $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_DIR)/polybench_s.wasm \
		$(INT_FILE) -o $(OUT_DIR)/$(notdir $(basename $@))_s.wasm
	wasm-ld $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_DIR)/polybench_m.wasm \
		$(INT_FILE) -o $(OUT_DIR)/$(notdir $(basename $@))_m.wasm
	rm $(INT_FILE)

