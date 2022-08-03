# Output
ROOT_DIR=../..
OUT_DIR=$(ROOT_DIR)/wasm/cortex/svd3
DATA_DIR=$(ROOT_DIR)/data/cortex/svd3

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(COMMON)

.PHONY: all

all: svd3

SRCS= main.c svd.c svd2.c common/*.c sortSVDResult.c

svd3:
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_s.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_m.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_l.wasm -D SIZE=2

	mkdir -p $(DATA_DIR)
	cp small.txt $(DATA_DIR)/small.txt
	cp med.txt $(DATA_DIR)/med.txt
	cp large.txt $(DATA_DIR)/large.txt
