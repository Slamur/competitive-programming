n = int(input())
a = list(map(int, input().split()))

ans_old_price, ans_new_price = 1, 1
ans = (-1, -1)

has = 1000
volume = 1000

pref_min = 0

for i in range(n):
    new_price = a[i]
    if a[pref_min] > new_price:
        pref_min = i

    old_price = a[pref_min]

    # profit = (new_price - old_price) * (money / old_price)
    # profit = (new_price / old_price - 1) * money
    # max_profit <-> max(new_price / old_price)

    # ans_new / ans_old < new / old
    # ans_new * old < new * ans_old

    if ans_new_price * old_price < new_price * ans_old_price:
        ans = (pref_min, i)
        ans_old_price, ans_new_price = old_price, new_price

start, end = ans
print(start + 1, end + 1)
