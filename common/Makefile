WASMCC=/opt/wasi-sdk/bin/clang
WASMCFLAGS= -O1

.PHONY: all clean

all: wrapper.wasm

wrapper.wasm: wrapper.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $@

clean:
	rm -f wrapper.wasm