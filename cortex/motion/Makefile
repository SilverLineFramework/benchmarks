# Output
ROOT_DIR=../..
OUT_DIR=$(ROOT_DIR)/wasm/cortex/motion
DATA_DIR=$(ROOT_DIR)/data/cortex/motion

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(COMMON)

.PHONY: all

all: motion

SRCS= App.c BmpHandler.c FullSearch.c Motion_Estimation.c -lm

motion:
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_s.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_m.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_l.wasm -D SIZE=2

	mkdir -p $(DATA_DIR)
	cp -r LR/synthetic1 $(DATA_DIR)/synthetic1
	cp -r LR/alpaca $(DATA_DIR)/alpaca
	cp -r LR/BookCase $(DATA_DIR)/BookCase
