"""Generate random queries."""

import random
import sys


def _make_query(s):
    random.seed(s)

    options = [
        ["*", "x"],
        ["*", "data"],
        ["DISTINCT *", "x"],
        ["DISTINCT *", "data"],
        ["x", "x"],
        ["DISTINCT x", "x"],
        ["data", "data"],
        ["DISTINCT data", "data"]
    ]
    select, order = random.choice(options)
    t = random.randint(0, 99)
    iters = random.randint(10, 20)

    return " UNION ALL ".join([
        "SELECT {sel} FROM test{t}".format(sel=select, t=t)
        for _ in range(iters)
    ]) + " ORDER BY {};".format(order)


print(_make_query(sys.argv[1]))
