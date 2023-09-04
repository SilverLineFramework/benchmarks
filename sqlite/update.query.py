"""Generate random queries."""

import random
import sys


_create = """CREATE TABLE TEST(x,y,z);
INSERT INTO TEST (x,y,z)
  SELECT abs(RANDOM()) % 1000, RANDOM(), RANDOM()
  FROM (SELECT * FROM (
         (SELECT 0 UNION ALL SELECT 1) t1,
         (SELECT 0 UNION ALL SELECT 1) t2,
         (SELECT 0 UNION ALL SELECT 1) t3,
         (SELECT 0 UNION ALL SELECT 1) t4,
         (SELECT 0 UNION ALL SELECT 1) t5,
         (SELECT 0 UNION ALL SELECT 1) t6,
         (SELECT 0 UNION ALL SELECT 1) t7,
         (SELECT 0 UNION ALL SELECT 1) t8,
         (SELECT 0 UNION ALL SELECT 1) t9,
         (SELECT 0 UNION ALL SELECT 1) t10,
         (SELECT 0 UNION ALL SELECT 1) t11,
         (SELECT 0 UNION ALL SELECT 1) t12,
         (SELECT 0 UNION ALL SELECT 1) t13,
         (SELECT 0 UNION ALL SELECT 1) t14,
         (SELECT 0 UNION ALL SELECT 1) t15,
         (SELECT 0 UNION ALL SELECT 1) t16
         )
    ) LIMIT {n};
UPDATE TEST SET x=x, y={expr}, z={expr} WHERE x < {limit};
UPDATE TEST SET x=x, y={expr}, z={expr} WHERE x < {limit};
UPDATE TEST SET x=x, y={expr}, z={expr} WHERE x < {limit};
UPDATE TEST SET x=x, y={expr}, z={expr} WHERE x < {limit};
UPDATE TEST SET x=x, y={expr}, z={expr} WHERE x < {limit};
"""


def _make_query(s):
    random.seed(s)
    n = random.randint(16384, 65536)
    limit = random.randint(0, 1000)

    operators = ['+', '-', '*', '/', '%']
    tokens = ['RANDOM()', 'x', 'y', 'z', '49331', '49333']
    nt = random.randint(2, 10)
    expr = "RANDOM()" + "".join([
        random.choice(operators) + random.choice(tokens) for _ in range(nt)])

    return _create.format(n=n, limit=limit, expr=expr)


print(_make_query(sys.argv[1]))
