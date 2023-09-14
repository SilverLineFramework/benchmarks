SUITE_NAME := datarace-oneshot
OUT_DIR= $(WALI_DIR)/$(SUITE_NAME)

SRCS := $(wildcard *.c)
WASMS := $(SRCS:.c=.wasm)

COMPILE := $(WASMCC) $(WASMCLFLAGS)

.PHONY: all dir

all: dir $(WASMS)

dir:
	mkdir -p $(OUT_DIR)

%.wasm: %.c
	$(COMPILE) -llfds711 $< -o $(OUT_DIR)/$@

