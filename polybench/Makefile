# Output
OUT_DIR=$(ROOT_WASM_DIR)/polybench
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
	$(eval INT_FILE_S = $(shell mktemp))
	$(WASMCC) $(WASMCFLAGS) $< -c -o $(INT_FILE_S) -D SMALL_DATASET
	$(WASMLD) $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_DIR)/polybench_s.wasm \
		$(INT_FILE_S) -o $(OUT_DIR)/$(notdir $(basename $@))_s.wasm
	rm $(INT_FILE_S)

	$(eval INT_FILE_M = $(shell mktemp))
	$(WASMCC) $(WASMCFLAGS) $< -c -o $(INT_FILE_M) -D MEDIUM_DATASET
	$(WASMLD) $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_DIR)/polybench_m.wasm \
		$(INT_FILE_M) -o $(OUT_DIR)/$(notdir $(basename $@))_m.wasm
	rm $(INT_FILE_M)
