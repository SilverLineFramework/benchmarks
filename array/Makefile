# WAMR Setup
WAMR_DIR=../wasm-micro-runtime
WAMR_SYMBOLS=${WAMR_DIR}/wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt

WASMCC=/opt/wasi-sdk/bin/clang

WASMCFLAGS= -O0 -z
WASMCFLAGS+= -Wl,-allow-undefined-file=${WAMR_SYMBOLS}
WASMCFLAGS+= -Wl,--no-threads,--strip-all,--no-entry
WASMCFLAGS+= -Wl,--export=main
WASMCFLAGS+= -Wl,--export=_start
WASMCFLAGS+= -Wl,--allow-undefined

COMMON= ../common/active.c ../common/dp.c

COMPILE= $(WASMCC) $(WASMCFLAGS) $(COMMON)

.PHONY: all clean dir

all: dir array.wasm

clean:
	rm -r ../wasm/array.wasm

dir:
	mkdir -p ../wasm

array.wasm:
	$(COMPILE) kernel.c -o ../wasm/array.wasm
