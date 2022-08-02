CC = clang

WASMCC=/opt/wasi-sdk/bin/clang

WASMCFLAGS= -O1

all: wrapper.wasm

wrapper.wasm: wrapper.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $@

clean:
	rm wrapper.wasm
