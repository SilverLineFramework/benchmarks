WASM_DIR=$(ROOT_WASM_DIR)/sqlite.wasm
DATA_DIR=$(ROOT_DATA_DIR)/sqlite

.PHONY: all clean
all: $(DATA_DIR)/like.db
	cp like.query.py $(DATA_DIR)

$(DATA_DIR)/like.db:
	python like.db.py $(DATA_DIR)

clean:
	rm -r $(DATA_DIR)
