import sys
import secrets
import hashlib
import random

def benchmark(num_iterations, data_size):
    for _ in range(num_iterations):
        # Generate random data
        random_data = secrets.token_bytes(data_size)

        # Hash the random data using SHA-256
        sha256_hash = hashlib.sha256(random_data).hexdigest()

if __name__ == "__main__":
    if len(sys.argv) > 2:
        benchmark(int(sys.argv[1]), int(sys.argv[2]))
    else:
        seed = int(sys.argv[1])
        random.seed(seed)
        num_iterations = random.randint(1000, 5000)
        data_size = random.randint(1000, 5000)
        benchmark(num_iterations, data_size)
