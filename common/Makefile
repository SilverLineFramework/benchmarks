.PHONY: all dir

MEMCHECK_WASM=$(ROOT_WASM_DIR)/common/memcheck.wasm

all: dir wrapper.wasm memcheck.wasm

dir:
	mkdir -p $(shell dirname $(WRAPPER_WASM))

wrapper.wasm: $(WRAPPER_C)
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $(WRAPPER_WASM)

memcheck.wasm: memcheck.c
	$(WASMCC) $(WASMCLFLAGS) $^ -o $(MEMCHECK_WASM)
