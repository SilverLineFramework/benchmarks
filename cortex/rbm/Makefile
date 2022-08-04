# Output
DATA_DIR=$(BASE_DATA_DIR)/rbm

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(WRAPPER_C)

.PHONY: all

all: rbm

SRCS= main.c twister.c -lm

rbm:
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_s.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_m.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_l.wasm -D SIZE=2

	mkdir -p $(DATA_DIR)
	cp data.txt $(DATA_DIR)/data.txt
