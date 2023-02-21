# Output
COMPILE= $(WASMCC) $(WASMCLFLAGS)

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

TOAST_SOURCES = $(SRC)/toast_lin.c	\
		$(SRC)/toast_ulaw.c	\
		$(SRC)/toast_alaw.c	\
		$(SRC)/toast_audio.c

MAIN_C = $(SRC)/toast.c
SUPP_C := $(GSM_SOURCES) $(TOAST_SOURCES)

SUPP := $(SUPP_C:.c=.wasm)
SUPP_WASM := $(addprefix $(COMMON_DIR)/, $(notdir $(SUPP)))

WASMCFLAGS+= -Wno-comment -D_WASI_EMULATED_SIGNAL 
WASMLDFLAGS+= -lwasi-emulated-signal

all: toast

$(SUPP) : %.wasm : %.c
	$(WASMCC) $(WASMCFLAGS) -c $^ -o $(COMMON_DIR)/$(notdir $@)

toast: $(SUPP)
	$(eval INT_FILE = $(shell mktemp))

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -D ENCODE -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_s.wasm

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -D ENCODE -D LARGE -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/$@_l.wasm

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/un$@_s.wasm

	$(WASMCC) $(WASMCFLAGS) $(MAIN_C) -D LARGE -c -o $(INT_FILE)
	$(WASMLD) $(WASMLDFLAGS) $(SUPP_WASM) \
		$(INT_FILE) -o $(WASM_DIR)/un$@_l.wasm

	rm $(INT_FILE)

	cp data/small.au $(DATA_DIR)/gsm_small.au
	cp data/large.au $(DATA_DIR)/gsm_large.au
	cp data/small.au.run.gsm $(DATA_DIR)/gsm_small.gsm
	cp data/large.au.run.gsm $(DATA_DIR)/gsm_large.gsm
