# Output
MAIN_C= main.c
COMMON_C= svd.c svd2.c sortSVDResult.c $(shell ls common/*.c)

COMMON := $(COMMON_C:.c=.wasm)
DATA_DIR := $(BASE_DATA_DIR)/svd3

.PHONY: all

all: dir svd3

dir:
	mkdir -p $(COMMON_DIR)

$(COMMON) : %.wasm : %.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $(COMMON_DIR)/$(notdir $@)

svd3: $(COMMON)
	$(eval COMMON_WASM = $(shell ls $(COMMON_DIR)/*.wasm))

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
	cp small.txt $(DATA_DIR)/small.txt
	cp med.txt $(DATA_DIR)/med.txt
	cp large.txt $(DATA_DIR)/large.txt
