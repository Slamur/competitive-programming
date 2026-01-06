# with open('input.txt', 'r') as file:
#     input_lines = file.readlines()
# 
# 
# def fast_input():
#     for line in input_lines:
#         yield line
# 
# 
# fast_input_reader = fast_input()
# 
# 
# def input():
#     return fast_input_reader.__next__()

def read_ints():
    return map(int, input().split())


def read_int():
    return int(input())


width = 3
height = 3


def get_symbol(text, pos, spaces=0):
    symbol = []
    start = spaces * pos + width * pos
    end = start + width
    for line in text:
        symbol.append(line[start:end])

    return symbol


digits_statement = [
    ' _     _  _     _  _  _  _  _ ',
    '| |  | _| _||_||_ |_   ||_||_|',
    '|_|  ||_  _|  | _||_|  ||_| _|',
]

digits = [
    get_symbol(digits_statement, i)
    for i in range(10)
]

sign_statement = [
    '         ',
    '_|____---',
    ' |    ---',
]

signs = [
    get_symbol(sign_statement, i)
    for i in range(3)
]

signs_str = "+-="

expression = [input() for _ in range(height)]

res = 0
answer = []

last_sign = 1
cur_value = 0

exp_len = (len(expression[2]) + 1) // 4
for i in range(exp_len):
    symbol = get_symbol(expression, i, spaces=1)
    if symbol in digits:
        digit = digits.index(symbol)
        cur_value *= 10
        cur_value += digit
    else:
        if cur_value > 0 or len(answer) > 0:
            answer.append(str(cur_value))

            real_value = cur_value * last_sign
            res += real_value

            last_sign = 1
            cur_value = 0

        sign = signs.index(symbol)
        sign_str = signs_str[sign]
        if '+' == sign_str:
            last_sign = 1
        if '-' == sign_str:
            last_sign = -1

        answer.append(sign_str)

answer.append(str(res))

print(''.join(answer))
