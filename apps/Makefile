WASM_DIR=$(ROOT_WASM_DIR)/apps
DATA_DIR=$(ROOT_DATA_DIR)/apps

.PHONY: all clean

all:
	mkdir -p $(DATA_DIR)
	cp -r python $(DATA_DIR)
	cp -r ffmpeg $(DATA_DIR)

clean:
	rm -r $(WASM_DIR)
	rm -r $(DATA_DIR)
