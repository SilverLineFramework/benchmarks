COMPILE= $(WASMCC) $(WASMCFLAGS)

.PHONY: all small large

SRCS = patricia.c patricia_test.c

all: small large

small:
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/patricia_s.wasm
	cp small.udp $(DATA_DIR)/patricia_small.udp

large:
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/patricia_l.wasm -D LARGE
	cp large.udp $(DATA_DIR)/patricia_large.udp
