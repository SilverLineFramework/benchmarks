import os
import pickle
import random
import sys

def generate_random_string(length):
    random_bytes = os.urandom(length)
    random_string = random_bytes.hex()
    return random_string

def benchmark(data_size, num_iterations):
    data = [generate_random_string(data_size) for _ in range(num_iterations)]

    # Create a temporary directory if it doesn't exist
    tmp_dir = 'tmp'
    if not os.path.exists(tmp_dir):
        os.makedirs(tmp_dir)

    # Serialize data using pickle
    pickle_file = os.path.join(tmp_dir, 'data.pickle')
    with open(pickle_file, 'wb') as f:
        pickle.dump(data, f)

    # Deserialize data using pickle
    with open(pickle_file, 'rb') as f:
        loaded_data = pickle.load(f)

    # Clean up: delete the temporary directory and its contents
    os.remove(pickle_file)
    os.rmdir(tmp_dir)

if __name__ == "__main__":
    if len(sys.argv) > 2:
        benchmark(int(sys.argv[1]), int(sys.argv[2]))
    else:
        seed = int(sys.argv[1])
        random.seed(seed)
        iters = random.randint(1000, 2000)
        size = random.randint(1000, 10000)
        benchmark(size, iters)
