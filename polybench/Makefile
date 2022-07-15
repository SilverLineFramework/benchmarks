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

# COMMON= polybench.c ../common/active.c ../common/dp.c
COMMON= polybench.c ../common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCFLAGS) $(COMMON)

# Folders must start with pb_; pulls all .c files in that directory.
BENCHMARKS := $(shell ls benchmarks/*.c)
WASM := $(BENCHMARKS:.c=.wasm)

.PHONY: all clean dir

all: dir $(WASM)

clean:
	rm -r $(OUT_DIR)_s
	rm -r $(OUT_DIR)_m

dir:
	mkdir -p $(OUT_DIR)_s
	mkdir -p $(OUT_DIR)_m
#	mkdir -p $(OUT_DIR)/large

$(WASM): %.wasm : %.c
	$(COMPILE) -D SMALL_DATASET $^ \
		-o $(OUT_DIR)_s/$(notdir $(basename $@)).wasm
	$(COMPILE) -D MEDIUM_DATASET $^ \
		-o $(OUT_DIR)_m/$(notdir $(basename $@)).wasm
#	$(COMPILE) -D LARGE_DATASET $^ \
#		-o $(OUT_DIR)/large/$(notdir $(basename $@)).wasm
