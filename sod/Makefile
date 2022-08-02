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

WASMCFLAGS= -O1 -D_WASI_EMULATED_MMAN -I.

WASMLDFLAGS= -L/opt/wasi-sdk/share/wasi-sysroot/lib/wasm32-wasi /opt/wasi-sdk/share/wasi-sysroot/lib/wasm32-wasi/crt1.o
WASMLDFLAGS+= -z -Wl,-allow-undefined-file=${WAMR_SYMBOLS}
WASMLDFLAGS+= --strip-all --no-entry
WASMLDFLAGS+= --export=main --export=_start
WASMLDFLAGS+= --allow-undefined -lwasi-emulated-mman
WASMLDFLAGS+= -lc /opt/wasi-sdk/lib/clang/10.0.0/lib/wasi/libclang_rt.builtins-wasm32.a

BENCHMARKS := $(shell ls samples/rt/*.c)
WASM := $(BENCHMARKS:.c=.wasm)

.PHONY: all clean dir

all: dir $(WASM)

dir:
	mkdir -p $(OUT_DIR)

sod-c: sod.c
	$(CC) sod.c samples/dilate_image.c -o sod_face_detect -I. $(CFLAGS)

sod.wasm: sod.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $@

wrapper.wasm: wrapper.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $@

../common/wrapper.wasm: ../common/wrapper.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $@

$(WASM): %.wasm : %.c ../common/wrapper.wasm sod.wasm
	$(eval INT_FILE = $(shell mktemp))
	$(WASMCC) $(WASMCFLAGS) $< -c -o $(INT_FILE)
	wasm-ld $(WASMLDFLAGS) ../common/wrapper.wasm sod.wasm $(INT_FILE) -o $(OUT_DIR)/$(notdir $(basename $@)).wasm
	rm $(INT_FILE)
	

clean:
	rm -r $(OUT_DIR) sod.wasm wrapper.wasm
