WASM_DIR=../../wasm/mibench
DATA_DIR=../../data/mibench

.PHONY: dir all clean children

all: dir children

children:
	make -C automotive

dir:
	mkdir -p $(DATA_DIR)
	mkdir -p $(WASM_DIR)

clean:
	rm -r $(DATA_DIR)
	rm -r $(WASM_DIR)
