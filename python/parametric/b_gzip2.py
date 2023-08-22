import os
import random
import os
import gzip
import sys


def generate_random_bytes(length):
    return os.urandom(length)

def benchmark(file_size, compression_level):
    os.makedirs("tmp", exist_ok=True)
    
    data = generate_random_bytes(file_size)
    
    compressed_filename = f"tmp/compressed_file.gz"
    with gzip.open(compressed_filename, "wb", compresslevel=compression_level) as f:
        f.write(data)

    with gzip.open(compressed_filename, "rb") as f:
        compressed_content = f.read()
        
    os.remove(compressed_filename)


if __name__ == "__main__":
    if len(sys.argv) > 2:
        benchmark(int(sys.argv[1]), int(sys.argv[2]))
    else:
        seed = int(sys.argv[1])
        random.seed(seed)
        data_size = random.randint(200000, 1000000)
        compression_level = random.randint(0, 9)
        benchmark(data_size, compression_level)
