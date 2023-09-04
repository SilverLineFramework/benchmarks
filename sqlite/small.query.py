"""Generate random queries."""

import random
import sys


def _make_query(s):
    chars = "AAAA%%%__1"
    tables = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50]

    random.seed(s)
    like = ''.join(
        random.choice(chars) for _ in range(random.randint(1, 7)))
    table = random.choice(tables)
    iters = random.randint(20, 100)

    query = "SELECT * FROM test{t} WHERE x LIKE '{like}';".format(
        t=table, like=like)
    return " ".join([query for _ in range(iters)])


print(_make_query(sys.argv[1]))
