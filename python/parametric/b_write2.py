import os
import secrets
import random
import sys


def generate_random_data(size):
    return secrets.token_bytes(size)

def create_files(num_files, file_size):
    os.makedirs("tmp", exist_ok=True)
    for i in range(num_files):
        file_name = f"tmp/file_{i}.txt"
        with open(file_name, 'wb') as f:
            random_data = generate_random_data(file_size)
            f.write(random_data)

def delete_files(num_files):
    for i in range(num_files):
        file_name = f"tmp/file_{i}.txt"
        if os.path.exists(file_name):
            os.remove(file_name)

def benchmark(num_files, file_size):   
    create_files(num_files, file_size)
    delete_files(num_files)

if __name__ == '__main__':
    if len(sys.argv) > 2:
        benchmark(int(sys.argv[1]), int(sys.argv[2]))
    else:
        seed = int(sys.argv[1])
        random.seed(seed)
        num_files = random.randint(25, 50)
        file_size = random.randint(200000, 2000000)
        benchmark(num_files, file_size)
