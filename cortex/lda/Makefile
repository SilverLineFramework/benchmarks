COMPILE= $(WASMCC) $(WASMCLFLAGS)

.PHONY: all

all: lda

SRCS= cokus.c lda-alpha.c lda-data.c lda-estimate.c lda-inference.c lda-model.c
SRCS+=utils.c -lm

lda:
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_s.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_m.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_l.wasm -D SIZE=2

	cp settings.txt $(DATA_DIR)/lda_settings.txt
	cp small/small_data.dat $(DATA_DIR)/lda_small.dat
	cp medium/medium_data.dat $(DATA_DIR)/lda_medium.dat
	cp large/large_data.dat $(DATA_DIR)/lda_large.dat
