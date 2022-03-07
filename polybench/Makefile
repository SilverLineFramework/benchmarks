# Output
OUT_DIR=../wasm/polybench

# WAMR Setup
WAMR_DIR=../wasm-micro-runtime
WAMR_SYMBOLS=${WAMR_DIR}/wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt

WASMCC=/opt/wasi-sdk/bin/clang

WASMCFLAGS= -O0 -z
WASMCFLAGS+= -Wl,-allow-undefined-file=${WAMR_SYMBOLS}
WASMCFLAGS+= -Wl,--no-threads,--strip-all,--no-entry
WASMCFLAGS+= -Wl,--export=main
WASMCFLAGS+= -Wl,--export=_start
WASMCFLAGS+= -Wl,--allow-undefined

COMMON= polybench.c ../common/runtime.c ../common/dp.c

COMPILE= $(WASMCC) $(WASMCFLAGS) -D LARGE_DATASET $(COMMON)

# Folders must start with pb_; pulls all .c files in that directory.
BENCHMARKS := $(shell ls benchmarks/*.c)
WASM := $(BENCHMARKS:.c=.wasm)

.PHONY: all clean dir

all: dir $(WASM)

clean:
	rm -r $(OUT_DIR)

dir:
	mkdir -p $(OUT_DIR)

$(WASM): %.wasm : %.c
	$(COMPILE) $^ -o $(OUT_DIR)/$(notdir $(basename $@)).wasm
