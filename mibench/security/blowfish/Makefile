# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench
DATA_DIR=$(ROOT_DIR)/data/mibench/security

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(COMMON)

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
