# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench/network
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

.PHONY: dir clean

all: patricia_small patricia_large

clean:
	rm $(OUT_DIR)/patricia_small.wasm
	rm $(OUT_DIR)/patricia_large.wasm

patricia_small: patricia.c patricia_test.c
	$(COMPILE) patricia.c patricia_test.c -o $(OUT_DIR)/patricia_small.wasm
	cp small.udp $(DATA_DIR)/small.udp

patricia_large: patricia.c patricia_test.c
	$(COMPILE) patricia.c patricia_test.c -o $(OUT_DIR)/patricia_large.wasm
	cp large.udp $(DATA_DIR)/large.udp
