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

WASMCLDFLAGS= -Wl,-allow-undefined-file=${WAMR_SYMBOLS}
WASMCLDFLAGS+= -Wl,--no-threads,--strip-all,--no-entry
WASMCLDFLAGS+= -Wl,--export=main
WASMCLDFLAGS+= -Wl,--export=_start
WASMCLDFLAGS+= -Wl,--allow-undefined
WASMCLDFLAGS+= -Wl,-lwasi-emulated-mman

WASMLDFLAGS= -L/opt/wasi-sdk/share/wasi-sysroot/lib/wasm32-wasi /opt/wasi-sdk/share/wasi-sysroot/lib/wasm32-wasi/crt1.o
WASMLDFLAGS+= -z -Wl,-allow-undefined-file=${WAMR_SYMBOLS}
WASMLDFLAGS+= --strip-all --no-entry
WASMLDFLAGS+= --export=main --export=_start
WASMLDFLAGS+= --allow-undefined -lwasi-emulated-mman
WASMLDFLAGS+= -lc /opt/wasi-sdk/lib/clang/10.0.0/lib/wasi/libclang_rt.builtins-wasm32.a

BENCHMARKS := $(shell ls samples/image-processing/*.c)
WASM := $(BENCHMARKS:.c=.wasm)

.PHONY: all clean dir

all: dir $(WASM)

dir:
	mkdir -p $(OUT_DIR)

sod-c: sod.c
	$(CC) sod.c samples/dilate_image.c -o sod_face_detect -I. $(CFLAGS)

sod-wasm: sod.c
	$(WASMCC) -D_WASI_EMULATED_MMAN $(WASMCFLAGS) -I. sod.c samples/dilate_image.c -o sod_dilate.wasm

sod.wasm: sod.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $@

#$(WASM): %.wasm : %.c
#	$(WASMCC) $(WASMCFLAGS) $(WASMCLDFLAGS) $^ sod.c -v -o $(OUT_DIR)/$(notdir $(basename $@)).wasm 

$(WASM): %.wasm : %.c sod.wasm
	$(eval INT_FILE = $(shell mktemp))
	$(WASMCC) $(WASMCFLAGS) $< -c -o $(INT_FILE)
	wasm-ld $(WASMLDFLAGS) sod.wasm $(INT_FILE) -o $(OUT_DIR)/$(notdir $(basename $@)).wasm
	rm $(INT_FILE)
	

clean:
	rm -r $(OUT_DIR) sod.wasm
