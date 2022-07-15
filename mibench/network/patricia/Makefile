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

.PHONY: all

all: patricia_small patricia_large

patricia_small: patricia.c patricia_test.c
	$(COMPILE) patricia.c patricia_test.c -o $(OUT_DIR)/patricia_s.wasm
	cp small.udp $(DATA_DIR)/small.udp

patricia_large: patricia.c patricia_test.c
	$(COMPILE) patricia.c patricia_test.c -o $(OUT_DIR)/patricia_l.wasm
	cp large.udp $(DATA_DIR)/large.udp
