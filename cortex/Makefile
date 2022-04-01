# Output
OUT_DIR=../wasm/cortex

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


.PHONY: all clean dir
all: dir kmeans spectral svd pca

clean:
	rm -r $(OUT_DIR)

dir:
	mkdir -p $(OUT_DIR)


.PHONY: kmeans spectral svd pca

KMEANS_SRCS= clustering/kmeans.c clustering/kmeans_main.c
kmeans:
	$(COMPILE) $(KMEANS_SRCS) -o $(OUT_DIR)/kmeans.wasm

SPECTRAL_SRCS= clustering/eigen.c clustering/kmeans.c clustering/spectral.c
spectral:
	$(COMPILE) $(SPECTRAL_SRCS) -o $(OUT_DIR)/spectral.wasm

SVD_SRCS= $(shell find svd -name '*.c')
svd:
	$(COMPILE) $(SVD_SRCS) -o $(OUT_DIR)/svd.wasm

PCA_SRCS= pca/pca.c
pca:
	$(COMPILE) $(PCA_SRCS) -o $(OUT_DIR)/pca.wasm
