# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(COMMON)

.PHONY: all

all: crc

crc: crc_32.c
	$(COMPILE) crc_32.c -o $(OUT_DIR)/crc32_s.wasm
	$(COMPILE) crc_32.c -o $(OUT_DIR)/crc32_l.wasm -D LARGE
