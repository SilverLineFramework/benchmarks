# Output
COMPILE= $(WASMCC) $(WASMCLFLAGS) $(WRAPPER_C)

.PHONY: all pcm adpcm data

all: pcm adpcm data

pcm:
	$(COMPILE) -o $(WASM_DIR)/adpcm_enc_s.wasm src/rawcaudio.c src/adpcm.c
	$(COMPILE) -o $(WASM_DIR)/adpcm_enc_l.wasm src/rawcaudio.c src/adpcm.c -D LARGE

adpcm:
	$(COMPILE) -o $(WASM_DIR)/adpcm_dec_s.wasm src/rawdaudio.c src/adpcm.c
	$(COMPILE) -o $(WASM_DIR)/adpcm_dec_l.wasm src/rawdaudio.c src/adpcm.c -D LARGE

data:
	cp data/large.adpcm $(DATA_DIR)/large.adpcm
	cp data/large.pcm $(DATA_DIR)/large.pcm
	cp data/small.adpcm $(DATA_DIR)/small.adpcm
	cp data/small.pcm $(DATA_DIR)/small.pcm
