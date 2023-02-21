# Output
COMPILE= $(WASMCC) $(WASMCLFLAGS)

.PHONY: dir sha

all: sha

sha:
	$(COMPILE) sha.c sha_driver.c -o $(WASM_DIR)/sha_s.wasm
	$(COMPILE) sha.c sha_driver.c -o $(WASM_DIR)/sha_l.wasm -D LARGE
	cp input_small.asc $(DATA_DIR)/sha_small.asc
	cp input_large.asc $(DATA_DIR)/sha_large.asc
