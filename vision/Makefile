export WASM_DIR=$(ROOT_WASM_DIR)/vision
export DATA_DIR=$(ROOT_DATA_DIR)/vision
export COMMON_DIR=$(WASM_DIR)/common

COMMON_C := $(shell ls common/*.c)
COMMON := $(COMMON_C:.c=.wasm)
export COMMON_WASM := $(addprefix $(COMMON_DIR)/, $(notdir $(COMMON)))

.PHONY: all dir clean

all: dir $(COMMON)
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
	mkdir -p $(DATA_DIR)

$(COMMON) : %.wasm : %.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $(COMMON_DIR)/$(notdir $@) -lm

clean:
	rm -r $(DATA_DIR)
	rm -r $(WASM_DIR)
