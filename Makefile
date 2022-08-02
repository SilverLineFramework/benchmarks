# Main makefile for WASM benchmarks
WAMR_COMPILER=./wasm-micro-runtime/wamr-compiler/build/wamrc
OUT_DIR=./wasm
AOT_DIR=./aot

AOT_SRCS:=$(shell find wasm -name "*.wasm")
AOT_SRCS:=$(AOT_SRCS:wasm/%=%)
AOT_OUT:=$(AOT_SRCS:%.wasm=%.aot)

# WAMR Setup
export WAMR_DIR=../wasm-micro-runtime
export WAMR_SYMBOLS=${WAMR_DIR}/wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt

export WASMCC=/opt/wasi-sdk/bin/clang
export WASMCFLAGS= -O1 -D_WASI_EMULATED_MMAN -I.

export WASMLDFLAGS= -L/opt/wasi-sdk/share/wasi-sysroot/lib/wasm32-wasi /opt/wasi-sdk/share/wasi-sysroot/lib/wasm32-wasi/crt1.o
export WASMLDFLAGS+= -z -Wl,-allow-undefined-file=${WAMR_SYMBOLS}
export WASMLDFLAGS+= --strip-all --no-entry
export WASMLDFLAGS+= --export=main --export=_start
export WASMLDFLAGS+= --allow-undefined -lwasi-emulated-mman
export WASMLDFLAGS+= -lc /opt/wasi-sdk/lib/clang/10.0.0/lib/wasi/libclang_rt.builtins-wasm32.a
export WASMCFLAGS= -O1 -D_WASI_EMULATED_MMAN -I.


# WASM: goes in ./wasm folder; also copy rustpython.wasm
wasm: dir polybench mibench cortex vision sod

dir:
	mkdir -p $(OUT_DIR)

.PHONY: common tests polybench cortex array mibench vision sod

common:
	make -C common

tests: common
	make -C tests
array:
	make -C array
polybench:
	make -C polybench
mibench:
	make -C mibench
cortex:
	make -C cortex
vision:
	make -C vision
sod: common
	make -C sod

# Copy rustpython to wasm folder (for distribution or AOT compilation)
rustpython:
	cp rustpython.wasm wasm

# Clean
clean:
	rm -rf $(OUT_DIR)
	rm -rf $(AOT_DIR)
	make -C common clean

# AOT: goes in ./aot folder.
aot: dir.aot $(AOT_OUT)

dir.aot:
	mkdir -p $(AOT_DIR)

$(AOT_OUT): %.aot: wasm/%.wasm
	mkdir -p $(dir aot/$@)
	$(WAMR_COMPILER) --instrument --opt-level=1 -o aot/$@ $^
