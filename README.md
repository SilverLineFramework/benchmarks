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

3. Acquire an MQTT token and save it in a file ```./mqtt_pwd.txt```.

    **NOTE**: if the MQTT server is unsecured (i.e. a default local install of mosquitto), you can just ```touch mqtt_pwd.txt```.

4. Build benchmarks:

    - ```make wasm```: build wasm programs; saved to ```./wasm```.
    - ```make rustpython```: copy rustpython to ```./wasm``` for distribution or AOT compilation.
    - ```make aot```: build wasm apps into AOT; saved in ```./aot```. **NOTE**: this can take a very long time, especially if rustpython is included.
    - ```make clean```: remove ```./wasm``` and ```./aot```.

5. Clone the [Python Client](https://github.com/SilverLineFramework/libsilverline), which includes scripts for launching benchmarks.

## Usage

1. Start the runtime using a known name. For example, if ```runtime-linux``` is set up in the same directory as ```benchmarks``` with a local orchestrator and MQTT server, you can use the following command:
    ```sh
    ./runtime-linux/runtime --host=localhost:1883 --name=test --dir=benchmarks --appdir=benchmarks
    ``` 

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

- ```tests```: Tests for basic functionality. Currently unmaintained.
- ```polybench```: [Polybench](https://web.cse.ohio-state.edu/~pouchet.2/software/polybench/) wrapped in distributed runtime interfaces; simulates output data using a dirichlet process ```alpha=1``` with ```geometric(0.001)``` prior.
- ```cortex```: Miscellaneous machine learning benchmarks manually ported from [UCSD Cortex Suite](https://cseweb.ucsd.edu/groups/bsg/).

## Additional Scripts

- ```status.py```: print status table for runtime nodes specified in a TSV file.
- ```list_devices.py```: print a list of runtimes specified in a TSV file (for passing to other commands, i.e. inside makefiles).
- ```stop_runtimes.py```: send DELETE_RUNTIME messages to request runtimes to exit.
