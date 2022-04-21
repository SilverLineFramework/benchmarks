XCLANG_OPTS = -disable-O0-optnone 
CLANG_OPTS = -O0 -emit-llvm #-fno-discard-value-names -O0 -emit-llvm
OPT_OPTS = -mem2reg -loop-simplify

ifeq ($(shell uname -m), x86_64)
CXXFLAGS = -rdynamic $(shell llvm-config --cxxflags) -g -fPIC -O0
else
CXXFLAGS = -rdynamic $(shell llvm-config --cxxflags) -g -O0
endif

SRC_C := $(wildcard *.c)
SRC_INT_LL := $(SRC_C:.c=.int.ll)
SRC_LL := $(SRC_C:.c=.ll)



all: malloc-checkpoint.so checkpoint.so null.so dyn_inst_cnt.so $(SRC_LL)

available-support.o: available-support.cpp available-support.h support.h

%.so: %.o #Dataflow.o available-support.o
	$(CXX) -dylib -shared $^ -o $@

%.ll: %.int.ll
	opt $(OPT_OPTS) $^ -S -o $@

%.int.ll: %.c
	/opt/wasi-sdk/bin/clang -Xclang $(XCLANG_OPTS) $(CLANG_OPTS) -S $^ -o $@


run:
	make

clean:
	rm -f *.o *~ *.so *.ll *.bc out *.wasm *.wat *.aot

clean-ll:
	rm *.ll

.PHONY: clean-ll clean all
