# Main makefile for WASM benchmarks
WAMR_COMPILER=./wasm-micro-runtime/wamr-compiler/build/wamrc

# Compilation flags
export WASMCC=/opt/wasi-sdk/bin/clang
export WASMCFLAGS= -O1

# Linking flags
export WASMLD=/opt/wasi-sdk/bin/wasm-ld
export WASMLDFLAGS= -L/opt/wasi-sdk/share/wasi-sysroot/lib/wasm32-wasi \
	/opt/wasi-sdk/share/wasi-sysroot/lib/wasm32-wasi/crt1.o
export WASMLDFLAGS+= --strip-all --no-entry
export WASMLDFLAGS+= --export=main --export=_start
export WASMLDFLAGS+= --allow-undefined -lwasi-emulated-mman
export WASMLDFLAGS+= -lc \
	/opt/wasi-sdk/lib/clang/10.0.0/lib/wasi/libclang_rt.builtins-wasm32.a

# For compilation+linking
export WASMCLFLAGS= -O1
export WASMCLFLAGS+= -Wl,--no-threads,--strip-all,--no-entry
export WASMCLFLAGS+= -Wl,--export=main
export WASMCLFLAGS+= -Wl,--export=_start
export WASMCLFLAGS+= -Wl,--allow-undefined

# Benchmark base common: Used by benchmarks to access the wrapper
export ROOT_DIR= $(shell pwd)
export ROOT_DATA_DIR=$(ROOT_DIR)/data
export ROOT_WASM_DIR=$(ROOT_DIR)/wasm

# WASM: goes in ./wasm folder
.PHONY: wasm
wasm: polybench mibench cortex vision sod

.PHONY: tests polybench mibench cortex vision
tests:
	make -C tests
polybench:
	make -C polybench
mibench:
	make -C mibench
cortex:
	make -C cortex
vision:
	make -C vision

sod:
	make -C sod

# Clean
.PHONY: clean
clean:
	rm -rf $(ROOT_WASM_DIR)
	rm -rf $(ROOT_DATA_DIR)
