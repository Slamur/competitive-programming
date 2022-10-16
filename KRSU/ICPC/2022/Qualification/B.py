def read_int():
    return int(input())


iterations = read_int()

it_in_sec = 10**8
sec_in_min = 60
min_in_hour = 60
hour_in_day = 24

seconds = iterations // it_in_sec

minutes = seconds // sec_in_min
seconds %= sec_in_min

hours = minutes // min_in_hour
minutes %= min_in_hour

days = hours // hour_in_day
hours %= hour_in_day

print(days, hours, minutes, seconds)
