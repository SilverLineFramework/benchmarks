# Benchmarks & Tests

## Setup

0. Set up infrastructure if required.

    - Mosquitto server: ```sudo apt-get install mosquitto```. Start with ```mosquitto``` if not already running.
    - Run [ARTS](https://github.com/conix-center/arts). All settings can be default, and config files can be empty.

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

    **NOTE**: if the MQTT server is unsecured, you should ```touch mqtt_pwd.txt```.

4. Build benchmarks:

    - ```make```, ```make wasm```: build wasm programs; saved in ```./wasm```.
    - ```make aot```: build wasm apps into AOT; saved in ```./aot```.
    - ```make clean```: remove ```./wasm``` and ```./aot```.

## Usage

1. Start the runtime using a known name. For example, if ```arena-runtime-linux``` is set up in the same directory as ```runtime-benchmarks``` with local ARTS and MQTT, you can use the following command:

    ```sh
    ../arena-runtime-linux/runtime --host=localhost:1883 --name=test --dir=. --appdir=.
    ``` 

2. Run the ```run.py``` script, for example:
    ```sh
    python run.py --type WA --path wasm/test/helloworld.wasm --runtime test
    ```

## Available Options

```
usage: run.py [-h] [--host HOST] [--port PORT] [--type TYPE] [--path PATH [PATH ...]] [--argv ARGV [ARGV ...]] [--runtime RUNTIME [RUNTIME ...]] [--scene SCENE] [--namespace NAMESPACE]
              [--aot] [--active] [--mean_size MEAN_SIZE] [--alpha ALPHA] [--n N] [--delay DELAY]

optional arguments:
  -h, --help            show this help message and exit
  --host HOST           MQTT host
  --port PORT           MQTT port
  --type TYPE           PY or WA
  --path PATH [PATH ...]
                        File path(s) to execute
  --argv ARGV [ARGV ...]
                        Module argv passthrough
  --runtime RUNTIME [RUNTIME ...]
                        Target runtimes
  --scene SCENE         Scene environment variable
  --namespace NAMESPACE
                        Namespace environment variable
  --aot                 Use AOT python
  --active              Use active profiling
  --mean_size MEAN_SIZE
                        Prior mean message size (used as input to dirichlet process)
  --alpha ALPHA         Dirichlet Process 'new table' parameter alpha.
  --n N                 Number of iterations to test
  --delay DELAY         Delay between iterations
```

Additional notes:
- ```runtime``` should correspond to the name of the runtime, not the UUID. This can also be a comma-separated list of names; in that case, the module specified will be created on all runtimes listed.
- The behavior when multiple modules (```path```) are specified depends on whether active profiling is enabled.
    - If enabled, the script will wait for all rounds of active profiling to complete before moving onto the next.
    - If disabled, the script will initialize all modules specified simulataneously.
- Active profiling uses a dirichlet process with parameter ```alpha``` and prior ```geometric(1 / mean_size)``` for input message sizes.

## Benchmarks

- ```tests```: Tests for basic functionality. Currently unmaintained.
- ```polybench```: [Polybench](https://web.cse.ohio-state.edu/~pouchet.2/software/polybench/) wrapped in distributed runtime interfaces; simulates output data using a dirichlet process ```alpha=1``` with ```geometric(0.001)``` prior.
- ```cortex```: Miscellaneous machine learning benchmarks manually ported from [UCSD Cortex Suite](https://cseweb.ucsd.edu/groups/bsg/)

## Additional Scripts

- ```status.py```: print status table for runtime nodes specified in a TSV file.
- ```list_devices.py```: print a list of runtimes specified in a TSV file (for passing to other commands, i.e. inside makefiles).
- ```stop_runtimes.py```: send DELETE_RUNTIME messages to request runtimes to exit.
