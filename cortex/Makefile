WASM_DIR=../../wasm/cortex
DATA_DIR=../../data/cortex

.PHONY: dir all clean children

all: dir children

children:
	make -C svd3
	make -C kmeans
	make -C spectral
	make -C pca
	make -C lda
	make -C motion
	make -C rbm

dir:
	mkdir -p $(DATA_DIR)
	mkdir -p $(WASM_DIR)

clean:
	rm -r $(DATA_DIR)
	rm -r $(WASM_DIR)
