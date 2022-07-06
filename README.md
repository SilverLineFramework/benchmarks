# Benchmarks & Tests

## Setup

0. Set up infrastructure if required.

    - Mosquitto server: ```sudo apt-get install mosquitto```. Start with ```mosquitto``` if not already running.
    - Run the [orchestrator](https://github.com/SilverLineFramework/orchestrator). All settings can be default, and config files can be empty.
    - The instructions here assume that the [linux runtime](https://github.com/SilverLineFramework/runtime-linux) is installed in the same directory as this repository:
        ```
        silverline/
            ...
            mqtt_pwd.txt
            benchmarks/
                ...
            runtime-linux/ 
                ...
        ```

1. Install dependencies:
    ```sh
    pip install -r requirements.txt
    ```

2. Compile the WAMR compiler:
    ```sh
    git submodule update --init --recursive
    cd wasm-micro-runtime/wamr-compiler
    ./build_llvm.sh
    mkdir build && cd build
    cmake ..
    make
    ```

3. Install the WASI SDK:
    ```shell
    wget https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-11/wasi-sdk-11.0-linux.tar.gz
    tar xvf wasi-sdk-11.0-linux.tar.gz
    sudo cp -r wasi-sdk-11.0 /opt/wasi-sdk
    ```

4. Acquire an MQTT token and save it in a file ```./mqtt_pwd.txt```.

    **NOTE**: if the MQTT server is unsecured (i.e. a default local install of mosquitto), you can just ```touch mqtt_pwd.txt```.

5. Build benchmarks:

    - ```make wasm```: build wasm programs; saved to ```./wasm```.
    - ```make rustpython```: copy rustpython to ```./wasm``` for distribution or AOT compilation.
    - ```make aot```: build wasm apps into AOT; saved in ```./aot```. **NOTE**: this can take a very long time, especially if rustpython is included.
    - ```make clean```: remove ```./wasm``` and ```./aot```.

6. Clone the [Python Client](https://github.com/SilverLineFramework/libsilverline), which includes scripts for launching benchmarks.

## Usage

1. Start the runtime using a known name. For example, if ```runtime-linux``` is set up in the same directory as ```benchmarks``` with a local orchestrator and MQTT server, you can use the following command:
    ```sh
    ../runtime-linux/runtime --host=localhost:1883 --name=test --dir=. --appdir=.
    ```

    **NOTE**: due to runtime WASI issues, you may need to start inside the benchmarks directory like this example in order for some benchmarks to properly open files.

2. Run the ```run.py``` script (from the [Python Client](https://github.com/SilverLineFramework/libsilverline)), for example:
    ```sh
    python libsilverline/run.py --path wasm/tests/helloworld.wasm --runtime test
    ```

## Available Options

```
usage: run.py [-h] [--arts ARTS] [--arts_port ARTS_PORT] [--mqtt MQTT]
              [--mqtt_port MQTT_PORT] [--username USERNAME] [--pwd PWD] [--ssl]
              [--type TYPE] [--path PATH [PATH ...]] [--argv ARGV [ARGV ...]]
              [--runtime RUNTIME [RUNTIME ...]] [--env ENV [ENV ...]] [--aot]
              [--mode MODE] [--time TIME] [--mean_size MEAN_SIZE] [--alpha ALPHA]
              [--n N] [--delay DELAY] [--config CONFIG]

optional arguments:
  -h, --help            show this help message and exit
  --config CONFIG       Config file to load; priority is (1) explicitly passed
                        args, (2) config file, (3) defaults

ARTS Options:
  --arts ARTS           ARTS host
  --arts_port ARTS_PORT
                        ARTS port

MQTT Options:
  --mqtt MQTT           MQTT Host address
  --mqtt_port MQTT_PORT
                        MQTT port
  --username USERNAME   Username
  --pwd PWD             Password file
  --ssl                 Use SSL (mqtt-secure)

Benchmark Options:
  --type TYPE           PY or WA
  --path PATH [PATH ...]
                        File path(s) to execute
  --argv ARGV [ARGV ...]
                        Module argv passthrough
  --runtime RUNTIME [RUNTIME ...]
                        Target runtime names
  --env ENV [ENV ...]   Module environment variables
  --aot                 Use AOT python for python benchmarks
  --mode MODE           Profiling mode (passive, active, timed)
  --time TIME           Total time limit (seconds) for timed profiling mode
  --mean_size MEAN_SIZE
                        Prior mean message size (used as input to dirichlet
                        process)
  --alpha ALPHA         Dirichlet Process "new table" parameter alpha
  --n N                 Number of iterations to test for active profiling mode
  --delay DELAY         Delay between iterations for active/timed profiling mode
```

Additional notes:
- ```runtime``` should correspond to the name of the runtime, not the UUID. This can also be a comma-separated list of names; in that case, the module specified will be created on all runtimes listed. **NOTE**: runtimes should have distinct names.
- The behavior when multiple modules (```path```) are specified depends on the profiling mode.
    - ```passive```: the script will instantiate the module, then exit. The module is responsible for exiting.
    - ```active```: the script will wait for ```--n``` rounds of active profiling to complete before sending the exit signal (```"exit"```) and moving on to the next.
    - ```timed```: the script will trigger new rounds of profiling until the time limit ```--time``` is reached, after which it will send the exit signal.
- Active and timed profiling uses a dirichlet process with parameter ```alpha``` and prior ```geometric(1 / mean_size)``` for input message sizes.

## Benchmarks

The following benchmark suites have been modified to work with the linux runtime:
- ```polybench```: [Polybench](https://web.cse.ohio-state.edu/~pouchet.2/software/polybench/)
- ```mibench```: [Mibench](https://vhosts.eecs.umich.edu/mibench/)

## Additional Scripts

- ```status.py```: print status table for runtime nodes specified in a TSV file.
- ```list_devices.py```: print a list of runtimes specified in a TSV file (for passing to other commands, i.e. inside makefiles).
- ```stop_runtimes.py```: send DELETE_RUNTIME messages to request runtimes to exit.

## Conversion Guide

1. Modify makefile. See this example header:
    ```Makefile
    # Output
    ROOT_DIR=../../..
    OUT_DIR=$(ROOT_DIR)/wasm/mibench/network
    DATA_DIR=$(ROOT_DIR)/data/mibench/network

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
    ```

    In the makefile, the WASM output should be ```wasm/path/to/benchmark.wasm```,
    and any accompanying data files should be copied to ```data/path/to/benchmark.dat```.

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
