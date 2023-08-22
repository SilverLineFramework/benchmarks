import os
import lzma
import random
import sys

def generate_random_data(size):
    return os.urandom(size)

def benchmark(input_size, compression_level):
    input_data = generate_random_data(input_size)
    
    compressed_data = lzma.compress(input_data, preset=compression_level)
    decompressed = lzma.decompress(compressed_data)

if __name__ == "__main__":
    if len(sys.argv) > 2:
        benchmark(int(sys.argv[1]), int(sys.argv[2]))
    else:
        seed = int(sys.argv[1])
        random.seed(seed)
        data_size = random.randint(25000, 250000)
        compression_level = random.randint(5, 9)
        benchmark(data_size, compression_level)
