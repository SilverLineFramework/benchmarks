"""Generate test database for `ORDER BY` benchmark."""

import sqlite3
from tqdm import tqdm
import numpy as np
import sys


def _str():
    """Make random a-z string using numpy for speed."""
    return np.random.randint(
        65, 91, size=255, dtype=np.uint8).tobytes().decode('ascii')


def _generate(out):

    con = sqlite3.connect(out)

    for i in tqdm(range(100)):
        size = np.random.randint(1000, 5000)
        nx = np.random.randint(10, 100)
        nd = np.random.randint(10, 100)
        dd = [_str() for _ in range(nd)]

        cur = con.cursor()
        cur.execute("CREATE TABLE test{}(x INTEGER, data TEXT)".format(i))
        con.commit()

        rows = [
            (np.random.randint(0, nx), dd[np.random.randint(0, nd)])
            for _ in range(size)]
        cur = con.cursor()
        cur.executemany("INSERT INTO test{} VALUES(?, ?)".format(i), rows)
        con.commit()


if __name__ == '__main__':
    out = sys.argv[1]
    np.random.seed(42)
    _generate(out)
