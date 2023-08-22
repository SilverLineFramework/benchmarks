import sys
import random

def benchmark(num_iterations, num_numbers):
    for _ in range(num_iterations):
        random_numbers = [random.random() for _ in range(num_numbers)]
        _ = sum(random_numbers)
    

if __name__ == "__main__":
    if len(sys.argv) > 2:
        benchmark(int(sys.argv[1]), int(sys.argv[2]))
    else:
        seed = int(sys.argv[1])
        random.seed(seed)
        num_iterations = random.randint(100, 1000)
        data_size = random.randint(100, 1000)
        benchmark(num_iterations, data_size)
