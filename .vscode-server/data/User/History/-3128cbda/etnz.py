"""
Part B: Intersection of Two Files
------------------------------------------
Reads two text files, tokenizes them based on
Part A code, and prints number of
common unique tokens
"""

import sys

def tokenize(text_file_path: str):
    """
    Reads a file and returns list of lowercase alphanumeric tokens.
    Handles bad input gracefully (skips invalid chars).
    
    Runtime Complexity: O(n)
    n = number of characters in the file; each character processed once and dictionary/set operations are O(1)
    """
    tokens = []
    current = ""

    try:
        with open(text_file_path, "r", encoding="utf-8", errors="ignore") as f:
            while True:
                c = f.read(1)
                if not c:
                    break
                if ('a' <= c.lower() <= 'z') or ('0' <= c <= '9'):
                    current += c.lower()
                else:
                    if current:
                        tokens.append(current)
                        current = ""
            if current:
                tokens.append(current)
    except Exception as e:
        print(f"Error reading file {text_file_path}: {e}")
        sys.exit(1)

    return tokens

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
