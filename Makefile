# Main makefile for WASM benchmarks
WAMR_COMPILER=./wasm-micro-runtime/wamr-compiler/build/wamrc

AOT_SRCS:=$(shell find wasm -not -path "*/common/*" -name "*.wasm")
AOT_SRCS:=$(AOT_SRCS:wasm/%=%)
AOT_OUT:=$(AOT_SRCS:%.wasm=%.aot)

# WAMR Setup
export WAMR_DIR=$(shell pwd)/wasm-micro-runtime
export WAMR_SYMBOLS=${WAMR_DIR}/wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt

# Compilation flags
export WASMCC=/opt/wasi-sdk/bin/clang
export WASMCFLAGS= -O1

# Linking flags
export WASMLD=/opt/wasi-sdk/bin/wasm-ld
export WASMLDFLAGS= -L/opt/wasi-sdk/share/wasi-sysroot/lib/wasm32-wasi \
	/opt/wasi-sdk/share/wasi-sysroot/lib/wasm32-wasi/crt1.o
export WASMLDFLAGS+= -z -Wl,-allow-undefined-file=${WAMR_SYMBOLS}
export WASMLDFLAGS+= --strip-all --no-entry
export WASMLDFLAGS+= --export=main --export=_start
export WASMLDFLAGS+= --allow-undefined -lwasi-emulated-mman
export WASMLDFLAGS+= -lc \
	/opt/wasi-sdk/lib/clang/10.0.0/lib/wasi/libclang_rt.builtins-wasm32.a

# For compilation+linking
export WASMCLFLAGS= -O1
export WASMCLFLAGS+= -Wl,--allow-undefined-file=${WAMR_SYMBOLS}
export WASMCLFLAGS+= -Wl,--no-threads,--strip-all,--no-entry
export WASMCLFLAGS+= -Wl,--export=main
export WASMCLFLAGS+= -Wl,--export=_start
export WASMCLFLAGS+= -Wl,--allow-undefined

# Benchmark base common: Used by benchmarks to access the wrapper
export ROOT_DIR= $(shell pwd)
export ROOT_DATA_DIR=$(ROOT_DIR)/data
export ROOT_WASM_DIR=$(ROOT_DIR)/wasm
export ROOT_AOT_DIR=$(ROOT_DIR)/aot

export WRAPPER_WASM= $(ROOT_DIR)/wasm/common/wrapper.wasm
export WRAPPER_C= $(ROOT_DIR)/common/wrapper.c

# WASM: goes in ./wasm folder
.PHONY: wasm
wasm: polybench mibench cortex vision sod

.PHONY: common
common:
	make -C common

.PHONY: tests polybench mibench cortex vision sod
tests: common
	make -C tests
polybench: common
	make -C polybench
mibench: common
	make -C mibench
cortex: common
	make -C cortex
vision: common
	make -C vision
sod: common
	make -C sod

# Copy rustpython to wasm folder (for distribution or AOT compilation)
.PHONY: rustpython
rustpython: wasm/rustpython.wasm
wasm/rustpython.wasm: rustpython.wasm
	cp rustpython.wasm wasm

# Clean
.PHONY: clean
clean:
	rm -rf $(ROOT_WASM_DIR)
	rm -rf $(ROOT_AOT_DIR)
	rm -rf $(ROOT_DATA_DIR)

# AOT: goes in ./aot folder.
.PHONY: aot
aot: dir.aot $(AOT_OUT)

dir.aot:
	mkdir -p $(ROOT_AOT_DIR)

$(AOT_OUT): %.aot: wasm/%.wasm
	mkdir -p $(dir aot/$@)
	$(WAMR_COMPILER) --instrument --opt-level=1 -o aot/$@ $^
