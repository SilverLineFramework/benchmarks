WASM_DIR=../../wasm/mibench/automotive
DATA_DIR=../../data/mibench/automotive

.PHONY: dir all clean children

all: dir children

children:
	make -C basicmath
	make -C bitcount
	make -C qsort
	make -C susan

dir:
	mkdir -p $(DATA_DIR)
	mkdir -p $(WASM_DIR)

clean:
	rm -r $(DATA_DIR)
	rm -r $(WASM_DIR)
