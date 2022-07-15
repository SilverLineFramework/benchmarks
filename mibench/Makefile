WASM_DIR=../wasm/mibench
DATA_DIR=../data/mibench

.PHONY: all clean

all:
	mkdir -p $(DATA_DIR)
	mkdir -p $(WASM_DIR)
	make -C automotive
	make -C network
	make -C telecomm
	make -C security

clean:
	rm -r $(DATA_DIR)
	rm -r $(WASM_DIR)
