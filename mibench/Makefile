export WASM_DIR=$(ROOT_WASM_DIR)/mibench
export BASE_DATA_DIR=$(ROOT_DATA_DIR)/mibench
export COMMON_DIR=$(ROOT_WASM_DIR)/common

.PHONY: all dir clean

all: dir
	mkdir -p $(BASE_DATA_DIR)
	mkdir -p $(WASM_DIR)
	make -C automotive
	make -C network
	make -C telecomm
	make -C security

dir:
	mkdir -p $(COMMON_DIR)

clean:
	rm -r $(BASE_DATA_DIR)
	rm -r $(WASM_DIR)
