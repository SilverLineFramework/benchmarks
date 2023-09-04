"""Generate random queries."""

import random
import sys


def _make_query(s):
    random.seed(s)
    t1 = random.randint(0, 99)
    t2 = t1
    while t2 == t1:
        t2 = random.randint(0, 99)
    return (
        "SELECT test{t1}.data, test{t2}.data FROM test{t1} "
        "JOIN test{t2} ON test{t1}.x=test{t2}.x;".format(t1=t1, t2=t2))


print(_make_query(sys.argv[1]))
