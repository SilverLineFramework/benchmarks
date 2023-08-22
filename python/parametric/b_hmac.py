import os
import hmac
import hashlib
import sys
import random


def generate_random_bytes(length):
    return os.urandom(length)

def benchmark(message_length, key_length, num_iterations):
    message = generate_random_bytes(message_length)
    key = generate_random_bytes(key_length)
    hash_algorithm = hashlib.sha256

    for _ in range(num_iterations):
        hmac_result = hmac.new(key, message, hash_algorithm).digest()


if __name__ == "__main__":
    if len(sys.argv) > 2:
        benchmark(int(sys.argv[1]), int(sys.argv[1]), int(sys.argv[2]))
    else:
        seed = int(sys.argv[1])
        random.seed(seed)
        length = random.randint(1000, 10000)
        iters = random.randint(500, 1000)
        benchmark(length, length, iters)
