# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(COMMON)

.PHONY: dir

all: basicmath_small basicmath_large

# Benchmark specifics
FILE1 = basicmath_small.c rad2deg.c cubic.c isqrt.c
FILE2 = basicmath_large.c rad2deg.c cubic.c isqrt.c


basicmath_small: $(FILE1)
	$(COMPILE) $(FILE1) -o $(OUT_DIR)/basicmath_s.wasm -lm
basicmath_large: $(FILE2)
	$(COMPILE) $(FILE2) -o $(OUT_DIR)/basicmath_l.wasm -lm
