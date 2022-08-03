# Output
ROOT_DIR=../..
OUT_DIR=$(ROOT_DIR)/wasm/cortex/pca
DATA_DIR=$(ROOT_DIR)/data/cortex/pca

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(COMMON)

.PHONY: all

all: pca

SRCS= pca.c -lm

pca:
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_s.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_m.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_l.wasm -D SIZE=2

	mkdir -p $(DATA_DIR)
	cp large.data $(DATA_DIR)/large.data
	cp medium.data $(DATA_DIR)/medium.data
	cp small.data $(DATA_DIR)/small.data
