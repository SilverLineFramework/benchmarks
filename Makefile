# Main makefile for WASM benchmarks
WAMR_COMPILER=./wasm-micro-runtime/wamr-compiler/build/wamrc
OUT_DIR=./wasm
AOT_DIR=./aot
LL_DIR=./ll

AOT_SRCS:=$(shell find wasm -name "*.wasm")
AOT_SRCS:=$(AOT_SRCS:wasm/%=%)
AOT_OUT:=$(AOT_SRCS:%.wasm=%.aot)

# Instrumentation variables
instrument=0
export INST_DIR=../instrumentation
export XCLANG_OPTS = -Xclang -disable-O0-optnone
export CLANG_OPTS = -O0 -emit-llvm
export OPT_SRC_OPTS = -mem2reg -loop-simplify


# WASM: goes in ./wasm folder; also copy rustpython.wasm
wasm: dir tests polybench cortex array

wasm-instrument: instrument=1
wasm-instrument: dir instrumentation tests polybench cortex array

dir:
	mkdir -p $(OUT_DIR)

.PHONY: instrumentation tests polybench cortex array
instrumentation:
	make -C instrumentation
tests:
	make -C tests instrument=$(instrument)
polybench:
	make -C polybench instrument=$(instrument)
cortex:
	make -C cortex instrument=$(instrument)
array:
	make -C array instrument=$(instrument)

# Copy rustpython to wasm folder (for distribution or AOT compilation)
rustpython:
	cp rustpython.wasm wasm

# Clean
clean:
	rm -rf $(OUT_DIR)
	rm -rf $(AOT_DIR)
	rm -rf $(LL_DIR)
	#make -C instrumentation clean

# AOT: goes in ./aot folder.
aot: dir.aot $(AOT_OUT)

dir.aot:
	mkdir -p $(AOT_DIR)

$(AOT_OUT): %.aot: wasm/%.wasm
	mkdir -p $(dir aot/$@)
	$(WAMR_COMPILER) -o aot/$@ $^
