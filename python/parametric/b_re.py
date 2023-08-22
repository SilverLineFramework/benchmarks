import re
import random
import string
import sys

# Generate a list of random strings
def generate_random_strings(num_strings, string_length):
    strings = []
    for _ in range(num_strings):
        random_string = ''.join(
            random.choice(string.ascii_lowercase) for _ in range(string_length))
        strings.append(random_string)
    return strings

def generate_random_regex():
    regex_length = random.randint(5, 15)
    regex_chars = string.ascii_letters + string.digits + ".[]()*+?{}|"
    regex_pattern = ''.join(random.choice(regex_chars) for _ in range(regex_length))
    return regex_pattern

def benchmark(root_seed, num_strings, string_length):
    random.seed(root_seed)
    next_seed = random.randint(0, 2**32 - 1)

    try:
        random_strings = generate_random_strings(num_strings, string_length)
        random_pattern = generate_random_regex()
        compiled_regex = re.compile(random_pattern)
        
        for string in random_strings:
            if compiled_regex.match(string):
                pass
    except:
        benchmark(next_seed, num_strings, string_length)


if __name__ == "__main__":
    if len(sys.argv) > 2:
        benchmark(0, int(sys.argv[1]), int(sys.argv[2]))
    else:
        seed = int(sys.argv[1])
        random.seed(seed)
        num_strings = random.randint(10, 100)
        string_length = random.randint(100, 1000)
        benchmark(seed, num_strings, string_length)
