# Output
ROOT_DIR=../../..
OUT_DIR=$(ROOT_DIR)/wasm/mibench
DATA_DIR=$(ROOT_DIR)/data/mibench/telecomm

# WAMR Setup
WAMR_DIR=$(ROOT_DIR)/wasm-micro-runtime
WAMR_SYMBOLS=$(WAMR_DIR)/wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt

WASMCC=/opt/wasi-sdk/bin/clang

WASMCFLAGS= -O0 -z
WASMCFLAGS+= -Wl,-allow-undefined-file=$(WAMR_SYMBOLS)
WASMCFLAGS+= -Wl,--no-threads,--strip-all,--no-entry
WASMCFLAGS+= -Wl,--export=main
WASMCFLAGS+= -Wl,--export=_start
WASMCFLAGS+= -Wl,--allow-undefined

COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

COMPILE= $(WASMCC) $(WASMCFLAGS) $(COMMON)

.PHONY: all clean toast

SRC=src

GSM_SOURCES =	$(SRC)/add.c		\
		$(SRC)/code.c		\
		$(SRC)/debug.c		\
		$(SRC)/decode.c		\
		$(SRC)/long_term.c	\
		$(SRC)/lpc.c		\
		$(SRC)/preprocess.c	\
		$(SRC)/rpe.c		\
		$(SRC)/gsm_destroy.c	\
		$(SRC)/gsm_decode.c	\
		$(SRC)/gsm_encode.c	\
		$(SRC)/gsm_explode.c	\
		$(SRC)/gsm_implode.c	\
		$(SRC)/gsm_create.c	\
		$(SRC)/gsm_print.c	\
		$(SRC)/gsm_option.c	\
		$(SRC)/short_term.c	\
		$(SRC)/table.c

TOAST_SOURCES = $(SRC)/toast.c 		\
		$(SRC)/toast_lin.c	\
		$(SRC)/toast_ulaw.c	\
		$(SRC)/toast_alaw.c	\
		$(SRC)/toast_audio.c


all: toast

EXTRAS= -Wno-comment -D_WASI_EMULATED_SIGNAL -lwasi-emulated-signal

TOAST=$(COMPILE) $(EXTRAS) $(GSM_SOURCES) $(TOAST_SOURCES)

toast:
	$(TOAST) -o $(OUT_DIR)/toast_sm.wasm -D ENCODE
	$(TOAST) -o $(OUT_DIR)/toast_l.wasm -D ENCODE -D LARGE
	$(TOAST) -o $(OUT_DIR)/untoast_s.wasm
	$(TOAST) -o $(OUT_DIR)/untoast_l.wasm -D LARGE
	cp data/small.au $(DATA_DIR)/small.au
	cp data/large.au $(DATA_DIR)/large.au
	cp data/small.au.run.gsm $(DATA_DIR)/small.au.run.gsm
	cp data/large.au.run.gsm $(DATA_DIR)/large.au.run.gsm
