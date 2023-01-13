# Compiling Rust Programs to Silverline Modules
Brief instruction on how to compile Rust code into WebAssembly modules which can be deployed and managed by the runtimes of Silverline.

-----

## Prerequisites

### The Rust Stack
Visit the [Rust Homepage](https://www.rust-lang.org/tools/install) to install Rust and its toolchain `rustup`.

### WASI-enabled Rust toolchain
Use `rustup` to install the toolchain capable of compiling Rust to WASM:
```
rustup target add wasm32-wasi
```

----

## Implementing Silverline Modules in Rust
The modules can be implemented completely in Rust. In order to implement the interaction between the module and the Silverline runtime (e.g. for publishing to a topic using the channel interface), please use the functions provided in `src/lib.rs` (the safely wrap the C Api offered by the Silverline runtime).

The `src/bin/` directory contains exemplary implementations of modules:

- `rust_counter` - A module printing out an increasing counter via stdout
- `rust_publish` - A module publishing a message to a topic
- `rust_subscribe` - A module subscribing to a topic, reading messages from it and printing them out to stdout

(if deployed at the same time, `rust_publish` and `rust_subscribe` should talk to each other, since they are using the same topic)

You can implement additional modules by creating a Rust file in the `src/bin/` directory and compiling them to WASM as described below.

----

## Compiling Rust to Wasm Modules

The modules in the `src/bin/` directory can be compiled to WASM using the command:

```
cargo build --target wasm32-wasi
```

The generated `.wasm` files are then placed in the directory `/target/wasm32-wasi/debug`.

Alternatively, the modules can be compiled with enabled compiler optimizations via:

```
cargo build --target --release wasm32-wasi
```

In this case, the generated `.wasm` files are placed in `/target/wasm32-wasi/release`.

The generated `.wasm` files can then be used to be deployed as modules and managed by Silverline.
