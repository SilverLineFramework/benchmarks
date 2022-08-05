# Output
COMPILE= $(WASMCC) $(WASMCLFLAGS) $(WRAPPER_C)

.PHONY: dir

all:  dijkstra_large dijkstra_small data

dijkstra_large: dijkstra_large.c
	$(COMPILE) dijkstra_large.c -o $(WASM_DIR)/dijkstra_l.wasm

dijkstra_small: dijkstra_small.c
	$(COMPILE) dijkstra_small.c -o $(WASM_DIR)/dijkstra_s.wasm 

data:
	cp input.dat $(DATA_DIR)/input.dat
