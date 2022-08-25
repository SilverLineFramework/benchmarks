# Output
COMPILE= $(WASMCC) $(WASMCLFLAGS) $(WRAPPER_C)

.PHONY: all

all: bitcnts

FILE = bitcnt_1.c bitcnt_2.c bitcnt_3.c bitcnt_4.c bitcnts.c bitfiles.c bitstrng.c bstr_i.c 

bitcnts: $(FILE)
	$(COMPILE) $(FILE) -o $(WASM_DIR)/bitcnts.wasm
