WASM_DIR=$(ROOT_WASM_DIR)/sqlite.wasm
DATA_DIR=$(ROOT_DATA_DIR)/sqlite
SQLITE=https://registry-cdn.wapm.io/contents/sqlite/sqlite/0.2.2/build/sqlite.wasm


DATABASES = $(DATA_DIR)/like.db $(DATA_DIR)/join.db $(DATA_DIR)/small.db \
	$(DATA_DIR)/sort.db

.PHONY: all clean dir
all: dir $(DATABASES) $(WASM_DIR)/sqlite.wasm
	cp chinook.db $(DATA_DIR)/chinook.db
	cp northwind.db $(DATA_DIR)/northwind.db
	cp -r *.query.py $(DATA_DIR)

dir:
	mkdir -p $(DATA_DIR)

clean:
	rm -r $(DATA_DIR)
	rm -r sqlite-amalgamation*

$(DATA_DIR)/like.db:
	python like.db.py $(DATA_DIR)/like.db

$(DATA_DIR)/join.db:
	python join.db.py $(DATA_DIR)/join.db

$(DATA_DIR)/small.db:
	python small.db.py $(DATA_DIR)/small.db

$(DATA_DIR)/sort.db:
	python sort.db.py $(DATA_DIR)/sort.db

$(WASM_DIR)/sqlite.wasm:
	wget $(SQLITE) -O $(WASM_DIR)
