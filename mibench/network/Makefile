WASM_DIR=../../wasm/mibench/network
DATA_DIR=../../data/mibench/network

.PHONY: dir all clean children

all: dir children

children:
	make -C dijkstra
	make -C patricia

dir:
	mkdir -p $(DATA_DIR)
	mkdir -p $(WASM_DIR)

clean:
	rm -r $(DATA_DIR)
	rm -r $(WASM_DIR)
