# Output
COMPILE= $(WASMCC) $(WASMCLFLAGS) $(WRAPPER_C)

.PHONY: all

all: crc

crc: crc_32.c
	$(COMPILE) crc_32.c -o $(WASM_DIR)/crc32_s.wasm
	$(COMPILE) crc_32.c -o $(WASM_DIR)/crc32_l.wasm -D LARGE
