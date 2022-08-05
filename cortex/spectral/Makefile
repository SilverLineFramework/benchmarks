# Output
MAIN_C= spectral.c
COMMON_C= eigen.c kmeans.c

COMMON := $(COMMON_C:.c=.wasm)
COMMON_WASM := $(addprefix $(COMMON_DIR)/, $(notdir $(COMMON)))

DATA_DIR := $(BASE_DATA_DIR)/spectral

.PHONY: all

all: spectral

$(COMMON) : %.wasm : %.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $(COMMON_DIR)/$(notdir $@)

spectral: $(COMMON)
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
	cp Aggregation $(DATA_DIR)/Aggregation
	cp D31 $(DATA_DIR)/D31
	cp R15 $(DATA_DIR)/R15
