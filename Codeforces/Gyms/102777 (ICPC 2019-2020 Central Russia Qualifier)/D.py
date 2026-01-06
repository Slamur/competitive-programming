def read_ints():
    return map(int, input().split())


def read_int():
    return int(input())


duration = read_int()


def get_answer():
    m_in_h = 60
    h_in_day = 24
    m_in_day = m_in_h * h_in_day
    
    def get_digits(time):
        h = time // m_in_h
        m = time % m_in_h
        
        h1 = h // 10
        h2 = h % 10
    
        m1 = m // 10
        m2 = m % 10
        
        return (h1, h2, m1, m2)


    for start in range(m_in_day):
        end = (start + duration) % m_in_day
        
        sd = get_digits(start)
        ed = get_digits(end)
        if len(set(sd) | set(ed)) == 8:
            h1, h2, m1, m2 = sd
            return f'{h1}{h2}:{m1}{m2}'

    return 'PASS'


ans = get_answer()
print(ans)

