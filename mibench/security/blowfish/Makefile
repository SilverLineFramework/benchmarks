# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench
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

.PHONY: blowfish

all: blowfish

SOURCES=bf.c bf_cbc.c bf_cfb64.c bf_ecb.c bf_enc.c bf_ofb64.c bf_skey.c

blowfish:
	$(COMPILE) $(SOURCES) -o $(OUT_DIR)/blowfish_enc_s.wasm -D ENCODE
	$(COMPILE) $(SOURCES) -o $(OUT_DIR)/blowfish_enc_l.wasm -D LARGE -D ENCODE
	$(COMPILE) $(SOURCES) -o $(OUT_DIR)/blowfish_dec_s.wasm
	$(COMPILE) $(SOURCES) -o $(OUT_DIR)/blowfish_dec_l.wasm -D LARGE

	cp output_large_bf.enc $(DATA_DIR)/output_large_bf.enc
	cp output_small_bf.enc $(DATA_DIR)/output_small_bf.enc
