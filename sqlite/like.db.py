"""Generate test database files with random strings."""

import sqlite3
import random
from tqdm import tqdm
import numpy as np
import os
import sys


def _string():
    """Make random a-z string using numpy for speed."""
    return np.random.randint(
        65, 91, size=255, dtype=np.uint8).tobytes().decode('ascii')


def _generate(out, size):
    con = sqlite3.connect(out)
    cur = con.cursor()
    cur.execute("CREATE TABLE test{}(x)".format(size))
    con.commit()

    for _ in tqdm(range(100), desc=str(size)):
        rows = [(_string(),) for _ in range(size * 10)]
        cur = con.cursor()
        cur.executemany("INSERT INTO test{} VALUES(?)".format(size), rows)
        con.commit()


if __name__ == '__main__':

    out = sys.argv[1]
    for i in range(10):
        _generate(out, 50 * (i + 1))
