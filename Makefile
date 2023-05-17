# --------------------------------------------------------------------------- #
#                       Silverline WASM Benchmark Suite                       #
# --------------------------------------------------------------------------- #

# ------------------------ Root / common directories ------------------------ #
export ROOT_DIR= $(shell pwd)
# Out: ./data
export ROOT_DATA_DIR=$(ROOT_DIR)/data

# ------------------------------- Native mode ------------------------------- #
ifeq ($(MODE),native)

# Compilation flags
export WASMCC=gcc
export WASMCFLAGS=-O1

# Linking flags
export WASMLD=gcc
export WASMLDFLAGS=

# Compilation + linking
export WASMCLFLAGS=

# Out: ./native
export ROOT_WASM_DIR=$(ROOT_DIR)/native

# -------------------------------- WASM mode -------------------------------- #
else  # $MODE

# Compilation flags
export WASMCC=/opt/wasi-sdk/bin/clang
export WASMCFLAGS= -O1 -DSILVERLINE -DWASM

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
export WASMCLFLAGS= -O1 -DSILVERLINE -DWASM
export WASMCLFLAGS+= -Wl,--no-threads,--strip-all,--no-entry
export WASMCLFLAGS+= -Wl,--export=main
export WASMCLFLAGS+= -Wl,--export=_start
export WASMCLFLAGS+= -Wl,--allow-undefined

# Out: ./wasm
export ROOT_WASM_DIR=$(ROOT_DIR)/wasm

endif  # $MODE

# -------------------------------- Benchmarks ------------------------------- #

.PHONY: wasm
wasm: polybench mibench cortex vision sod loadgen

.PHONY: polybench mibench cortex vision sod loadgen
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
loadgen:
	make -C loadgen

.PHONY: clean
clean:
	rm -rf $(ROOT_WASM_DIR)
	rm -rf $(ROOT_DATA_DIR)
