# Output
DATA_DIR=$(BASE_DATA_DIR)/pca

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(WRAPPER_C)

.PHONY: all

all: pca

SRCS= pca.c -lm

pca:
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_s.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_m.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_l.wasm -D SIZE=2

	mkdir -p $(DATA_DIR)
	cp large.data $(DATA_DIR)/large.data
	cp medium.data $(DATA_DIR)/medium.data
	cp small.data $(DATA_DIR)/small.data
