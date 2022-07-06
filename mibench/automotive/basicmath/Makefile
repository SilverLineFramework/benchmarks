# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench/automotive

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

all: basicmath_small basicmath_large

clean:
	rm $(OUT_DIR)/basicmath_large.wasm
	rm $(OUT_DIR)/basicmath_small.wasm

# Benchmark specifics
FILE1 = basicmath_small.c rad2deg.c cubic.c isqrt.c
FILE2 = basicmath_large.c rad2deg.c cubic.c isqrt.c


basicmath_small: $(FILE1)
	$(COMPILE) $(FILE1) -o $(OUT_DIR)/basicmath_small.wasm -lm
basicmath_large: $(FILE2)
	$(COMPILE) $(FILE2) -o $(OUT_DIR)/basicmath_large.wasm -lm
