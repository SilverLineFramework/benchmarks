export WASM_DIR=$(ROOT_WASM_DIR)/cortex
export BASE_DATA_DIR=$(ROOT_DATA_DIR)/cortex
export COMMON_DIR=$(WASM_DIR)/common

.PHONY: all clean

all:
	mkdir -p $(BASE_DATA_DIR)
	mkdir -p $(COMMON_DIR)
	make -C svd3
	make -C kmeans
	make -C spectral
	make -C pca
	make -C lda
	make -C motion
	make -C rbm
	make -C liblinear

clean:
	rm -r $(BASE_DATA_DIR)
	rm -r $(WASM_DIR)
