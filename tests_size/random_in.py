#!/usr/bin/python3

import random
import sys

def main():
    n = int(sys.argv[1])

    x = []
    for i in range(0,n):
        x.append([ 0 for x in range(0,n)])

    for i in range(0, n):
        for j in range(0, i):
            x[i][j] = random.randint(5,25)

    for i in range(0, n):
        for j in range(i, n):
            if j > i:
                x[i][j] = x[j][i]

    print(n)
    for i in x:
        for j in i:
            print(str(j).rjust(3), end=" ")
        print()

main()
