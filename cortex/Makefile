export WASM_DIR=$(shell pwd)/../wasm/cortex
export BASE_DATA_DIR=$(shell pwd)/../data/cortex
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
	rm -r $(DATA_DIR)
	rm -r $(WASM_DIR)
