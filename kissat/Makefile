WASM_DIR=$(ROOT_WASM_DIR)/kissat.wasm
DATA_DIR=$(ROOT_DATA_DIR)/kissat
KISSAT_WASM=https://github.com/thetianshuhuang/kissat-wasm/releases/download/v3.1.0/kissat.wasm
SATLIB_3SAT=https://github.com/thetianshuhuang/kissat-wasm/releases/download/v3.1.0/3sat.tar
SATLIB_FLAT=https://github.com/thetianshuhuang/kissat-wasm/releases/download/v3.1.0/flat.tar

.PHONY: all clean
all:
	mkdir -p $(DATA_DIR)
	wget $(KISSAT_WASM) -O $(WASM_DIR)

	wget $(SATLIB_3SAT) -O $(DATA_DIR)/3sat.tar
	cd $(DATA_DIR); tar -xzf 3sat.tar
	rm $(DATA_DIR)/3sat.tar

	wget $(SATLIB_FLAT) -O $(DATA_DIR)/flat.tar
	cd $(DATA_DIR); tar -xzf flat.tar
	rm $(DATA_DIR)/flat.tar

clean:
	rm -r $(DATA_DIR)
