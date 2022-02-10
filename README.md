# Benchmarks & Tests

## Setup

1. This module should be a submodule in the runtime directory, and initialized as part of the runtime setup.

2. Make sure you have Python 3 and Paho (```pip install paho-mqtt```) installed.

3. Build WASM apps with ```./build.sh```

4. Acquire an MQTT token and save it in a file ```./mqtt_pwd.txt```.

## Usage

1. The ```run.py``` manager script will generate a ```runtime.sh``` script which contains the relevant arguments needed to start the runtime (with known UUID, with the correct MQTT host/port, etc). ```run.py``` will then wait for input.

2. Run the ```runtime.sh``` script (```chmod +x runtime.sh``` on the first time it is generated, or if it is deleted and regenerated). This starts the runtime with the specified options.

3. Press enter on the manager script terminal to send the ```CREATE_MODULE``` message. If ```--num``` is specified ```>1```, press enter multiple times to spawn ```num``` modules.

Depending on the ```--mode```, the following will happen:
- ```profile```: after creating the module(s), the manager script will exit. Profile data will be collected by the runtime.
- ```profile_active```: after creating the module(s), the manager script will send random ```float32``` arrays to ```ch/in/[module_uuid]``` every ```--delay``` seconds.
- ```delete```: ```--num``` modules will be created, then deleted with delay ```--delay``` seconds; this is repeated 10 times.

## Available Options

```
usage: run.py [-h] [--type TYPE] [--num NUM] [--kwargs [KWARGS ...]] [--argv ARGV] [--host HOST] [--port PORT]
              [--arts] [--no-arts] [--mode MODE] [--size SIZE] [--delay DELAY] [--script SCRIPT] [--scene SCENE]
              [--namespace NAMESPACE] [--aot] [--path PATH]

optional arguments:
  -h, --help            show this help message and exit
  --type TYPE           PY or WA
  --num NUM             Number of copies
  --kwargs [KWARGS ...]
                        Runtime passthrough args
  --argv ARGV           Module argv passthrough
  --host HOST           MQTT Host
  --port PORT           MQTT Port
  --arts                Use ARTS
  --no-arts             Skip ARTS and manually schedule
  --mode MODE           Testing mode (profile, profile_active, or delete)
  --size SIZE           Array size (bytes) for active profiling
  --delay DELAY         Processing delay (seconds)
  --script SCRIPT       Script name
  --scene SCENE         Scene environment variable
  --namespace NAMESPACE
                        Namespace environment variable
  --aot                 Use AOT python
  --path PATH           File name
```

## Benchmark

Options for the ```benchmark.wasm``` test suite:

| Index | Type | Name | Size | Complexity |
| --- | --- | --- | --- | --- |
| 0 | debug | identity | n | n |
| 1 | debug | not | n | n |
| 2 | scale | concat | 2n | n |
| 3 | sort | bubble_sort | n | n^2 |
| 4 | sort | quicksort | n | n log(n) |
| 5 | float | correlation | (n/10)^2 | n |
| 6 | float | 2mm | n/3 | n^(3/2) |
| 7 | float | 3mm | n/4 | n^(3/2) |
| 8 | float | cholesky | n | n^(3/2)

Examples:
```
7,8,5,4
4,5,1,4
7,8,2,2,7,8,2,2,7
```

## Build

- ```make```: build wasm programs.
- ```make aot```: build wasm apps into AOT.
- ```make rustpython.aot```: compile rustpython. Not included in ```make aot```.
