WASM_DIR=../wasm/vision
DATA_DIR=../data/vision

.PHONY: all clean

all:
	mkdir -p $(DATA_DIR)
	mkdir -p $(WASM_DIR)
	make -C disparity
	make -C localization
	make -C mser
	make -C multi_ncut
	make -C sift
	make -C stitch
	make -C svm
	make -C texture
	make -C tracking

clean:
	rm -r $(DATA_DIR)
	rm -r $(WASM_DIR)
