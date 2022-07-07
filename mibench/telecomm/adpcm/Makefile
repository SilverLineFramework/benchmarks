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

.PHONY: all clean pcm adpcm data

all: pcm adpcm data

clean:
	rm $(OUT_DIR)/adpcm_enc_small.wasm
	rm $(OUT_DIR)/adpcm_enc_large.wasm
	rm $(OUT_DIR)/adpcm_dec_small.wasm
	rm $(OUT_DIR)/adpcm_dec_large.wasm

pcm:
	$(COMPILE) -o $(OUT_DIR)/adpcm_enc_small.wasm src/rawcaudio.c src/adpcm.c
	$(COMPILE) -o $(OUT_DIR)/adpcm_enc_large.wasm src/rawcaudio.c src/adpcm.c -D LARGE

adpcm:
	$(COMPILE) -o $(OUT_DIR)/adpcm_dec_small.wasm src/rawdaudio.c src/adpcm.c
	$(COMPILE) -o $(OUT_DIR)/adpcm_dec_large.wasm src/rawdaudio.c src/adpcm.c -D LARGE

data:
	cp data/large.adpcm $(DATA_DIR)/large.adpcm
	cp data/large.pcm $(DATA_DIR)/large.pcm
	cp data/small.adpcm $(DATA_DIR)/small.adpcm
	cp data/small.pcm $(DATA_DIR)/small.pcm
