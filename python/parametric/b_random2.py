import random
import sys

def benchmark(num_iterations, sequence_length):
    sequence = list(range(sequence_length))
    
    for _ in range(num_iterations):
        shuffled_sequence = sequence.copy()
        random.shuffle(shuffled_sequence)


if __name__ == "__main__":
    if len(sys.argv) > 2:
        benchmark(int(sys.argv[1]), int(sys.argv[2]))
    else:
        seed = int(sys.argv[1])
        random.seed(seed)
        num_iterations = random.randint(10, 100)
        data_size = random.randint(100, 1000)
        benchmark(num_iterations, data_size)
