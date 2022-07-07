# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench/telecomm
DATA_DIR=$(ROOT_DIR)/data/mibench/telecomm

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

.PHONY: all clean

all: crc

crc: crc_32.c
	$(COMPILE) crc_32.c -o $(OUT_DIR)/crc32_small.wasm
	$(COMPILE) crc_32.c -o $(OUT_DIR)/crc32_large.wasm -D LARGE

clean:
	rm $(OUT_DIR)/crc32_small.wasm
	rm $(OUT_DIR)/crc32_large.wasm
