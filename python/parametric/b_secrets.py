import secrets
import sys
import random

def benchmark(num_iterations, string_length):
    for _ in range(num_iterations):
        random_string = secrets.token_hex(string_length)

if __name__ == "__main__":
    if len(sys.argv) > 2:
        benchmark(int(sys.argv[1]), int(sys.argv[2]))
    else:
        seed = int(sys.argv[1])
        random.seed(seed)
        num_iterations = random.randint(1000, 5000)
        data_size = random.randint(5000, 10000)
        benchmark(num_iterations, data_size)