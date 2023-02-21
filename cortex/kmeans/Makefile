COMPILE= $(WASMCC) $(WASMCLFLAGS)

.PHONY: all

all: kmeans

SRCS= kmeans.c kmeans_main.c -lm

kmeans:
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_s.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_m.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_l.wasm -D SIZE=2

	cp finland $(DATA_DIR)/kmeans_small
	cp MNIST $(DATA_DIR)/kmeans_medium
	cp spiral $(DATA_DIR)/kmeans_large
