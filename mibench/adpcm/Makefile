# Output
COMPILE= $(WASMCC) $(WASMCLFLAGS)

.PHONY: all pcm adpcm data

all: pcm adpcm data

pcm:
	$(COMPILE) -o $(WASM_DIR)/adpcm_enc_s.wasm src/rawcaudio.c src/adpcm.c
	$(COMPILE) -o $(WASM_DIR)/adpcm_enc_l.wasm src/rawcaudio.c src/adpcm.c -D LARGE

adpcm:
	$(COMPILE) -o $(WASM_DIR)/adpcm_dec_s.wasm src/rawdaudio.c src/adpcm.c
	$(COMPILE) -o $(WASM_DIR)/adpcm_dec_l.wasm src/rawdaudio.c src/adpcm.c -D LARGE

data:
	cp data/large.adpcm $(DATA_DIR)/adpcm_large.adpcm
	cp data/large.pcm $(DATA_DIR)/adpcm_large.pcm
	cp data/small.adpcm $(DATA_DIR)/adpcm_small.adpcm
	cp data/small.pcm $(DATA_DIR)/adpcm_small.pcm
