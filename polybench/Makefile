# Output
OUT_DIR=$(ROOT_WASM_DIR)/polybench
COMMON_DIR=$(OUT_DIR)/common

# Folders must start with pb_; pulls all .c files in that directory.
BENCHMARKS := $(shell ls benchmarks/*.c)
WASM := $(BENCHMARKS:.c=.wasm)

.PHONY: all clean dir

all: dir $(WASM)

clean:
	rm -rf $(OUT_DIR)

dir:
	mkdir -p $(OUT_DIR)
	mkdir -p $(OUT_DIR)/mini
	mkdir -p $(OUT_DIR)/small
	mkdir -p $(OUT_DIR)/medium
	mkdir -p $(OUT_DIR)/large
	mkdir -p $(COMMON_DIR)

polybench: $(COMMON_DIR) polybench.c
	$(WASMCC) $(WASMCFLAGS) -c -I/$^ -o $(COMMON_DIR)/polybench.wasm

LINKCOMMON=$(WASMLD) $(WASMLDFLAGS) $(COMMON_DIR)/polybench.wasm


$(WASM): %.wasm : %.c polybench
	$(eval TMP = $(shell mktemp))

	$(WASMCC) $(WASMCFLAGS) $< -c -o $(TMP) -D MINI_DATASET -I./
	$(LINKCOMMON) $(TMP) -o $(OUT_DIR)/mini/$(notdir $(basename $@)).wasm
	$(WASMCC) $(WASMCFLAGS) $< -c -o $(TMP) -D SMALL_DATASET -I./
	$(LINKCOMMON) $(TMP) -o $(OUT_DIR)/small/$(notdir $(basename $@)).wasm
	rm $(TMP)
