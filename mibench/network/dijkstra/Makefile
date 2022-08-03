# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench
DATA_DIR=$(ROOT_DIR)/data/mibench/network

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(COMMON)

.PHONY: dir

all:  dijkstra_large dijkstra_small data

dijkstra_large: dijkstra_large.c
	$(COMPILE) dijkstra_large.c -o $(OUT_DIR)/dijkstra_l.wasm

dijkstra_small: dijkstra_small.c
	$(COMPILE) dijkstra_small.c -o $(OUT_DIR)/dijkstra_s.wasm 

data:
	cp input.dat $(DATA_DIR)/input.dat
