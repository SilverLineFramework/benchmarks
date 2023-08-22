import os
import random
import string
import gzip
import sys

def generate_random_data(size):
    return ''.join(random.choice(string.ascii_letters) for _ in range(size))

def write_gzip_file(data, filename):
    with gzip.open(filename, 'wt') as f:
        f.write(data)

def read_gzip_file(filename):
    with gzip.open(filename, 'rt') as f:
        content = f.read()
    return content

def benchmark(data_size, num_files):
    os.makedirs("tmp", exist_ok=True)
    
    for i in range(num_files):
        data = generate_random_data(data_size)
        filename = f"tmp/file_{i}.txt.gz"
        write_gzip_file(data, filename)
        
        read_data = read_gzip_file(filename)
        assert data == read_data
        
        os.remove(filename)


if __name__ == "__main__":
    if len(sys.argv) > 2:
        benchmark(int(sys.argv[1]), int(sys.argv[2]))
    else:
        seed = int(sys.argv[1])
        random.seed(seed)
        data_size = random.randint(2000, 20000)
        num_files = random.randint(2, 10)
        benchmark(data_size, num_files)
