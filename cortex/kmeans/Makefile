# Output
DATA_DIR=$(BASE_DATA_DIR)/kmeans

COMPILE= $(WASMCC) $(WASMCLFLAGS) $(WRAPPER_C)

.PHONY: all

all: kmeans

SRCS= kmeans.c kmeans_main.c -lm

kmeans:
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_s.wasm -D SIZE=0
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_m.wasm -D SIZE=1
	$(COMPILE) $(SRCS) -o $(WASM_DIR)/$@_l.wasm -D SIZE=2

	mkdir -p $(DATA_DIR)
	cp finland $(DATA_DIR)/finland
	cp MNIST $(DATA_DIR)/MNIST
	cp spiral $(DATA_DIR)/spiral
