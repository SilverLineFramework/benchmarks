# Output
ROOT_DIR=../..
OUT_DIR=$(ROOT_DIR)/wasm/vision/mser
DATA_DIR=$(ROOT_DIR)/data/vision/mser

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(COMMON)

.PHONY: all

all: mser

SRCS= src/*.c ../common/*.c

mser:
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_s.wasm -D SIZE=0 -D sqcif
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_m.wasm -D SIZE=1 -D qcif
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_l.wasm -D SIZE=2 -D cif

	mkdir -p $(DATA_DIR)
	cp -r data/sqcif $(DATA_DIR)
	cp -r data/qcif $(DATA_DIR)
	cp -r data/cif $(DATA_DIR)
