# Benchmarks

The following benchmark suites are included, some of which required modifications to work with WASM/WASI:
- ```polybench```: [Polybench](https://web.cse.ohio-state.edu/~pouchet.2/software/polybench/); 90 benchmarks (30 benchmarks x 3 sizes)
- ```mibench```: [Mibench](https://vhosts.eecs.umich.edu/mibench/); 35 benchmarks (18 benchmarks having small and large sizes except one)
- ```cortex```: [UCSD CortexSuite](https://cseweb.ucsd.edu//groups/bsg/), excluding the San Diego Vision Benchmark suite; 24 benchmarks (8 benchmarks x 3 sizes)
- ```vision```: [San Diego Vision Benchmark Suite](https://michaeltaylor.org/vision/); 27 benchmarks (9 benchmarks x 3 sizes)

In total, we currently have 176 benchmarks, 65 of which are unique (differ by more than just data / parameters).

## Setup

1. Install the [WASI SDK](https://github.com/webassembly/wasi-sdk/):
    ```sh
    wget https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-11/wasi-sdk-11.0-linux.tar.gz
    tar xvf wasi-sdk-11.0-linux.tar.gz
    sudo cp -r wasi-sdk-11.0 /opt/wasi-sdk
    ```

2. Build benchmarks:

    - `make`: build all benchmarks; saved to `./wasm`. Any necessary data files are saved to `./data`. Since paths are hard-coded into benchmarks, benchmarks must be executed with `./benchmarks` as a WASI pre-opened directory (or equivalently, `wasm` and `data` in WASI working directory).
    - `MODE=native make`: build all benchmarks natively using gcc for comparison; saved to `./native`.
    - `MODE=silverline make`: build benchmarks with silverline integration enabled for each benchmark (if supported).
    - `make {benchmark}`: make `polybench`, `mibench`, `cortex`, or `vision` individually.
    - `make clean`: remove `./wasm` and `./data`.
