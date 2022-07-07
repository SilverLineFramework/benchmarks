WASM_DIR=../../wasm/mibench/telecomm
DATA_DIR=../../data/mibench/telecomm

.PHONY: dir all clean children

all: dir children

children:
	make -C adpcm
	make -C CRC32
	make -C FFT
	make -C gsm

dir:
	mkdir -p $(DATA_DIR)
	mkdir -p $(WASM_DIR)

clean:
	rm -r $(DATA_DIR)
	rm -r $(WASM_DIR)
