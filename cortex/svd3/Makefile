# Output
ROOT_DIR=../..
OUT_DIR=$(ROOT_DIR)/wasm/cortex/svd3
DATA_DIR=$(ROOT_DIR)/data/cortex/svd3

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

all: svd3

clean:
	rm -r $(OUT_DIR)
	rm -r $(DATA_DIR)

SRCS= main.c svd.c svd2.c common/*.c sortSVDResult.c

svd3:
	mkdir -p $(OUT_DIR)
	$(COMPILE) $(SRCS) -o $(OUT_DIR)/small.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(OUT_DIR)/medium.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(OUT_DIR)/large.wasm -D SIZE=2

	mkdir -p $(DATA_DIR)
	cp small.txt $(DATA_DIR)/small.txt
	cp med.txt $(DATA_DIR)/med.txt
	cp large.txt $(DATA_DIR)/large.txt
