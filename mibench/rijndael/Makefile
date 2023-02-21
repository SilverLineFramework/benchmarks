# Output
MAIN_C := aesxam.c
SUPP_C := aes.c

SUPP := $(SUPP_C:.c=.wasm)
SUPP_WASM := $(addprefix $(COMMON_DIR)/, $(notdir $(SUPP)))
LINK := $(WASMLD) $(WASMLDFLAGS) $(SUPP_WASM)

.PHONY: all

all: rijndael

$(SUPP) : %.wasm : %.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $(COMMON_DIR)/$(notdir $@)

rijndael: $(SUPP)
	$(eval TMP = $(shell mktemp))

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -D ENCODE -c -o $(TMP)
	$(LINK) $(TMP) -o $(WASM_DIR)/$@_enc_s.wasm

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -D LARGE -D ENCODE -c -o $(TMP)
	$(LINK) $(TMP) -o $(WASM_DIR)/$@_enc_l.wasm

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -c -o $(TMP)
	$(LINK) $(TMP) -o $(WASM_DIR)/$@_dec_s.wasm

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -D LARGE -c -o $(TMP)
	$(LINK) $(TMP) -o $(WASM_DIR)/$@_dec_l.wasm

	rm $(TMP)

	cp output_large.enc $(DATA_DIR)/rijndael_output_large.enc
	cp output_small.enc $(DATA_DIR)/rijndael_output_small.enc
	cp input_large.asc $(DATA_DIR)/rijndael_input_large.asc
	cp input_small.asc $(DATA_DIR)/rijndael_input_small.asc
