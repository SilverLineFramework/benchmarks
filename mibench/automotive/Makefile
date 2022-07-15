DATA_DIR=../../data/mibench/automotive

.PHONY: dir all children

all: dir children

children:
	make -C basicmath
	make -C bitcount
	make -C qsort

dir:
	mkdir -p $(DATA_DIR)
