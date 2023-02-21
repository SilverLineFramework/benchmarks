COMPILE= $(WASMCC) $(WASMCLFLAGS)

.PHONY: all

all: pca

SRCS= pca.c -lm

pca:
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_s.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_m.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_l.wasm -D SIZE=2

	cp large.data $(DATA_DIR)/pca_large.data
	cp medium.data $(DATA_DIR)/pca_medium.data
	cp small.data $(DATA_DIR)/pca_small.data
