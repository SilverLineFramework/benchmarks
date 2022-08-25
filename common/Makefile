WASMCC=/opt/wasi-sdk/bin/clang
WASMCFLAGS= -O1

OUT_DIR=../wasm/common

.PHONY: all dir

all: dir wrapper.wasm

dir:
	mkdir -p $(OUT_DIR)

wrapper.wasm: $(WRAPPER_C)
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $(OUT_DIR)/$@

