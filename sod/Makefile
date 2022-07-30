# SOD does not generally require a Makefile to build. Just drop sod.c and its accompanying
# header files on your source tree and you are done.
CC = clang
CFLAGS = -lm -Ofast -march=native -Wall -std=c99

WASMCC=/opt/wasi-sdk/bin/clang

WASMCFLAGS= -O1 -z
#WASMCFLAGS+= -Wl,-allow-undefined-file=${WAMR_SYMBOLS}
WASMCFLAGS+= -Wl,--no-threads,--strip-all,--no-entry
WASMCFLAGS+= -Wl,--export=main
WASMCFLAGS+= -Wl,--export=_start
WASMCFLAGS+= -Wl,--allow-undefined
WASMCFLAGS+= -Wl,-lwasi-emulated-mman

all: sod-wasm

sod: sod.c
	$(CC) sod.c samples/dilate_image.c -o sod_face_detect -I. $(CFLAGS)

sod-wasm: sod.c
	$(WASMCC) -D_WASI_EMULATED_MMAN $(WASMCFLAGS) -I. sod.c samples/dilate_image.c -o sod_dilate.wasm
