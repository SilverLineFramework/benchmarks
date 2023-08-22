import os
import array
import sys
import random

def benchmark(array_size, iterations):
    # Generate random bytes for the array
    random_bytes = os.urandom(array_size)
    
    # Create an array from the random bytes
    int_array = array.array('B', random_bytes)

    # Perform some operations on the array
    for _ in range(iterations):
        int_array.append(random_bytes[0])
        int_array.pop(0)
        int_array.count(25)

if __name__ == "__main__":
    if len(sys.argv) > 2:
        benchmark(int(sys.argv[1]), int(sys.argv[2]))
    else:
        seed = int(sys.argv[1])
        random.seed(seed)
        size = random.randint(100, 2000)
        iters = random.randint(100, 2000)
        benchmark(size, iters)
