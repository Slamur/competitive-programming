import math
import os.path
import sys

from typing import List

filename = ''
input_file_name = filename + '.in'
output_file_name = filename + '.out'

if not os.path.isfile(input_file_name):
    input_file_name = ''

if len(input_file_name) > 0:
    with open(input_file_name, 'r') as file:
        input_lines = file.readlines()
else:
    input_lines = sys.stdin.readlines()


def fast_input():
    for line in input_lines:
        yield line


fast_input_reader = fast_input()


def input():
    return fast_input_reader.__next__()


def read_ints():
    return map(int, input().split())


def read_int():
    return int(input())


output_lines = [[]]

SPACE = ' '
ENDL = '\n'


def print(output, sep=ENDL):
    line = str(output)
    output_lines[-1].append(line)
    if ENDL == sep:
        output_lines.append([])

        
def solve():
    a, b = read_ints()
    print(a + b)


def main():
    solve()

    output = ENDL.join(
        SPACE.join(line_parts)
        for line_parts
        in output_lines
    ) + ENDL

    if len(input_file_name) > 0 and len(output_file_name) > 0:
        with open(output_file_name, 'w') as output_file:
            output_file.write(output)
    else:
        sys.stdout.write(output)


if __name__ == '__main__':
    main()
