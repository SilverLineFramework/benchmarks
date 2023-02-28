OUT_DIR=../wasm/tests

#SRCS := $(shell ls *.c)
SRCS := counter.c helloworld.c
WASM := $(SRCS:%.c=%.wasm)

.PHONY: all clean dir

all: dir $(WASM)

clean:
	rm -r $(OUT_DIR)

dir:
	mkdir -p $(OUT_DIR)

%.wasm : %.c
	${WASMCC} ${WASMCLFLAGS} $^ -o $(OUT_DIR)/$@

