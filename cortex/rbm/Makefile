# Output
ROOT_DIR=../..
OUT_DIR=$(ROOT_DIR)/wasm/cortex/rbm
DATA_DIR=$(ROOT_DIR)/data/cortex/rbm

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(COMMON)

.PHONY: all

all: rbm

SRCS= main.c twister.c -lm

rbm:
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_s.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_m.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_l.wasm -D SIZE=2

	mkdir -p $(DATA_DIR)
	cp data.txt $(DATA_DIR)/data.txt
