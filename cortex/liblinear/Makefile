COMPILE= $(WASMCC) $(WASMCLFLAGS)

.PHONY: all

all: liblinear

SRCS= linear.c train.c tron.c blas/*.c -lm

liblinear:
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_s.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_m.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_l.wasm -D SIZE=2

	cp data/1M/iris_cut $(DATA_DIR)/liblinear_small
	cp data/10M/surgery $(DATA_DIR)/liblinear_medium
	cp data/100M/crime_scale $(DATA_DIR)/liblinear_large
