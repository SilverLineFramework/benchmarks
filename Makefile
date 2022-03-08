# Main makefile for WASM benchmarks

OUT_DIR=./wasm

# WASM: goes in ./wasm folder; also copy rustpython.wasm
wasm: dir tests polybench

dir:
	mkdir -p $(OUT_DIR)
	cp rustpython.wasm $(OUT_DIR)

.PHONY: tests polybench cortex
tests:
	make -C tests
polybench:
	make -C polybench
cortex:
	make -C cortex

# Clean
clean:
	rm -rf $(OUT_DIR)
