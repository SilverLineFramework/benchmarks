# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench/telecomm
DATA_DIR=$(ROOT_DIR)/data/mibench/telecomm

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

all: fft

fft:
	$(COMPILE) main.c fourierf.c fftmisc.c -o $(OUT_DIR)/fft_small.wasm
	$(COMPILE) main.c fourierf.c fftmisc.c -o $(OUT_DIR)/fft_large.wasm -D LARGE
	$(COMPILE) main.c fourierf.c fftmisc.c -o $(OUT_DIR)/invfft_small.wasm -D INV
	$(COMPILE) main.c fourierf.c fftmisc.c -o $(OUT_DIR)/invfft_large.wasm -D LARGE -D INV

clean:
	rm $(OUT_DIR)/fft_small.wasm
	rm $(OUT_DIR)/fft_large.wasm
	rm $(OUT_DIR)/invfft_small.wasm
	rm $(OUT_DIR)/invfft_large.wasm
