WAMR_COMPILER=./wasm-micro-runtime/wamr-compiler/build/wamrc
OUT_DIR=./wasm
AOT_DIR=./aot

AOT_SRCS:=$(shell find wasm -name "*.wasm")
AOT_SRCS:=$(AOT_SRCS:wasm/%=%)
AOT_OUT:=$(AOT_SRCS:%.wasm=%.aot)

# Clean
clean: clean.aot clean.wasm

clean.aot:
	rm -rf $(AOT_DIR)

clean.wasm:
	rm -rf $(OUT_DIR)

# WASM: goes in ./wasm folder; also copy rustpython.wasm
wasm: dir.wasm wasm-apps polybench

dir.wasm:
	mkdir -p $(OUT_DIR)
	cp rustpython.wasm $(OUT_DIR)

.PHONY: wasm-apps polybench
wasm-apps:
	make -C wasm-apps

polybench:
	make -C polybench

# AOT: goes in ./aot folder.
aot: dir.aot $(AOT_OUT)

dir.aot:
	mkdir -p $(AOT_DIR)

$(AOT_OUT): %.aot: wasm/%.wasm
	mkdir -p $(dir aot/$@)
	$(WAMR_COMPILER) -o aot/$@ $^
