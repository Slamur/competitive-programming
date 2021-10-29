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
    if 1 == n:
        return [
            ((0, n), [-a[0]]),
            ((0, n), [0]),
            ((0, n), [0]),
        ]
        
    ans = []
        
    prefix_len = n - 1
    
    first_seg = (0, prefix_len)
    ans.append((
        first_seg,
        (prefix_len * value for value in a[:prefix_len])
    ))
    
    second_seg = (prefix_len, n)
    ans.append((
        second_seg, [-a[-1]]
    ))
    a[-1] = 0
    
    third_seg = (0, n)
    ans.append((
        third_seg,
        (-n * value for value in a)
    ))
    
    return ans

def solve():
    n = read_int()
    a = list(read_ints())
    
    ans = get_answer(n, a)
    for segment, values in ans:
        start, end = segment
        print(start + 1, SPACE)
        print(end)
        print(" ".join(map(str, values)))


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
