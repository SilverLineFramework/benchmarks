# Output
ROOT_DIR=../..
OUT_DIR=$(ROOT_DIR)/wasm/cortex/liblinear
DATA_DIR=$(ROOT_DIR)/data/cortex/liblinear

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(COMMON)

.PHONY: all

all: liblinear

SRCS= linear.c train.c tron.c blas/*.c -lm

liblinear:
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_s.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_m.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_l.wasm -D SIZE=2

	mkdir -p $(DATA_DIR)
	cp data/1M/iris_cut $(DATA_DIR)/iris_cut
	cp data/10M/surgery $(DATA_DIR)/surgery
	cp data/100M/crime_scale $(DATA_DIR)/crime_scale
