OUT_DIR=../wasm/tests

WAMR_DIR=../wasm-micro-runtime
WAMR_SYMBOLS=${WAMR_DIR}/wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt

WASMCC=/opt/wasi-sdk/bin/clang

WASMCFLAGS= -O0
WASMCFLAGS+= -Wl,--allow-undefined-file=${WAMR_SYMBOLS}
WASMCFLAGS+= -Wl,--no-threads,--strip-all,--no-entry
WASMCFLAGS+= -Wl,--export=main
WASMCFLAGS+= -Wl,--export=_start
WASMCFLAGS+= -Wl,--allow-undefined

## Instrumenting vars
instrument=0

INST_DIR=../instrumentation
OUT_LL_DIR=../ll/tests

XCLANG_OPTS = -Xclang -disable-O0-optnone
CLANG_OPTS = -O0 -emit-llvm
OPT_SRC_OPTS = -mem2reg -loop-simplify
##


SRCS := $(shell ls *.c)
WASM := $(SRCS:%.c=%.wasm)

.PHONY: all clean dir
.SECONDARY: $(wildcard $(OUT_LL_DIR)/*.inst.ll) $(wildcard $(OUT_LL_DIR)/%.ll)

all: dir $(WASM)

clean:
	rm -r $(OUT_DIR)


ifeq ($(instrument), 0)
dir:
	mkdir -p $(OUT_DIR)

%.wasm : %.c
	${WASMCC} ${WASMCFLAGS} $^ -o $(OUT_DIR)/$@

# Instrumenting code
else
WASMCFLAGS+= -Wl,--export=runtime_ctr

dir:
	mkdir -p $(OUT_DIR)
	mkdir -p $(OUT_LL_DIR)

%.wasm : $(OUT_LL_DIR)/%.inst.ll
	$(WASMCC) $(WASMCFLAGS) $^ -o $(OUT_DIR)/$@

# Instrumented LL
$(OUT_LL_DIR)/%.inst.ll: $(OUT_LL_DIR)/%.ll
	opt -load ./$(INST_DIR)/checkpoint.so -load ./$(INST_DIR)/dyn_inst_cnt.so \
	-checkpoint -dyn-inst-cnt $^ -S -o $@

# Get the source compiled down to LL
$(OUT_LL_DIR)/%.ll: %.intll
	opt $(OPT_SRC_OPTS) $^ -S -o $@

%.intll : %.c
	$(WASMCC) $(XCLANG_OPTS) $(CLANG_OPTS) -S $^ -o $@

endif
