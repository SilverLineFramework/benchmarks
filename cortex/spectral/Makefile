# Output
MAIN_C= spectral.c
COMMON_C= eigen.c kmeans.c

COMMON := $(COMMON_C:.c=.wasm)
COMMON_WASM := $(addprefix $(COMMON_DIR)/, $(notdir $(COMMON)))

.PHONY: all

all: spectral

$(COMMON) : %.wasm : %.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $(COMMON_DIR)/$(notdir $@)

spectral: $(COMMON)
	$(eval INT_FILE = $(shell mktemp))

	$(WASMCC) $(WASMCFLAGS) -D SIZE=0 $(MAIN_C) -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(COMMON_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_s.wasm

	$(WASMCC) $(WASMCFLAGS) -D SIZE=1 $(MAIN_C) -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(COMMON_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_m.wasm

	$(WASMCC) $(WASMCFLAGS) -D SIZE=2 $(MAIN_C) -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(COMMON_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_l.wasm

	rm $(INT_FILE)

	cp D31 $(DATA_DIR)/spectral_large
	cp Aggregation $(DATA_DIR)/spectral_medium
	cp R15 $(DATA_DIR)/spectral_small
