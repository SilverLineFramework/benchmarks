# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench
DATA_DIR=$(ROOT_DIR)/data/mibench/automotive

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(COMMON)

.PHONY: all

all: qsort_small qsort_large

qsort_small: qsort_small.c
	$(COMPILE) qsort_small.c -o $(OUT_DIR)/qsort_s.wasm -lm
	cp input_small.dat $(DATA_DIR)/input_small.dat
qsort_large: qsort_large.c
	$(COMPILE) qsort_large.c -o $(OUT_DIR)/qsort_l.wasm -lm
	cp input_large.dat $(DATA_DIR)/input_large.dat
