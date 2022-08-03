# Output
OUT_DIR=../wasm/polybench

# COMMON= polybench.c ../common/active.c ../common/dp.c

# Folders must start with pb_; pulls all .c files in that directory.
BENCHMARKS := $(shell ls benchmarks/*.c)
WASM := $(BENCHMARKS:.c=.wasm)

.PHONY: all clean dir

all: dir $(WASM)

dir:
	mkdir -p $(OUT_DIR)

polybench.wasm: polybench.c
	$(WASMCC) $(WASMCFLAGS) -D SMALL_DATASET -c $^ -o $@

$(WASM): %.wasm : %.c polybench.wasm
	$(eval INT_FILE = $(shell mktemp))
	$(WASMCC) $(WASMCFLAGS) $< -c -o $(INT_FILE)
	wasm-ld $(WASMLDFLAGS) ../common/passive.wasm polybench.wasm \
		$(INT_FILE) -o $(OUT_DIR)/$(notdir $(basename $@))_s.wasm
	rm $(INT_FILE)

clean:
	rm -f *.wasm