WASMLDFLAGS+= -lm
# Output
MAIN1_C := basicmath_small.c
MAIN2_C := basicmath_large.c
SUPP_C := rad2deg.c cubic.c isqrt.c

SUPP := $(SUPP_C:.c=.wasm)
SUPP_WASM := $(addprefix $(COMMON_DIR)/, $(notdir $(SUPP)))

.PHONY: all

all: basicmath

$(SUPP) : %.wasm : %.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $(COMMON_DIR)/$(notdir $@)

basicmath: $(SUPP)
	$(eval INT_FILE = $(shell mktemp))

	$(WASMCC) $(WASMCFLAGS) $(MAIN1_C) -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_WASM) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_s.wasm

	$(WASMCC) $(WASMCFLAGS) $(MAIN2_C) -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_WASM) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_l.wasm

	rm $(INT_FILE)
