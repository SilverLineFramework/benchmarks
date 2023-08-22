WASM_DIR=$(ROOT_WASM_DIR)/kissat.wasm
DATA_DIR=$(ROOT_DATA_DIR)/python
KISSAT_WASM=https://github.com/thetianshuhuang/kissat-wasm/releases/download/v3.1.0/kissat.wasm

.PHONY: all clean
all:
	mkdir -p $(DATA_DIR)
	wget $(KISSAT_WASM) -O $(WASM_DIR)

clean:
	rm -r $(DATA_DIR)
