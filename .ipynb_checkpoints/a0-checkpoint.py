# a0.py

# Starter code for assignment 0 in ICS 32 Programming with Software Libraries in Python

# Replace the following placeholders with your information.

# Henry Lee
# hwlee4@uci.edu
# 89041994

user = int(input())

def block(user):
    for i in range(user):
        print(" " * 2 * i + "+-+")
        for j in range(i):
            print(" " * (2 * (j + 1)) + "| |")
            print(" " * (2 * (j + 1)) + "+-+")
        
    print(" " * 2 * n + "| |")
    print(" " * 2 * n + "+-+")

if __name__ == '__main__':
    block(user)
