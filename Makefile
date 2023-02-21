# Main makefile for WASM benchmarks
WAMR_COMPILER=wamrc

AOT_SRCS:=$(shell find wasm -not -path "*/common/*" -name "*.wasm")
AOT_SRCS:=$(AOT_SRCS:wasm/%=%)
AOT_OUT:=$(AOT_SRCS:%.wasm=%.aot)

# WAMR Setup
export WAMR_DIR=${PWD}/../runtime/wamr
export WAMR_SYMBOLS=${WAMR_DIR}/wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt
# Compilation flags
export WASMCC=/opt/wasi-sdk/bin/clang
export WASMCFLAGS= -O1 -nostdlib


# Linking flags
export WASMLD=/opt/wasi-sdk/bin/wasm-ld
export WASMLDFLAGS= --initial-memory=8192
export WASMLDFLAGS+= --allow-undefined
export WASMLDFLAGS+= --allow-undefined-file=${WAMR_SYMBOLS}
export WASMLDFLAGS+= --export=main
export WASMLDFLAGS+= --export=__main_argc_argv
export WASMLDFLAGS+= --strip-all --no-entry
export WASMLDFLAGS+= --export-dynamic
#export WASMLDFLAGS+= --allow-undefined -lwasi-emulated-mman
#export WASMLDFLAGS+= -lc \
#	/opt/wasi-sdk/lib/clang/14.0.4/lib/wasi/libclang_rt.builtins-wasm32.a

# For compilation+linking
export WASMCLFLAGS= --target=wasm32 -O1 -z stack-size=4096
export WASMCLFLAGS+= --sysroot=${WAMR_DIR}/wamr-sdk/app/libc-builtin-sysroot
export WASMCLFLAGS+= -Wl,--initial-memory=8192
export WASMCLFLAGS+= -Wl,--allow-undefined
export WASMCLFLAGS+= -Wl,--allow-undefined-file=${WAMR_SYMBOLS}
export WASMCLFLAGS+= -Wl,--strip-all,--no-entry
export WASMCLFLAGS+= -Wl,--export-dynamic
export WASMCLFLAGS+= -nostdlib -Ilib

# Benchmark base common: Used by benchmarks to access the wrapper
export ROOT_DIR= $(shell pwd)
export ROOT_DATA_DIR=$(ROOT_DIR)/data
export ROOT_WASM_DIR=$(ROOT_DIR)/wasm
export ROOT_AOT_DIR=$(ROOT_DIR)/aot

export WRAPPER_WASM= $(ROOT_DIR)/wasm/common/wrapper.wasm
# export WRAPPER_C= $(ROOT_DIR)/common/active.c
#export WRAPPER_C= $(ROOT_DIR)/common/passive.c
export WRAPPER_C= $(ROOT_DIR)/common/test_main.c

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

# AOT: goes in ./aot folder.
.PHONY: aot
aot: dir.aot $(AOT_OUT)

dir.aot:
	mkdir -p $(ROOT_AOT_DIR)

$(AOT_OUT): %.aot: wasm/%.wasm
	mkdir -p $(dir aot/$@)
	$(WAMR_COMPILER) --target=thumbv7 --target-abi=eabi --cpu=cortex-m7 \
  --format=aot -o aot/$@ $^
