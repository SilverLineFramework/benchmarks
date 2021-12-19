# Benchmarks & Tests

## Setup

1. Clone this repository at the same level as ```arena-runtime-linux```:

```
arena
    arena-runtime-linux
    runtime-benchmarks
```

2. Make sure you have Python 3 and Paho (```pip install paho-mqtt```) installed.

3. Build WASM apps with ```./build.sh```.

## Usage

1. Run the ```run-py``` or ```run-wasm``` script.
    - Use ```--kwargs``` to include additional arguments for the runtime:
    ```shell
    python run-wasm.py [...] --kwargs --verbose.wamr=0 --verbose=4 --username=runtime
    ```
    - Specify ```--path``` for ```run-wasm``` or ```--script```, ```--scene```, and ```--namespace``` for ```run-wasm```.
    - This should create a file ```runtime.sh```.

2. Run the generated ```runtime.sh``` script.
    - Run with ```./runtime.sh``` in a different terminal (this way you can observe manager and runtime outputs).
    - You will need to ```chmod +x runtime.sh``` the first time it is generated (or after you delete ```runtime.sh``` and regenerate)

3. Return to the manager terminal and press enter.
    - If ```--num``` is specified ```>1```, press enter multiple times to spawn ```num``` modules.
