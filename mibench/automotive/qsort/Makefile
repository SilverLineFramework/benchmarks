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

all: qsort_small qsort_large

clean:
	rm $(OUT_DIR)/qsort_small.wasm
	rm $(OUT_DIR)/qsort_large.wasm
	rm $(DATA_DIR)/input_small.dat
	rm $(DATA_DIR)/input_large.dat

qsort_small: qsort_small.c
	$(COMPILE) qsort_small.c -o $(OUT_DIR)/qsort_small.wasm -lm
	cp input_small.dat $(DATA_DIR)/input_small.dat
qsort_large: qsort_large.c
	$(COMPILE) qsort_large.c -o $(OUT_DIR)/qsort_large.wasm -lm
	cp input_large.dat $(DATA_DIR)/input_large.dat
