# Benchmarks

The following benchmark suites are included, some of which required modifications to work with WASM/WASI:
- ```polybench```: [Polybench](https://web.cse.ohio-state.edu/~pouchet.2/software/polybench/); 90 benchmarks (30 benchmarks x 3 sizes)
- ```mibench```: [Mibench](https://vhosts.eecs.umich.edu/mibench/); 35 benchmarks (18 benchmarks having small and large sizes except one)
- ```cortex```: [UCSD CortexSuite](https://cseweb.ucsd.edu//groups/bsg/), excluding the San Diego Vision Benchmark suite; 24 benchmarks (8 benchmarks x 3 sizes)
- ```vision```: [San Diego Vision Benchmark Suite](https://michaeltaylor.org/vision/); 27 benchmarks (9 benchmarks x 3 sizes)
- ```libsodium```: [Libsodium Benchmarks](https://github.com/jedisct1/libsodium), available pre-compiled [here](https://github.com/jedisct1/webassembly-benchmarks); 70 benchmarks (15 [benchmark types](https://00f.net/2023/01/04/webassembly-benchmark-2023/), various configurations per type)
- ```apps```: 26 benchmarks made from common real-world applications:
    - ```python```: the [CPython](https://github.com/python/cpython) interpreter [compiled to WASM](https://github.com/singlestore-labs/python-wasi) running 12 python scripts taken from the [Codon benchmark suite](https://github.com/exaloop/codon/tree/develop/bench). Note that WASM/WASI-compiled python currently does not support pip-installed modules; complicated imports are also somewhat flaky.
    - ```ffmpeg```: [FFmpeg](https://www.ffmpeg.org/) standalone executable [compiled to WASM](https://github.com/SebastiaanYN/FFmpeg-WASI), supporting `zlib` and `x264` with 6 different operations.
    - ```wasm3```: [wasm3](https://github.com/wasm3/wasm3) running two different wasm modules, as well as running a small module inside itself (running wasm3 inside wasm3 inside a wasm runtime). Currently only working on wasmer, and only up to 3 runtimes deep.
    - ```lua```: [Lua](https://www.lua.org/) interpreter, running 5 different scripts; requires [WALI](https://github.com/arjunr2/WALI) instead of only WASI to run.
    - ```sqlite3```: [SQLite](https://www.sqlite.org/index.html) running 5 different queries; requires [WALI](https://github.com/arjunr2/WALI).

In total, we currently have 272 benchmarks.

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
    - `make {benchmark}`: make benchmark suites individually.
    - `make clean`: remove `./wasm` and `./data`.
