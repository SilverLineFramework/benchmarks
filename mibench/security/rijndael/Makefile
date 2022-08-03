# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench
DATA_DIR=$(ROOT_DIR)/data/mibench/security

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(COMMON)

.PHONY: dir rijndael

all: rijndael
	rm $(OUT_DIR)/rijndael_dec_l.wasm

rijndael:
	$(COMPILE) aes.c aesxam.c -o $(OUT_DIR)/rijndael_enc_s.wasm -D ENCODE
	$(COMPILE) aes.c aesxam.c -o $(OUT_DIR)/rijndael_enc_l.wasm -D LARGE -D ENCODE
	$(COMPILE) aes.c aesxam.c -o $(OUT_DIR)/rijndael_dec_s.wasm
	$(COMPILE) aes.c aesxam.c -o $(OUT_DIR)/rijndael_dec_l.wasm -D LARGE

	cp output_large.enc $(DATA_DIR)/output_large.enc
	cp output_small.enc $(DATA_DIR)/output_small.enc
