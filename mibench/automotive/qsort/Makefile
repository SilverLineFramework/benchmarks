# Output
COMPILE= $(WASMCC) $(WASMCLFLAGS) $(WRAPPER_C)

.PHONY: all

all: qsort_small qsort_large

qsort_small: qsort_small.c
	$(COMPILE) qsort_small.c -o $(WASM_DIR)/qsort_s.wasm -lm
	cp input_small.dat $(DATA_DIR)/input_small.dat

qsort_large: qsort_large.c
	$(COMPILE) qsort_large.c -o $(WASM_DIR)/qsort_l.wasm -lm
	cp input_large.dat $(DATA_DIR)/input_large.dat
