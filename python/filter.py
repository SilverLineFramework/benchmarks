import subprocess
import os
from tqdm import tqdm

PYTHON="./btime ../../runtimes/bin/iwasm -v=0 --dir=. python.iwasm.aot python-tests/{}"

def _run(p):
    if p.endswith(".py") and p.startswith("test"):
        with open("results/{}".format(p), 'w') as f:
            subprocess.call(PYTHON.format(p), shell=True, stdout=f, stderr=f)


for p in tqdm(os.listdir("python-tests")):
    _run(p)
