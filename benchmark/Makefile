MAIN=$(shell basename $(CURDIR))

WAMR_DIR=../../wasm-micro-runtime
WAMR_SYMBOLS=wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt

CC=/opt/wasi-sdk/bin/clang
CFLAGS=-O0 -z stack-size=4096 -Wl,--initial-memory=65536 \
	-Wl,--allow-undefined-file=${WAMR_DIR}/${WAMR_SYMBOLS} \
	-Wl,--no-threads,--strip-all,--no-entry \
	-Wl,--export=main \
	-Wl,--export=_start \
	-Wl,--allow-undefined

SRCS=$(shell find -name '*.c' | grep -v -e $(MAIN).c)

OBJS=$(SRCS:.c=.o)

all: $(MAIN).wasm
	cp $(MAIN).wasm ../wasm-out/$(MAIN).wasm

$(MAIN).wasm: $(MAIN).c $(OBJS)
	$(info $(MAIN).c)
	$(CC) $(CFLAGS) -o $@ $(MAIN).c $(OBJS)

%.wasm : %.c
	$(CC) $< -o $@ $(CFLAGS) $(LIBS)

%.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(LIBS)

clean:
	rm *.wasm *.o polybench/*.o

build:
	mkdir $@
