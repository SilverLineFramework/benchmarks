# Output
MAIN_C= spectral.c
COMMON_C= eigen.c kmeans.c

COMMON := $(COMMON_C:.c=.wasm)
DATA_DIR := $(BASE_DATA_DIR)/spectral

.PHONY: all

all: spectral

$(COMMON) : %.wasm : %.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $(COMMON_DIR)/$(notdir $@)

spectral: $(COMMON)
	$(eval INT_FILE_S = $(shell mktemp))
	$(WASMCC) $(WASMCFLAGS) -D SIZE=0 $(MAIN_C) -c -o $(INT_FILE_S)
	wasm-ld $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_WASM) \
		$(INT_FILE_S) -o $(WASM_DIR)/$@_s.wasm
	rm $(INT_FILE_S)

	$(eval INT_FILE_M = $(shell mktemp))
	$(WASMCC) $(WASMCFLAGS) -D SIZE=0 $(MAIN_C) -c -o $(INT_FILE_M)
	wasm-ld $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_WASM) \
		$(INT_FILE_M) -o $(WASM_DIR)/$@_m.wasm
	rm $(INT_FILE_M)

	$(eval INT_FILE_L = $(shell mktemp))
	$(WASMCC) $(WASMCFLAGS) -D SIZE=0 $(MAIN_C) -c -o $(INT_FILE_L)
	wasm-ld $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_WASM) \
		$(INT_FILE_L) -o $(WASM_DIR)/$@_l.wasm
	rm $(INT_FILE_L)


	mkdir -p $(DATA_DIR)
	cp Aggregation $(DATA_DIR)/Aggregation
	cp D31 $(DATA_DIR)/D31
	cp R15 $(DATA_DIR)/R15
