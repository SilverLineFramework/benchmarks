OUT_DIR=../wasm

# WAMR Setup
WAMR_DIR=../wasm-micro-runtime
WAMR_SYMBOLS=${WAMR_DIR}/wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt

WASMCC=/opt/wasi-sdk/bin/clang

WASMCFLAGS= -O0 -z
WASMCFLAGS+= -Wl,-allow-undefined-file=${WAMR_SYMBOLS}
WASMCFLAGS+= -Wl,--no-threads,--strip-all,--no-entry
WASMCFLAGS+= -Wl,--export=main
WASMCFLAGS+= -Wl,--export=_start
WASMCFLAGS+= -Wl,--allow-undefined

COMMON= ../common/active.c ../common/dp.c

COMPILE= $(WASMCC) $(WASMCFLAGS) $(COMMON)

## Instrumenting vars
instrument=0
OUT_LL_DIR=../ll
##


.PHONY: all clean dir
.SECONDARY: $(OUT_LL_DIR)/array.inst.ll

all: dir array.wasm

clean:
	rm -r $(OUT_DIR)/array.wasm


ifeq ($(instrument), 0)
dir:
	mkdir -p ../wasm

array.wasm:
	$(COMPILE) kernel.c -o $(OUT_DIR)/array.wasm

# Instrumenting code
else
WASMCFLAGS+= -Wl,--export=runtime_ctr

dir:
	mkdir -p $(OUT_DIR)
	mkdir -p $(OUT_LL_DIR)

array.wasm : $(OUT_LL_DIR)/array.inst.ll
	$(COMPILE) $^ -o $(OUT_DIR)/$@

# Instrumented LL
$(OUT_LL_DIR)/array.inst.ll: $(OUT_LL_DIR)/array.ll
	opt -load ./$(INST_DIR)/checkpoint.so -load ./$(INST_DIR)/dyn_inst_cnt.so \
	-checkpoint -dyn-inst-cnt $^ -S -o $@

# Get the source compiled down to LL
$(OUT_LL_DIR)/array.ll: array.intll
	opt $(OPT_SRC_OPTS) $^ -S -o $@
	rm $^

array.intll : kernel.c
	$(WASMCC) $(XCLANG_OPTS) $(CLANG_OPTS) -S $^ -o $@

endif

