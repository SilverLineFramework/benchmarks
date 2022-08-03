# Output
ROOT_DIR=../..
OUT_DIR=$(ROOT_DIR)/wasm/cortex/kmeans
DATA_DIR=$(ROOT_DIR)/data/cortex/kmeans

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(COMMON)

.PHONY: all

all: kmeans

SRCS= kmeans.c kmeans_main.c -lm

kmeans:
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_s.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_m.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_l.wasm -D SIZE=2

	mkdir -p $(DATA_DIR)
	cp finland $(DATA_DIR)/finland
	cp MNIST $(DATA_DIR)/MNIST
	cp spiral $(DATA_DIR)/spiral
