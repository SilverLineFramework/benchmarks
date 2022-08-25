# SOD does not generally require a Makefile to build. Just drop sod.c and its accompanying
# header files on your source tree and you are done.
CC = clang
CFLAGS = -lm -Ofast -march=native -Wall -std=c99

# Benchmark specific flags
WASMCFLAGS+= -I.

# Output
OUT_DIR=$(ROOT_WASM_DIR)/sod/image-processing
COMMON_DIR=$(ROOT_WASM_DIR)/sod/common

# Common files
COMMON = sod.wasm

BENCHMARKS := $(shell ls samples/rt/*.c)
WASM := $(BENCHMARKS:.c=.wasm)

.PHONY: all clean dir

all: dir $(WASM)

dir:
	mkdir -p $(OUT_DIR)
	mkdir -p $(COMMON_DIR)

sod-c: sod.c
	$(CC) sod.c samples/dilate_image.c -o sod_face_detect -I. $(CFLAGS)

$(COMMON) : %.wasm : %.c
	$(WASMCC) $(WASMCFLAGS) -D_WASI_EMULATED_MMAN -c $^ -o $(COMMON_DIR)/$@

$(WASM): %.wasm : %.c $(COMMON)
	$(eval INT_FILE = $(shell mktemp))
	$(WASMCC) $(WASMCFLAGS) $< -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_DIR)/sod.wasm \
		$(INT_FILE) -o $(OUT_DIR)/$(notdir $(basename $@)).wasm
	rm $(INT_FILE)

