DATA_DIR=../../data/mibench/telecomm

.PHONY: dir all children

all: dir children

children:
	make -C adpcm
	make -C CRC32
	make -C FFT
	make -C gsm

dir:
	mkdir -p $(DATA_DIR)
