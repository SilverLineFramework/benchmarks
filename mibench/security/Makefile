DATA_DIR=../../data/mibench/security

.PHONY: dir all children

all: dir children

children:
	make -C sha
	make -C rijndael
	make -C blowfish

dir:
	mkdir -p $(DATA_DIR)
