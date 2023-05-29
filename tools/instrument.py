import os
import subprocess


files = os.listdir("wasm/sod")
for f in files:
    if f.endswith(".wasm"):
        dst = os.path.join("wasm/instrumented", f.replace(".wasm", ".lc.wasm"))
        src = os.path.join("wasm/sod", f)
        subprocess.call([
            "./wasm-instrument/instrument", "-s", "loop-count", "-o", dst, src
        ])
