#!/usr/bin/python3

import re
import sys
from pathlib import Path

pattern=r"^@rtloop_.*hidden"

num_matches = 0
dir_path = Path('ll/polybench-raw')
for path in dir_path.iterdir():
    if(str(path).endswith('.inst.ll')):
        f = open(path, 'r')
        num_matches = len(re.findall(pattern, f.read(), re.MULTILINE))
        print(path.name, " : ", num_matches)

