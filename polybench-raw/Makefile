# Output

# WAMR Setup
WAMR_DIR=../wasm-micro-runtime
WAMR_SYMBOLS=${WAMR_DIR}/wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt

WASMCC=/opt/wasi-sdk/bin/clang

WASMCFLAGS= -O0 -z
WASMCFLAGS+= -Wl,-allow-undefined-file=${WAMR_SYMBOLS}
WASMCFLAGS+= -Wl,--no-threads,--strip-all,--no-entry
WASMCFLAGS+= -Wl,--export-all
WASMCFLAGS+= -Wl,--allow-undefined

# Instrumentation
instrument=0
threshold=30

OUT_LL_DIR=../ll/polybench-raw
INST_DIR=../instrumentation
CLANG_OPTS= -O0 -emit-llvm -fno-discard-value-names
OPT_SRC_OPTS= -mem2reg -loop-simplify
SRC_C_DIR=benchmarks
#

COMMON= polybench.c

COMPILE= $(WASMCC) $(WASMCFLAGS) $(COMMON)

# Folders must start with pb_; pulls all .c files in that directory.
BENCHMARKS := $(shell ls benchmarks/*.c)
WASM := $(BENCHMARKS:.c=.wasm)

.PHONY: all clean dir
.SECONDARY: $(wildcard $(OUT_LL_DIR)/*.inst.ll)

all: dir $(WASM)

clean:
	rm -r $(OUT_DIR)

dir:
	mkdir -p $(OUT_DIR)/small
	mkdir -p $(OUT_DIR)/medium
	mkdir -p $(OUT_DIR)/large
	mkdir -p $(OUT_LL_DIR)

ifeq ($(instrument), 1)
OUT_DIR=../wasm/polybench-raw-inst

COMPILE= $(WASMCC) $(WASMCFLAGS)
# Finally compile down to WASM
$(WASM): benchmarks/%.wasm : $(OUT_LL_DIR)/%.inst.ll
#	$(COMPILE) -D SMALL_DATASET $^ \
		-o $(OUT_DIR)/small/$(notdir $(basename $@)).wasm
	$(COMPILE) -D MEDIUM_DATASET $^ \
		-o $(OUT_DIR)/medium/$(notdir $(basename $@)).wasm
#	$(COMPILE) -D LARGE_DATASET $^ \
		-o $(OUT_DIR)/large/$(notdir $(basename $@)).wasm


# Instrumented LL
$(OUT_LL_DIR)/%.inst.ll: $(OUT_LL_DIR)/%.ll
	opt -load ./$(INST_DIR)/weighted-checkpoint.so -weighted-checkpoint -threshold $(threshold) $^ -S -o $@

# Linked LL
$(OUT_LL_DIR)/%.ll: $(OUT_LL_DIR)/%.unlinkedll $(OUT_LL_DIR)/polybench.ll
	llvm-link $^ -S -o $@
	rm $<

# Source to LL
$(OUT_LL_DIR)/%.unlinkedll: %.intll 
	opt $(OPT_SRC_OPTS) $^ -S -o $@
	rm $^

# Polybench compilation
$(OUT_LL_DIR)/polybench.ll: polybench.intll
	opt $(OPT_SRC_OPTS) $^ -S -o $@

polybench.intll : polybench.c
	$(WASMCC) $(CLANG_OPTS) -S $^ -o $@
#

%.intll : $(SRC_C_DIR)/%.c
	$(WASMCC) -D MEDIUM_DATASET $(CLANG_OPTS) -S $^ -o $@

else
OUT_DIR=../wasm/polybench-raw

$(WASM): %.wasm : %.c
#	$(COMPILE) -D SMALL_DATASET $^ \
		-o $(OUT_DIR)/small/$(notdir $(basename $@)).wasm
	$(COMPILE) -D MEDIUM_DATASET $^ \
		-o $(OUT_DIR)/medium/$(notdir $(basename $@)).wasm
#	$(COMPILE) -D LARGE_DATASET $^ \
		-o $(OUT_DIR)/large/$(notdir $(basename $@)).wasm

endif
