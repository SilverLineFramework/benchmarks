# Benchmarks

The following benchmark suites are included, some of which required modifications to work with WASM/WASI:
- `polybench`: [Polybench](https://web.cse.ohio-state.edu/~pouchet.2/software/polybench/); 90 benchmarks (30 benchmarks x 3 sizes)
- `mibench`: [Mibench](https://vhosts.eecs.umich.edu/mibench/); 35 benchmarks (18 benchmarks having small and large sizes except one)
- `cortex`: [UCSD CortexSuite](https://cseweb.ucsd.edu//groups/bsg/), excluding the San Diego Vision Benchmark suite; 24 benchmarks (8 benchmarks x 3 sizes)
- `vision`: [San Diego Vision Benchmark Suite](https://michaeltaylor.org/vision/); 27 benchmarks (9 benchmarks x 3 sizes)
- `libsodium`: [Libsodium Benchmarks](https://github.com/jedisct1/libsodium), available pre-compiled [here](https://github.com/jedisct1/webassembly-benchmarks); 70 benchmarks (15 [benchmark types](https://00f.net/2023/01/04/webassembly-benchmark-2023/), various configurations per type)
- `apps`: benchmarks made from common real-world applications:
    - `python`: the [CPython](https://github.com/python/cpython) interpreter [compiled to WASM](https://github.com/singlestore-labs/python-wasi) running 12 python scripts taken from the [Codon benchmark suite](https://github.com/exaloop/codon/tree/develop/bench). Note that WASM/WASI-compiled python currently does not support pip-installed modules; complicated imports are also somewhat flaky.
    - `ffmpeg`: [FFmpeg](https://www.ffmpeg.org/) standalone executable [compiled to WASM](https://github.com/SebastiaanYN/FFmpeg-WASI), supporting `zlib` and `x264` with 6 different operations.
    - `lua`: [Lua](https://www.lua.org/) interpreter, running 5 different scripts; requires [WALI](https://github.com/arjunr2/WALI) instead of only WASI to run.
    - `sqlite3`: [SQLite](https://www.sqlite.org/index.html) running 5 different queries; requires [WALI](https://github.com/arjunr2/WALI).

We also include a number of "data-dependent" benchmarks. These benchmarks include a variety of input data, and have behavior that can vary greatly depending on the inputs given.
- `python`: [CPython](https://github.com/python/cpython) interpreter [compiled to WASM](https://github.com/singlestore-labs/python-wasi) running 20 different python scripts; each script takes a random seed, and generates random data depending on randomly sampled parameters. We also include scripts from the python test suite as a small representative sample.
- `kissat`: [Kissat](https://github.com/arminbiere/kissat) SAT solver, [compiled to WASM](https://github.com/thetianshuhuang/kissat-wasm) with a minor modification (changing the allocation size of a buffer on the stack). Benchmarks taken from [SATLib](https://www.cs.ubc.ca/~hoos/SATLIB/benchm.html) are used as inputs.
- `sqlite`: [SQLite](https://www.sqlite.org/index.html) database [compiled to WASM](https://wasmer.io/sqlite/sqlite) running randomly generated queries on randomly generated databases; we include example queries for the [northwind](https://musiliadebayo.medium.com/50-sql-practice-queries-and-answers-3fc896650b2e) and [chinook](https://github.com/LucasMcL/15-sql_queries_02-chinook/blob/master/chinook-queries.sql) standard test databases as a small representative sample.

## Setup

1. Install the [WASI SDK](https://github.com/webassembly/wasi-sdk/):
    ```sh
    wget https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-20/wasi-sdk-20.0-linux.tar.gz
    tar xvf wasi-sdk-20.0-linux.tar.gz
    sudo cp -r wasi-sdk-20.0 /opt/wasi-sdk
    ```

2. Build benchmarks:
    - `make`: build all benchmarks; saved to `./wasm`. Any necessary data files are saved to `./data`. Since paths are hard-coded into benchmarks, benchmarks must be executed with `./benchmarks` as a WASI pre-opened directory (or equivalently, `wasm` and `data` in WASI working directory).
    - `MODE=native make`: build all benchmarks natively using gcc for comparison; saved to `./native`.
    - `make {benchmark}`: make benchmark suites individually.
    - `make clean`: remove `./wasm` and `./data`.
