# Output
ROOT_DIR=../..
OUT_DIR=$(ROOT_DIR)/wasm/cortex/lda
DATA_DIR=$(ROOT_DIR)/data/cortex/lda

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

all: lda

clean:
	rm -r $(OUT_DIR)
	rm -r $(DATA_DIR)

SRCS= cokus.c lda-alpha.c lda-data.c lda-estimate.c lda-inference.c lda-model.c
SRCS+=utils.c -lm

lda:
	mkdir -p $(OUT_DIR)
	$(COMPILE) $(SRCS) -o $(OUT_DIR)/small.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(OUT_DIR)/medium.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(OUT_DIR)/large.wasm -D SIZE=2

	mkdir -p $(DATA_DIR)
	cp settings.txt $(DATA_DIR)/settings.txt
	cp small/small_data.dat $(DATA_DIR)/small_data.dat
	cp medium/medium_data.dat $(DATA_DIR)/medium_data.dat
	cp large/large_data.dat $(DATA_DIR)/large_data.dat
