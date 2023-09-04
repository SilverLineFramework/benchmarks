"""Generate test database for small database iteration benchmark."""

import sqlite3
from tqdm import tqdm
import numpy as np
import sys


def _str():
    """Make random a-z string using numpy for speed."""
    return np.random.randint(
        65, 91, size=255, dtype=np.uint8).tobytes().decode('ascii')


def _generate(out, size):
    con = sqlite3.connect(out)
    cur = con.cursor()
    cur.execute("CREATE TABLE test{}(x)".format(size))
    con.commit()

    for _ in tqdm(range(100), desc=str(size)):
        rows = [(_str(),) for _ in range(size)]
        cur = con.cursor()
        cur.executemany("INSERT INTO test{} VALUES(?)".format(size), rows)
        con.commit()


if __name__ == '__main__':

    out = sys.argv[1]
    np.random.seed(42)
    for i in range(10):
        _generate(out, 5 * (i + 1))
