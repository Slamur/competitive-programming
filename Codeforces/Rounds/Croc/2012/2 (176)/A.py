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
    
def calc_profit(buy_prices, 
                buy_counts, 
                sell_prices,
                capacity):
    profit_with_count = [
        (max(sell_prices[i] - buy_prices[i], 0), buy_counts[i])
        for i in range(len(buy_prices))
    ]
    
    profit_with_count = reversed(
        sorted(profit_with_count)
    )
    
    profit = 0
    for product_profit, count in profit_with_count:
        delta = min(capacity, count)
        capacity -= delta
        
        profit += delta * product_profit
        
    return profit

def get_answer(planets_count,
               planets,
               products_count,
               capacity):

    ans = 0
    for buy in range(planets_count):
        buy_prices, _, buy_counts = planets[buy]
        for sell in range(planets_count):
            _, sell_prices, _ = planets[sell]
            profit = calc_profit(
                buy_prices, 
                buy_counts, 
                sell_prices,
                capacity
            )
            ans = max(ans, profit)
    
    return ans
    
def read_planet(products_count):
    input() # name
    
    buy_prices = []
    sell_prices = []
    buy_counts = []
    
    for _ in range(products_count):
        buy_price, sell_price, buy_count = read_ints()
        buy_prices.append(buy_price)
        sell_prices.append(sell_price)
        buy_counts.append(buy_count)
    
    return [
        buy_prices, sell_prices, buy_counts
    ]

def solve():
    planets_count, products_count, capacity = read_ints()
    
    planets = [
        read_planet(products_count) 
        for _ in range(planets_count)
    ]
    
    ans = get_answer(
        planets_count,
        planets,
        products_count,
        capacity
    )
    print(ans)


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
