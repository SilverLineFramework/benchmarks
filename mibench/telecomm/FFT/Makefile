# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(COMMON)

.PHONY: all

all: fft

fft:
	$(COMPILE) main.c fourierf.c fftmisc.c -o $(OUT_DIR)/fft_s.wasm
	$(COMPILE) main.c fourierf.c fftmisc.c -o $(OUT_DIR)/fft_l.wasm -D LARGE
	$(COMPILE) main.c fourierf.c fftmisc.c -o $(OUT_DIR)/invfft_s.wasm -D INV
	$(COMPILE) main.c fourierf.c fftmisc.c -o $(OUT_DIR)/invfft_l.wasm -D LARGE -D INV
