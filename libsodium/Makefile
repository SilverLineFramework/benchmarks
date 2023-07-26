WASM_DIR=$(ROOT_WASM_DIR)/libsodium

.PHONY: all clean

all:
	mkdir -p $(WASM_DIR)
	cp -r webassembly-benchmarks/2022-12/wasm/* $(WASM_DIR)

clean:
	rm -r $(WASM_DIR)
