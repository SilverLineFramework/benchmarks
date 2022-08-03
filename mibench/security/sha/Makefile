# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench
DATA_DIR=$(ROOT_DIR)/data/mibench/security

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(COMMON)

.PHONY: dir sha

all: sha

sha:
	$(COMPILE) sha.c sha_driver.c -o $(OUT_DIR)/sha_s.wasm
	$(COMPILE) sha.c sha_driver.c -o $(OUT_DIR)/sha_l.wasm -D LARGE
	cp input_small.asc $(DATA_DIR)/input_small.asc
	cp input_large.asc $(DATA_DIR)/input_large.asc
