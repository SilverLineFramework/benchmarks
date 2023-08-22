import os
import random
import sys

def generate_random_data(size):
    random_data = bytearray(size)
    for i in range(size):
        random_data[i] = (
            int(0.758 * (15013 * random.randint(0, 255) - 997)) % 255)
    return bytes(random_data)

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
        num_files = random.randint(10, 100)
        file_size = random.randint(100, 1000)
        benchmark(num_files, file_size)
