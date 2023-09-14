INC_DIR := $(WALI_LIB_DIR)/inc
LIB_DIR := $(WALI_LIB_DIR)/lib

DIRECTORIES := $(wildcard */)

LIBS := $(DIRECTORIES:/=)
CLEAN_LIBS := $(addsuffix -clean, $(LIBS))

.PHONY: all clean default dir $(LIBS) $(CLEAN_LIBS)

default: all

dir:
	mkdir -p $(INC_DIR)
	mkdir -p $(LIB_DIR)


liblfds711:
	make -C $@/build/gcc_gnumake
	cp -r $@/inc/* $(INC_DIR)/
	cp $@/bin/liblfds711.a $(LIB_DIR)/
liblfds711-clean:
	make -C liblfds711/build/gcc_gnumake clean


all: dir $(LIBS)
	@echo "Libs: $(LIBS)"
	
clean: $(CLEAN_LIBS)
	@echo "CleanLibs: $(CLEAN_LIBS)"
