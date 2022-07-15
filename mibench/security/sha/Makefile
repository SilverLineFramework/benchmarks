# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench
DATA_DIR=$(ROOT_DIR)/data/mibench/security

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

.PHONY: dir sha

all: sha

sha:
	$(COMPILE) sha.c sha_driver.c -o $(OUT_DIR)/sha_s.wasm
	$(COMPILE) sha.c sha_driver.c -o $(OUT_DIR)/sha_l.wasm -D LARGE
	cp input_small.asc $(DATA_DIR)/input_small.asc
	cp input_large.asc $(DATA_DIR)/input_large.asc
