TRIPLE = wasm32-unknown-unknown
TARGET = loop
RUST_WASM_DIR = ../../wasm/rust/
# Not currently 
LLVM_CONFIG = /Users/rue1pi/Code/llvm-build/bin/llvm-config
RUSTC = /Users/rue1pi/Code/rust/build/aarch64-apple-darwin/stage1/bin/rustc
RUSTFLAGS="-C link-arg=-fuse-ld=lld"

all: dir.wasm
	#export CARGO_TARGET_WASM32_UNKNOWN_UNKNOWN_LINKER=wasm-ld
	export LLVM_CONFIG=$(LLVM_CONFIG)
	export RUSTFLAGS=$(RUSTFLAGS)
	export RUSTC=$(RUSTC)
	#export RUSTFLAGS="-C link-args=-Wl,-zstack-size=8192"
	RUSTFLAGS="-C linker=ld64.lld" cargo build --target $(TRIPLE) --release --verbose
	cp target/$(TRIPLE)/release/$(TARGET).wasm $(RUST_WASM_DIR)

dir.wasm:
	mkdir -p $(RUST_WASM_DIR)

.PHONY: clean
clean:
	cargo clean
