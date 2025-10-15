"""
Part A: Word Frequencies
------------------------------------------
Reads a text file, tokenizes it, counts frequencies, 
and prints them ordered by decreasing frequency.
"""

import sys

def tokenize(text_file_path: str):
    """
    Reads a file and returns a list of lowercase alphanumeric tokens.
    Non-alphanumeric chars break tokens.
    
    Runtime complexity: O(n)
    n = number of characters
    """
    tokens = []
    current = ""

    try:
        with open(text_file_path, "r", encoding="utf-8", errors="ignore") as f:
            while True:
                c = f.read(1)
                if not c:
                    break
                if c.isalnum():
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

def compute_word_frequencies(tokens: list):
    """
    Counts how many times each token appears.
    
    Runtime Complexity: O(m)
    m = number of tokens
    """
    freq_map = {}
    for x in tokens:
        if x in freq_map:
            freq_map[x] += 1
        else:
            freq_map[x] = 1
    return freq_map

def print_frequencies(freq_map: dict):
    """
    Prints word frequencies sorted by decreasing frequency.
    
    Runtime Complexity: O(k log k)
    k = number of unique tokens
    """
    sorted_items = sorted(freq_map.items(), key=lambda x: x[1], reverse=True)
    for token, count in sorted_items:
        print(f"{token} -> {count}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 PartA.py <textfile>")
        sys.exit(1)

    file_path = sys.argv[1]
    tokens = tokenize(file_path)
    freq_map = compute_word_frequencies(tokens)
    print_frequencies(freq_map)
