# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench/automotive
DATA_DIR=$(ROOT_DIR)/data/mibench/automotive

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

all: susan

clean:
	rm $(OUT_DIR)/susan_*.wasm
	rm $(DATA_DIR)/input_small.pgm
	rm $(DATA_DIR)/input_large.pgm

susan: susan.c
	cp input_small.pgm $(DATA_DIR)/input_small.pgm
	cp input_large.pgm $(DATA_DIR)/input_large.pgm
	$(COMPILE) -o $(OUT_DIR)/susan_small_0.wasm susan.c -lm -D MODE=0
	$(COMPILE) -o $(OUT_DIR)/susan_small_1.wasm susan.c -lm -D MODE=1
	$(COMPILE) -o $(OUT_DIR)/susan_small_2.wasm susan.c -lm -D MODE=2
	$(COMPILE) -o $(OUT_DIR)/susan_large_0.wasm susan.c -lm -D LARGE -D MODE=0
	$(COMPILE) -o $(OUT_DIR)/susan_large_1.wasm susan.c -lm -D LARGE -D MODE=1
	$(COMPILE) -o $(OUT_DIR)/susan_large_2.wasm susan.c -lm -D LARGE -D MODE=2
