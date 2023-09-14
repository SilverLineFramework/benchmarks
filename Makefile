# --------------------------------------------------------------------------- #
#                       Silverline WASM Benchmark Suite                       #
# --------------------------------------------------------------------------- #

ifndef MODE
export MODE=wasm
endif

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

# -------------------------------- WALI-WASM mode -------------------------------- #
else ifeq ($(MODE),wali) # $MODE

### -- Configure these -- ###
LLVM_DIR=
WALI_SYSROOT_DIR=
-include config.mak
export WALI_SYSROOT_DIR
### --------------------- ###

RT_LIB=$(LLVM_DIR)/build/lib/clang/16/lib/wasi/libclang_rt.builtins-wasm32.a

CFLAGS_WARN_IGN= -Wno-implicit-function-declaration -Wno-int-conversion \
											-Wno-incompatible-function-pointer-types

WASM_EXTENSIONS= -matomics -mbulk-memory -mmutable-globals -msign-ext
 

# Compilation flags
export WASMCC=$(LLVM_DIR)/build/bin/clang
export WASMCFLAGS= -O1 -DWASM --target=wasm32-wasi-threads $(CFLAGS_WARN_IGN) \
											--sysroot=$(WALI_SYSROOT_DIR) -pthread \
											$(WASM_EXTENSIONS) -c

# Linking flags
export WASMLD=$(LLVM_DIR)/build/bin/wasm-ld
export WASMLDFLAGS= -L$(WALI_SYSROOT_DIR)/lib $(WALI_SYSROOT_DIR)/lib/crt1.o \
											--no-gc-sections --no-entry --shared-memory \
											--export-memory --import-memory --max-memory=67108864 \
											--allow-undefined -lc -lm $(RT_LIB)

# For compilation+linking
export WASMCLFLAGS= --target=wasm32-wasi-threads -O1 -pthread \
  									--sysroot=$(WALI_SYSROOT_DIR) -L$(WALI_SYSROOT_DIR)/lib \
  									$(WASM_EXTENSIONS) \
  									-Wl,--shared-memory -Wl,--export-memory -Wl,--max-memory=67108864 \

# Out: ./wasm-wali
export ROOT_WASM_DIR=$(ROOT_DIR)/wasm-wali

# Silverline mode. Enable with MODE=silverline.
ifeq ($(MODE),silverline)
export WASMCFLAGS+= -DSILVERLINE
export WASMCLFLAGS+= -DSILVERLINE
endif

# -------------------------------- WASI-WASM mode -------------------------------- #
else  # $MODE

# Compilation flags
export WASMCC=/opt/wasi-sdk/bin/clang
export WASMCFLAGS= -O1 -DWASM

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
export WASMCLFLAGS= -O1 -DWASM
export WASMCLFLAGS+= -Wl,--no-threads,--strip-all,--no-entry
export WASMCLFLAGS+= -Wl,--export=main
export WASMCLFLAGS+= -Wl,--export=_start
export WASMCLFLAGS+= -Wl,--allow-undefined

# Out: ./wasm
export ROOT_WASM_DIR=$(ROOT_DIR)/wasm

# Silverline mode. Enable with MODE=silverline.
ifeq ($(MODE),silverline)
export WASMCFLAGS+= -DSILVERLINE
export WASMCLFLAGS+= -DSILVERLINE
endif

endif  # $MODE

# -------------------------------- Benchmarks ------------------------------- #

BENCHMARKS=polybench mibench cortex vision sod loadgen libsodium apps
ifeq ($(MODE),wali) # $MODE
BENCHMARKS=wali
endif


.PHONY: wasm
wasm: $(BENCHMARKS)

.PHONY: $(BENCHMARKS)
$(BENCHMARKS):
	@echo "Building $@ in $(MODE) mode."
	make -C $@

.PHONY: clean
clean:
	rm -rf $(ROOT_WASM_DIR)
	rm -rf $(ROOT_DATA_DIR)
ifeq ($(MODE),wali)
	make -C $(BENCHMARKS) clean
endif
