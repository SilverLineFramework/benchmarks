# SOD does not generally require a Makefile to build. Just drop sod.c and its accompanying
# header files on your source tree and you are done.
CC = clang
CFLAGS = -lm -Ofast -march=native -Wall -std=c99

# Output
OUT_DIR=../wasm/sod/image-processing

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

$(WASM): %.wasm : %.c sod.wasm
	$(eval INT_FILE = $(shell mktemp))
	$(WASMCC) $(WASMCFLAGS) $< -c -o $(INT_FILE)
	wasm-ld $(WASMLDFLAGS) ../common/wrapper.wasm sod.wasm $(INT_FILE) -o $(OUT_DIR)/$(notdir $(basename $@)).wasm
	rm $(INT_FILE)
	

clean:
	rm -r $(OUT_DIR) sod.wasm
