# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench
DATA_DIR=$(ROOT_DIR)/data/mibench/network

# WAMR Setup
WAMR_DIR=$(ROOT_DIR)/wasm-micro-runtime
WAMR_SYMBOLS=$(WAMR_DIR)/wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt

WASMCC=/opt/wasi-sdk/bin/clang

WASMCFLAGS= -O0 -z
WASMCFLAGS+= -Wl,-allow-undefined-file=$(WAMR_SYMBOLS)
WASMCFLAGS+= -Wl,--no-threads,--strip-all,--no-entry
WASMCFLAGS+= -Wl,--export=main
WASMCFLAGS+= -Wl,--export=_start
WASMCFLAGS+= -Wl,--allow-undefined

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCFLAGS) $(COMMON)

.PHONY: dir

all:  dijkstra_large dijkstra_small data

dijkstra_large: dijkstra_large.c
	$(COMPILE) dijkstra_large.c -o $(OUT_DIR)/dijkstra_l.wasm

dijkstra_small: dijkstra_small.c
	$(COMPILE) dijkstra_small.c -o $(OUT_DIR)/dijkstra_s.wasm 

data:
	cp input.dat $(DATA_DIR)/input.dat
