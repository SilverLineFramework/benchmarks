WASM_DIR=../wasm/cortex
DATA_DIR=../data/cortex

.PHONY: all clean

all:
	mkdir -p $(DATA_DIR)
	mkdir -p $(WASM_DIR)
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
