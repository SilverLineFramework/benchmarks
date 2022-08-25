# Output
MAIN_C := aesxam.c
SUPP_C := aes.c

SUPP := $(SUPP_C:.c=.wasm)
SUPP_WASM := $(addprefix $(COMMON_DIR)/, $(notdir $(SUPP)))

.PHONY: all

all: rijndael
	rm $(WASM_DIR)/rijndael_dec_l.wasm

$(SUPP) : %.wasm : %.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $(COMMON_DIR)/$(notdir $@)

rijndael: $(SUPP)
	$(eval INT_FILE = $(shell mktemp))

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -D ENCODE -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_WASM) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_enc_s.wasm

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -D LARGE -D ENCODE -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_WASM) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_enc_l.wasm

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_WASM) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_dec_s.wasm

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -D LARGE -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_WASM) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_dec_l.wasm

	rm $(INT_FILE)

	cp output_large.enc $(DATA_DIR)/output_large.enc
	cp output_small.enc $(DATA_DIR)/output_small.enc
	cp input_large.asc $(DATA_DIR)/input_large.asc
	cp input_small.asc $(DATA_DIR)/input_small.asc
