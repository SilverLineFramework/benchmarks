# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench/security
DATA_DIR=$(ROOT_DIR)/data/mibench/security

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

.PHONY: dir clean rijndael

all: rijndael

clean:
	rm $(OUT_DIR)/rijndael_enc_small.wasm
	rm $(OUT_DIR)/rijndael_enc_large.wasm
	rm $(OUT_DIR)/rijndael_dec_small.wasm
	rm $(OUT_DIR)/rijndael_dec_large.wasm

rijndael:
	$(COMPILE) aes.c aesxam.c -o $(OUT_DIR)/rijndael_enc_small.wasm -D ENCODE
	$(COMPILE) aes.c aesxam.c -o $(OUT_DIR)/rijndael_enc_large.wasm -D LARGE -D ENCODE
	$(COMPILE) aes.c aesxam.c -o $(OUT_DIR)/rijndael_dec_small.wasm
	$(COMPILE) aes.c aesxam.c -o $(OUT_DIR)/rijndael_dec_large.wasm -D LARGE

	cp output_large.enc $(DATA_DIR)/output_large.enc
	cp output_small.enc $(DATA_DIR)/output_small.enc
