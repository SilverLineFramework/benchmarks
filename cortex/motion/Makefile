COMPILE= $(WASMCC) $(WASMCLFLAGS)

.PHONY: all

all: motion

SRCS= App.c BmpHandler.c FullSearch.c Motion_Estimation.c -lm

motion:
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_s.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_m.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_l.wasm -D SIZE=2
	
	cp -r LR/synthetic1 $(DATA_DIR)/motion_small
	cp -r LR/alpaca $(DATA_DIR)/motion_medium
	cp -r LR/BookCase $(DATA_DIR)/motion_large
