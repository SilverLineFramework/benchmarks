import os
import base64
import sys
import random

def generate_random_data(size):
    return os.urandom(size)

def benchmark(num_iterations, data_size):
    data = generate_random_data(data_size)

    for _ in range(num_iterations):
        encoded_data = base64.b64encode(data)
        data = base64.b64decode(encoded_data)

if __name__ == "__main__":
    if len(sys.argv) > 2:
        benchmark(int(sys.argv[1]), int(sys.argv[2]))
    else:
        seed = int(sys.argv[1])
        random.seed(seed)
        iters = random.randint(5, 20)
        size = random.randint(200000, 2000000)
        benchmark(iters, size)
