OUT_DIR=../wasm/apps

WAMR_DIR=../wasm-micro-runtime
WAMR_SYMBOLS=${WAMR_DIR}/wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt

WASMCC=/opt/wasi-sdk/bin/clang

WASMCFLAGS= -O0
WASMCFLAGS+= -Wl,--allow-undefined-file=${WAMR_SYMBOLS}
WASMCFLAGS+= -Wl,--no-threads,--strip-all,--no-entry
WASMCFLAGS+= -Wl,--export=main
WASMCFLAGS+= -Wl,--export=_start
WASMCFLAGS+= -Wl,--allow-undefined

SRCS := $(shell ls *.c)
WASM := $(SRCS:%.c=%.wasm)

.PHONY: all clean dir

all: dir $(WASM)

clean:
	rm -r $(OUT_DIR)

dir:
	mkdir -p $(OUT_DIR)

%.wasm : %.c
	${WASMCC} ${WASMCFLAGS} $^ -o $(OUT_DIR)/$@
