# Main makefile for WASM benchmarks
WAMR_COMPILER=./wasm-micro-runtime/wamr-compiler/build/wamrc
OUT_DIR=./wasm
AOT_DIR=./aot

AOT_SRCS:=$(shell find wasm -name "*.wasm")
AOT_SRCS:=$(AOT_SRCS:wasm/%=%)
AOT_OUT:=$(AOT_SRCS:%.wasm=%.aot)

# WASM: goes in ./wasm folder; also copy rustpython.wasm
wasm: dir tests polybench cortex array

dir:
	mkdir -p $(OUT_DIR)

.PHONY: tests polybench cortex array
tests:
	make -C tests
polybench:
	make -C polybench
cortex:
	make -C cortex
array:
	make -C array

# Copy rustpython to wasm folder (for distribution or AOT compilation)
rustpython:
	cp rustpython.wasm wasm

# Clean
clean:
	rm -rf $(OUT_DIR)
	rm -rf $(AOT_DIR)

# AOT: goes in ./aot folder.
aot: dir.aot $(AOT_OUT)

dir.aot:
	mkdir -p $(AOT_DIR)

$(AOT_OUT): %.aot: wasm/%.wasm
	mkdir -p $(dir aot/$@)
	$(WAMR_COMPILER) -o aot/$@ $^
