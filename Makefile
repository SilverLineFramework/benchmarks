WAMR_COMPILER=./wasm-micro-runtime/wamr-compiler/build/wamrc
OUT_DIR=./wasm-out

AOT_SRCS:=$(shell find wasm-out -name "*.wasm")
AOT_OUT:=$(AOT_SRCS:%.wasm=%.aot)

.PHONY: all clean dir

all: dir wasm-apps polybench

clean:
	rm -r $(OUT_DIR)

dir:
	mkdir -p $(OUT_DIR)

.PHONY: wasm-apps
wasm-apps:
	make -C wasm-apps

.PHONY: polybench
polybench:
	make -C polybench

aot: $(AOT_OUT)

rustpython.aot: rustpython.aot
	$(WAMR_COMPILER) -o $(OUT_DIR)/rustpython.aot rustpython.wasm

%.aot: %.wasm
	$(WAMR_COMPILER) -o $@ $^
