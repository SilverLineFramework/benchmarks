export WASM_DIR=$(ROOT_WASM_DIR)/mibench
export DATA_DIR=$(ROOT_DATA_DIR)/mibench
export COMMON_DIR=$(WASM_DIR)/common

.PHONY: all dir clean

all: dir
	make -C basicmath
	make -C bitcount
	make -C qsort
	make -C stringsearch
	make -C dijkstra
	make -C patricia
	make -C blowfish
	make -C rijndael
	make -C sha
	make -C adpcm
	make -C gsm
	make -C crc32
	make -C fft

dir:
	mkdir -p $(DATA_DIR)
	mkdir -p $(WASM_DIR)
	mkdir -p $(COMMON_DIR)

clean:
	rm -r $(DATA_DIR)
	rm -r $(WASM_DIR)
