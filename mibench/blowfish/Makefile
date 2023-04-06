# Output
MAIN_C := bf.c
SUPP_C := bf_cbc.c bf_cfb64.c bf_ecb.c bf_enc.c bf_ofb64.c bf_skey.c bf_pi.c

SUPP := $(SUPP_C:.c=.wasm)
SUPP_WASM := $(addprefix $(COMMON_DIR)/, $(notdir $(SUPP)))

.PHONY: all

all: blowfish

$(SUPP) : %.wasm : %.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $(COMMON_DIR)/$(notdir $@)

blowfish: $(SUPP)
	$(eval INT_FILE = $(shell mktemp))

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -D ENCODE -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_enc_s.wasm

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -D LARGE -D ENCODE -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_enc_l.wasm

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_dec_s.wasm

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -D LARGE -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_dec_l.wasm

	rm $(INT_FILE)

	cp output_large_bf.enc $(DATA_DIR)/bf_dec_large.enc
	cp output_small_bf.enc $(DATA_DIR)/bf_dec_small.enc
	cp input_large.asc $(DATA_DIR)/bf_enc_large.asc
	cp input_small.asc $(DATA_DIR)/bf_enc_small.asc

