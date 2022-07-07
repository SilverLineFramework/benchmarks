WASM_DIR=../../wasm/mibench/security
DATA_DIR=../../data/mibench/security

.PHONY: dir all clean children

all: dir children

children:
	make -C sha
	make -C rijndael
	make -C blowfish

dir:
	mkdir -p $(DATA_DIR)
	mkdir -p $(WASM_DIR)

clean:
	rm -r $(DATA_DIR)
	rm -r $(WASM_DIR)
