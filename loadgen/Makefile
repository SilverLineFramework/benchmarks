WASM_DIR=$(ROOT_WASM_DIR)

.PHONY: all loadgen
all: loadgen

loadgen:
	$(WASMCC) $(WASMCLFLAGS) main.c matrix.c -o $(WASM_DIR)/loadgen.wasm -lm
