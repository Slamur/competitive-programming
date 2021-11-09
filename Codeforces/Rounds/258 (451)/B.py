import sys
import os.path

input_file_name = 'input.txt'
output_file_name = 'output.txt'

if not os.path.isfile(input_file_name):
    input_file_name = ''

if not os.path.isfile(output_file_name):
    output_file_name = ''

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


def read_int():
    return int(input())


def read_strings():
    return input().split()


def read_ints():
    return map(int, read_strings())


output_lines = [[]]

SPACE = ' '
ENDL = '\n'


def print(output, sep=ENDL):
    line = str(output)
    output_lines[-1].append(line)
    if ENDL == sep:
        output_lines.append([])


def yes_no(value, yes="YES", no="NO"):
    print(yes if value else no)
    return value

def get_answer(n, a):
    sorted_a = sorted(a)
    
    start = n
    for i in range(n):
        if a[i] != sorted_a[i]:
            start = i
            break
        
    end = 0
    for i in range(n, 0, -1):
        if a[i - 1] != sorted_a[i - 1]:
            end = i
            break
            
    if start > end:
        return (0, 0)
    
    a[start:end] = reversed(a[start:end])
    return (start, end - 1) if a == sorted(a) else None

def solve():
    n = read_int()
    a = list(read_ints())
    
    ans = get_answer(n, a)
    if yes_no(ans is not None, 'yes', 'no'):
        start, end = ans
        print(start + 1, sep=SPACE)
        print(end + 1)


def main():
    solve()

    output = ENDL.join(
        SPACE.join(line_parts)
        for line_parts
        in output_lines
    ) + ENDL

    if len(output_file_name) > 0:
        with open(output_file_name, 'w') as file:
            file.write(output)
    else:
        sys.stdout.write(output)


if __name__ == '__main__':
    main()
