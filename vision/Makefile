export WASM_DIR=$(shell pwd)/../wasm/vision
export BASE_DATA_DIR=$(shell pwd)/../data/vision
export COMMON_DIR=$(WASM_DIR)/common

COMMON_C := $(shell ls common/*.c)
COMMON := $(COMMON_C:.c=.wasm)
export COMMON_WASM := $(addprefix $(COMMON_DIR)/, $(notdir $(COMMON)))

.PHONY: all dir clean

all: dir $(COMMON)
	mkdir -p $(BASE_DATA_DIR)
	make -C disparity
	make -C localization
	make -C mser
	make -C multi_ncut
	make -C sift
	make -C stitch
	make -C svm
	make -C texture
	make -C tracking

dir:
	mkdir -p $(COMMON_DIR)
	echo $(COMMON)

$(COMMON) : %.wasm : %.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $(COMMON_DIR)/$(notdir $@)

clean:
	rm -r $(BASE_DATA_DIR)
	rm -r $(WASM_DIR)
