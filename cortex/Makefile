WASM_DIR=../../wasm/cortex
DATA_DIR=../../data/cortex

.PHONY: dir all clean children

all: dir children

children:
	make -C svd3
dir:
	mkdir -p $(DATA_DIR)
	mkdir -p $(WASM_DIR)

clean:
	rm -r $(DATA_DIR)
	rm -r $(WASM_DIR)
