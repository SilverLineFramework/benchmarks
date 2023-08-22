import os
import math
import random
import sys

def benchmark(num_iterations, max_value):
    # Generate random data
    random_numbers = [int.from_bytes(os.urandom(4), byteorder='big') % max_value for _ in range(num_iterations)]

    # Perform calculations using the math library
    sum_result = sum(random_numbers)
    sqrt_results = [math.sqrt(num) for num in random_numbers]
    log_results = [math.log(num + 1) for num in random_numbers]
    factorial_results = [math.factorial(num) for num in random_numbers]
    cosine_results = [math.cos(num) for num in random_numbers]


if __name__ == "__main__":
    if len(sys.argv) > 2:
        benchmark(int(sys.argv[1]), int(sys.argv[2]))
    else:
        seed = int(sys.argv[1])
        random.seed(seed)
        iters = random.randint(50, 500)
        maxval = random.randint(1000, 4000)
        benchmark(iters, maxval)
