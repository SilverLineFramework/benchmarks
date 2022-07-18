# Benchmarks & Tests

## Benchmarks

The following benchmark suites have been modified to work with the linux runtime:
- ```polybench```: [Polybench](https://web.cse.ohio-state.edu/~pouchet.2/software/polybench/); 60 benchmarks (30 benchmarks x 2 sizes)
- ```mibench```: [Mibench](https://vhosts.eecs.umich.edu/mibench/); 30 benchmarks (16 benchmarks, with 14 having small and large sizes)
- ```cortex```: [UCSD CortexSuite](https://cseweb.ucsd.edu//groups/bsg/), excluding the San Diego Vision Benchmark suite; 24 benchmarks (8 benchmarks x 3 sizes)
- ```vision```: [San Diego Vision Benchmark Suite](https://michaeltaylor.org/vision/); 27 benchmarks (9 benchmarks x 3 sizes)

In total, we currently have 141 benchmarks, 63 of which are unique (differ by more than just data / parameters).

## Setup

0. Set up infrastructure if not already installed.

    - Mosquitto server: ```sudo apt-get install mosquitto```. Start with ```mosquitto``` if not already running.
    - Run the [orchestrator](https://github.com/SilverLineFramework/orchestrator). All settings can be default, and config files can be empty.
    - Install the Python Client, [libsilverline](https://github.com/SilverLineFramework/libsilverline).
    - The instructions here assume that the [linux runtime](https://github.com/SilverLineFramework/runtime-linux) is installed in the same directory as this repository:
        ```
        silverline/
            ...
            mqtt_pwd.txt
            libsilverline/
                ...
            benchmarks/
                ...
            runtime-linux/ 
                ...
        ```

1. Install the WASI SDK:
    ```shell
    wget https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-11/wasi-sdk-11.0-linux.tar.gz
    tar xvf wasi-sdk-11.0-linux.tar.gz
    sudo cp -r wasi-sdk-11.0 /opt/wasi-sdk
    ```

2. In ```benchmarks/```, compile the WAMR compiler:
    ```sh
    git submodule update --init --recursive
    cd wasm-micro-runtime/wamr-compiler
    ./build_llvm.sh
    mkdir build && cd build
    cmake ..
    make
    ```

3. Acquire an MQTT token and save it in a file ```./mqtt_pwd.txt```.

    **NOTE**: if the MQTT server is unsecured (i.e. a default local install of mosquitto), you can just ```touch mqtt_pwd.txt```.

4. Build benchmarks:

    - ```make wasm```: build wasm programs; saved to ```./wasm```.
    - ```make {benchmark}```: make ```tests```, ```polybench```, ```mibench```, ```vision```, or ```cortex``` individually.
    - ```make rustpython```: copy rustpython to ```./wasm``` for distribution or AOT compilation.
    - ```make clean```: remove ```./wasm``` and ```./aot```.
    - ```make aot```: build wasm apps into AOT. This will compile **all** ```*.wasm``` files in the ```./wasm``` directory to corresponding ```*.aot``` files in the ```./aot``` directory.
    
        **NOTE**: this can take a very long time, especially if rustpython is included. Always ```make aot -j16``` (with the appropriate number of threads).

## Usage

1. Start the runtime using a known name. For example, if ```runtime-linux``` is set up in the same directory as ```benchmarks``` with a local orchestrator and MQTT server, you can use the following command:
    ```sh
    ../runtime-linux/runtime --host=localhost:1883 --name=test --dir=. --appdir=.
    ```

    **NOTE**: due to runtime WASI issues, you may need to start inside the benchmarks directory like this example in order for some benchmarks to properly open files.

2. Run the ```run.py``` script (from the [Python Client](https://github.com/SilverLineFramework/libsilverline)):
    ```sh
    python libsilverline/run.py --path wasm/tests/helloworld.wasm --runtime test
    ```

    The ```run.py``` script supports several benchmarking modes. ```---type passive``` will likely be most helpful; for example:
    ```sh
    python libsilverline/run.py --path aot/polybench/2mm.aot --runtime test --type passive --duration 10
    ```
    will create a module for the AOT-compiled benchmark ```aot/polybench/2mm.aot``` on the runtime named ```test```, wait for 10 seconds, then instruct it to exit.

## Conversion Guide

1. Modify makefile. For example:
    ```Makefile
    # Output
    BENCHMARK_NAME=network
    ROOT_DIR=../../..
    OUT_DIR=$(ROOT_DIR)/wasm/mibench/$(BENCHMARK_NAME)
    DATA_DIR=$(ROOT_DIR)/data/mibench/$(BENCHMARK_NAME)

    # WAMR Setup
    WAMR_DIR=$(ROOT_DIR)/wasm-micro-runtime
    WAMR_SYMBOLS=$(WAMR_DIR)/wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt

    WASMCC=/opt/wasi-sdk/bin/clang

    WASMCFLAGS= -O0 -z
    WASMCFLAGS+= -Wl,-allow-undefined-file=$(WAMR_SYMBOLS)
    WASMCFLAGS+= -Wl,--no-threads,--strip-all,--no-entry
    WASMCFLAGS+= -Wl,--export=main
    WASMCFLAGS+= -Wl,--export=_start
    WASMCFLAGS+= -Wl,--allow-undefined

    COMMON= $(ROOT_DIR)/common/passive.c -D PROFILE_PASSIVE

    COMPILE= $(WASMCC) $(WASMCFLAGS) $(COMMON)

    .phony: all

    SRCS= src/*.c ../common/*.c

    all:
        $(COMPILE) $(SRCS) -o $(OUT_DIR).wasm
        cp data.dat $(DATA_DIR)/data.dat
    ```

    In the makefile, the WASM output should be ```wasm/path/to/benchmark.wasm```,
    and any accompanying data files should be copied to ```data/path/to/benchmark.dat```. No specific data file naming/directory scheme is required, as long as it does not conflict with other benchmarks.

2. Rename main function to ```benchmark_main```.

3. In the main file, include the following:

    ```c
    #include "../../../common/runtime.h"
    ```
    where the appropriate relative path is given.

3. Add the new main function:

    ```c
    int main(int argc, char **argv) {
        return loop(argc, argv, &benchmark_main);
    }
    ```

4. Run on the runtime and observe the number of loops (should be printed out by the common driver at exit). Generally, you should get at least 10 loops in a 10s interval, and at most 2000.
