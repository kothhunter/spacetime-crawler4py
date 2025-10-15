"""
Part B: Intersection of Two Files
------------------------------------------
Reads two text files, tokenizes them based on
Part A code, and prints number of
common unique tokens
"""

import sys
from PartA import tokenize

'''
Runtime Complexity (overall): O(n + m)
n = number of characters in file 1, m = number in file 2
'''
if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 PartB.py <file1> <file2>")
        sys.exit(1)

    file1, file2 = sys.argv[1], sys.argv[2]

    tokens1 = tokenize(file1)
    tokens2 = tokenize(file2)

    first_set = set(tokens1)
    second_set = set(tokens2)

    common_tokens = first_set.intersection(second_set)

    print(len(common_tokens))
