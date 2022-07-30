# SOD does not generally require a Makefile to build. Just drop sod.c and its accompanying
# header files on your source tree and you are done.
CC = clang
CFLAGS = -lm -Ofast -march=native -Wall -std=c99

# Output
OUT_DIR=../wasm/sod/image-processing

# WAMR Setup
WAMR_DIR=../wasm-micro-runtime
WAMR_SYMBOLS=${WAMR_DIR}/wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt

WASMCC=/opt/wasi-sdk/bin/clang

WASMCFLAGS= -O1 -z
WASMCFLAGS+= -Wl,-allow-undefined-file=${WAMR_SYMBOLS}
WASMCFLAGS+= -Wl,--no-threads,--strip-all,--no-entry
WASMCFLAGS+= -Wl,--export=main
WASMCFLAGS+= -Wl,--export=_start
WASMCFLAGS+= -Wl,--allow-undefined
WASMCFLAGS+= -Wl,-lwasi-emulated-mman

WASMINCS= -I.
WASMDEFS= -D_WASI_EMULATED_MMAN

BENCHMARKS := $(shell ls samples/image-processing/*.c)
WASM := $(BENCHMARKS:.c=.wasm)

.PHONY: all clean dir

all: dir $(WASM)

dir:
	mkdir -p $(OUT_DIR)

sod: sod.c
	$(CC) sod.c samples/dilate_image.c -o sod_face_detect -I. $(CFLAGS)

sod-wasm: sod.c
	$(WASMCC) -D_WASI_EMULATED_MMAN $(WASMCFLAGS) -I. sod.c samples/dilate_image.c -o sod_dilate.wasm


$(WASM): %.wasm : %.c
	$(WASMCC) $(WASMCFLAGS) $(WASMDEFS) $(WASMINCS) $^ -o $(OUT_DIR)/$(notdir $(basename $@)).wasm 


clean:
	rm -r $(OUT_DIR)
