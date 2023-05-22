WASM_DIR=$(ROOT_WASM_DIR)
SRCS=main.c matrix.c
CC=$(WASMCC) $(WASMCLFLAGS) $(SRCS)

.PHONY: loadgen
loadgen:
	$(CC) -DPASSIVE -o $(WASM_DIR)/loadgen_passive.wasm -lm
	$(CC) -DACTIVE -o $(WASM_DIR)/loadgen_active.wasm -lm
	$(CC) -DONESHOT -o $(WASM_DIR)/loadgen.wasm -lm
