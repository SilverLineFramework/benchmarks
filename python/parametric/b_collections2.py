import os
import os.path
import collections
import sys
import random

def generate_random_string(length):
    return os.urandom(length).hex()

def benchmark(num_defaultdicts, num_items_per_dict, key_length=32, value_length=32):
    # Generate random data for defaultdicts
    defaultdicts = []
    for _ in range(num_defaultdicts):
        random_defaultdict = collections.defaultdict(
            lambda: generate_random_string(value_length))
        for _ in range(num_items_per_dict):
            key = generate_random_string(key_length)
            value = generate_random_string(value_length)
            random_defaultdict[key] = value
        defaultdicts.append(random_defaultdict)

    # Perform benchmarking operations
    combined_defaultdict = collections.defaultdict(str)
    for defaultdict in defaultdicts:
        for key, value in defaultdict.items():
            combined_defaultdict[key] = value

    return combined_defaultdict

if __name__ == "__main__":
    if len(sys.argv) > 2:
        benchmark(int(sys.argv[1]), int(sys.argv[2]))
    else:
        seed = int(sys.argv[1])
        random.seed(seed)
        num_dicts = random.randint(50, 200)
        items = random.randint(100, 500)
        benchmark(num_dicts, items)
