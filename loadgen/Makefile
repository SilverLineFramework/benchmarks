WASM_DIR=$(ROOT_WASM_DIR)/loadgen
SRCS=main.c matrix.c
CC=$(WASMCC) $(WASMCLFLAGS) $(SRCS)

.PHONY: loadgen dir

all: dir loadgen

dir:
	mkdir -p $(WASM_DIR)

loadgen:
	$(CC) -DPASSIVE -o $(WASM_DIR)/passive.wasm -lm
	$(CC) -DACTIVE -o $(WASM_DIR)/actor.wasm -lm
	$(CC) -DONESHOT -o $(WASM_DIR)/oneshot.wasm -lm
ifeq ($(MODE),silverline)
	$(WASMCC) $(WASMCLFLAGS) send.c -o $(WASM_DIR)/sender.wasm -lm
endif
