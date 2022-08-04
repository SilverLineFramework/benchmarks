# Output
DATA_DIR=$(BASE_DATA_DIR)/motion

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(WRAPPER_C)

.PHONY: all

all: motion

SRCS= App.c BmpHandler.c FullSearch.c Motion_Estimation.c -lm

motion:
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_s.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_m.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_l.wasm -D SIZE=2
	
	mkdir -p $(DATA_DIR)
	cp -r LR/synthetic1 $(DATA_DIR)/synthetic1
	cp -r LR/alpaca $(DATA_DIR)/alpaca
	cp -r LR/BookCase $(DATA_DIR)/BookCase
