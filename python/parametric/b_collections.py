import os
import os.path
import collections
import sys
import random

def generate_random_string(length):
    return os.urandom(length).hex()

def benchmark(num_lists, list_length):
    query_length = 32
    num_queries = list_length
    
    # Generate random data for lists
    lists = []
    for _ in range(num_lists):
        random_list = [generate_random_string(query_length) for _ in range(list_length)]
        lists.append(random_list)

    # Generate random data for queries
    queries = [generate_random_string(query_length) for _ in range(num_queries)]

    # Perform benchmarking operations
    counter_list = [collections.Counter(lst) for lst in lists]
    intersection_result = set.intersection(*map(set, lists))
    dict_of_counters = {
        generate_random_string(query_length):
            collections.Counter(queries) for _ in range(num_lists)
    }

    return counter_list, intersection_result, dict_of_counters

if __name__ == "__main__":
    if len(sys.argv) > 2:
        benchmark(int(sys.argv[1]), int(sys.argv[2]))
    else:
        seed = int(sys.argv[1])
        random.seed(seed)
        num_lists = random.randint(50, 250)
        list_length = random.randint(100, 500)
        benchmark(num_lists, list_length)
