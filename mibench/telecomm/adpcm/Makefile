# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench
DATA_DIR=$(ROOT_DIR)/data/mibench/telecomm

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(COMMON)

.PHONY: all pcm adpcm data

all: pcm adpcm data

pcm:
	$(COMPILE) -o $(OUT_DIR)/adpcm_enc_s.wasm src/rawcaudio.c src/adpcm.c
	$(COMPILE) -o $(OUT_DIR)/adpcm_enc_l.wasm src/rawcaudio.c src/adpcm.c -D LARGE

adpcm:
	$(COMPILE) -o $(OUT_DIR)/adpcm_dec_s.wasm src/rawdaudio.c src/adpcm.c
	$(COMPILE) -o $(OUT_DIR)/adpcm_dec_l.wasm src/rawdaudio.c src/adpcm.c -D LARGE

data:
	cp data/large.adpcm $(DATA_DIR)/large.adpcm
	cp data/large.pcm $(DATA_DIR)/large.pcm
	cp data/small.adpcm $(DATA_DIR)/small.adpcm
	cp data/small.pcm $(DATA_DIR)/small.pcm
