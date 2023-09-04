"""Generate random queries."""

import random
import sys


def _make_query(s):
    chars = "AAAA%%%__1"
    tables = [50, 100, 150, 200, 250, 300, 350, 400, 450, 500]

    random.seed(s)
    like = ''.join(random.choice(chars) for _ in range(random.randint(1, 7)))
    table = random.choice(tables)
    return "SELECT * FROM test{} WHERE x LIKE '{}';".format(table, like)


print(_make_query(sys.argv[1]))
