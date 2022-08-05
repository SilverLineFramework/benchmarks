# Output
MAIN_C := main.c
COMMON_C := svd.c svd2.c sortSVDResult.c $(shell ls common/*.c)

COMMON := $(COMMON_C:.c=.wasm)
COMMON_WASM := $(addprefix $(COMMON_DIR)/, $(notdir $(COMMON)))

DATA_DIR := $(BASE_DATA_DIR)/svd3

.PHONY: all

all: svd3

$(COMMON) : %.wasm : %.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $(COMMON_DIR)/$(notdir $@)

svd3: $(COMMON)
	$(eval INT_FILE = $(shell mktemp))

	$(WASMCC) $(WASMCFLAGS) -D SIZE=0 $(MAIN_C) -c -o $(INT_FILE)
	wasm-ld $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_s.wasm

	$(WASMCC) $(WASMCFLAGS) -D SIZE=1 $(MAIN_C) -c -o $(INT_FILE)
	wasm-ld $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_m.wasm

	$(WASMCC) $(WASMCFLAGS) -D SIZE=2 $(MAIN_C) -c -o $(INT_FILE)
	wasm-ld $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_l.wasm

	rm $(INT_FILE)

	mkdir -p $(DATA_DIR)
	cp small.txt $(DATA_DIR)/small.txt
	cp med.txt $(DATA_DIR)/med.txt
	cp large.txt $(DATA_DIR)/large.txt
