# Output
ROOT_DIR=../..
OUT_DIR=$(ROOT_DIR)/wasm/cortex/spectral
DATA_DIR=$(ROOT_DIR)/data/cortex/spectral

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(COMMON)

.PHONY: all

all: spectral

SRCS= eigen.c kmeans.c spectral.c -lm

spectral:
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_s.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_m.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(OUT_DIR)_l.wasm -D SIZE=2

	mkdir -p $(DATA_DIR)
	cp Aggregation $(DATA_DIR)/Aggregation
	cp D31 $(DATA_DIR)/D31
	cp R15 $(DATA_DIR)/R15
