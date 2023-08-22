import sys
import itertools
import random


def benchmark(numbers, r):
    numbers = list(range(numbers))
    for _ in itertools.combinations(numbers, r):
        pass


if __name__ == "__main__":
    if len(sys.argv) > 2:
        benchmark(int(sys.argv[1]), int(sys.argv[2]))
    else:
        seed = int(sys.argv[1])
        random.seed(seed)
        numbers = random.randint(40, 50)
        r = random.randint(3, 5)
        benchmark(numbers, r)
