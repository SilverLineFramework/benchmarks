# Output
MAIN_C := main.c
SUPP_C := fourierf.c fftmisc.c

SUPP := $(SUPP_C:.c=.wasm)
SUPP_WASM := $(addprefix $(COMMON_DIR)/, $(notdir $(SUPP)))

.PHONY: all

all: fft

$(SUPP) : %.wasm : %.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $(COMMON_DIR)/$(notdir $@)

fft: $(SUPP)
	$(eval INT_FILE = $(shell mktemp))

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_s.wasm -lm

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -D LARGE -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_l.wasm -lm

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -D INV -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/inv$@_s.wasm -lm

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -D LARGE -D INV -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/inv$@_l.wasm -lm

	rm $(INT_FILE)
