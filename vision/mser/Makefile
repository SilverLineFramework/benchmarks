# Output
MAIN_C := src/script_mser.c
SUPP_C := $(filter-out $(MAIN_C), $(shell ls src/*.c))

SUPP := $(SUPP_C:.c=.wasm)
SUPP_WASM := $(addprefix $(COMMON_DIR)/, $(notdir $(SUPP)))

.PHONY: all

all: mser

$(SUPP) : %.wasm : %.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $(COMMON_DIR)/$(notdir $@)

mser: $(SUPP)
	$(eval INT_FILE = $(shell mktemp))

	$(WASMCC) $(WASMCFLAGS) -D SIZE=0 -D sqcif $(MAIN_C) -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_WASM) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_s.wasm -lm

	$(WASMCC) $(WASMCFLAGS) -D SIZE=1 -D qcif $(MAIN_C) -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_WASM) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_m.wasm -lm

	$(WASMCC) $(WASMCFLAGS) -D SIZE=2 -D cif $(MAIN_C) -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(WRAPPER_WASM) $(COMMON_WASM) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_l.wasm -lm

	rm $(INT_FILE)

	mkdir -p $(DATA_DIR)/mser
	cp -r data/sqcif $(DATA_DIR)/mser
	cp -r data/qcif $(DATA_DIR)/mser
	cp -r data/cif $(DATA_DIR)/mser
