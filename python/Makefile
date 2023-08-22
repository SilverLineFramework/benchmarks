WASM_DIR=$(ROOT_WASM_DIR)/python
DATA_DIR=$(ROOT_DATA_DIR)/python


.PHONY: all clean
all:
	mkdir -p $(DATA_DIR)
	cp -r python-tests $(DATA_DIR)/tests
	cp -r parametric $(DATA_DIR)/parametric

clean:
	rm -r $(WASM_DIR)
	rm -r $(DATA_DIR)


python-tests:

tests.json: results
	python filter2.py

results:
	python filter.py
	rm -r tempcwd
	rm tmp.py