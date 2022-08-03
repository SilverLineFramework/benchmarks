WASMCC=/opt/wasi-sdk/bin/clang
WASMCFLAGS= -O1

.PHONY: all clean

all: wrapper.wasm passive.wasm

wrapper.wasm: wrapper.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $@

passive.wasm: passive.c
	$(WASMCC) $(WASMCFLAGS) -D PROFILE_PASSIVE -c $^ -o $@

clean:
	rm -f *.wasm