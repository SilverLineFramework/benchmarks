.PHONY: all dir

all: dir wrapper.wasm

dir:
	mkdir -p $(shell dirname $(WRAPPER_WASM))

wrapper.wasm: $(WRAPPER_C)
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $(WRAPPER_WASM)

