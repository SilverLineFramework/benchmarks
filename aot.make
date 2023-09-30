.PHONY: aot dir

WASMDIR := wasm-wali
AOTDIR := aot

WALIC := ../runtimes/wasm-micro-runtime-wali/wamr-compiler/build/wamrc

ARCHS := x86_64 aarch64 riscv64

INFILES := $(shell find $(WASMDIR) -type f -name '*.wasm')
OUTFILES_INT := $(foreach arch,$(ARCHS),$(patsubst $(WASMDIR)/%,$(AOTDIR)/$(arch)/%, $(INFILES)))
OUTFILES := $(OUTFILES_INT:.wasm=.aot)

aot: $(OUTFILES)

define ARCH_template =
.ONESHELL:
$(AOTDIR)/$(1)/%.aot: $(WASMDIR)/%.wasm
	mkdir -p `dirname $$@`
	$(WALIC) --enable-multi-thread --target=$(1) --disable-simd -o $$@ $$<
endef

$(foreach arch,$(ARCHS),$(eval $(call ARCH_template,$(arch))))

clean:
	rm -rf $(AOTDIR)
