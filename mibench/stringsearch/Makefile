.PHONY: all

all: search_small search_large

FILE1 = bmhasrch.c  bmhisrch.c  bmhsrch.c  pbmsrch_small.c 
FILE2 = bmhasrch.c  bmhisrch.c  bmhsrch.c  pbmsrch_large.c 

search_small: $(FILE1)
	$(WASMCC) $(WASMCFLAGS) $(FILE1) -o $(WASM_DIR)/stringsearch_s.wasm

search_large: $(FILE2)
	$(WASMCC) $(WASMCFLGS) $(FILE2) -o $(WASM_DIR)/stringsearch_l.wasm
