import random


def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


def solve():
    hands_text = """AD JH KD 9C 8H TH 6D 9D JS 6S JC QH QD 7S 7D 7C 8S 6C
9S 7H AH JD 9H TD 8D KC 8C AC QS 6H KH KS TS AS QC TC

6H 8C AS JD 7C 6C 8H KS TD TS AD 9H 9D 8D 6D TC 7H AC
KC AH JH KH 9C QD TH KD JS 7D 7S QH 9S QC QS 6S 8S JC

AH 8D QS 9S 7C JH 6D 6C 9D AC 7S KC JD TC KH QH 8H QD
6H TD 9C KS JS QC 9H 8S 6S JC AS KD 8C 7H AD TH 7D TS

QS TH 7D 6D AD TD 7S 9C KD 8S 6C 9H JD KS KC QD 8C 8H
KH 7C JC AH 7H 8D AS TS JH QC TC JS 9D 6S AC 9S 6H QH

JD QH KH 8C 6S JH 9S 8H TH JS 7C 6C QC 6D QD 8D AD KD
7H AS 9D 7S 9H 6H JC AH TD TC QS 7D 8S TS AC KS 9C KC

TS TH 7S JH TD AC 7C QS 9H 6C KC 9D KS 9S AH 6H 7D KH
QD 8C TC 6S AD AS 8H 8D QC 8S QH JC JD 7H KD 9C JS 6D

AH JS AC JC 7D AD 8D 6S JD KH QS 8H TH 7S KD 8S 7H 9C
6C KS 9S 9H 6D TD 7C 8C TC 9D JH QC AS 6H KC TS QD QH

KC KH JD KD 8C QC 9S 8S AC 9C JH 8D 7H 6D 7D 6S 7C 9D
8H QH QS JC TH KS 9H TS 6H JS 7S AH TC AD QD 6C AS TD

KD 7H JH JC TD 6H 7S KC 6C TS 9S KH AD 6D 7C 8H 8D TC
AC 9D QC 8S 9H QH AS QS 6S TH KS AH 9C 7D QD 8C JD JS

7H 8D 6S AD 6C QS JD 7D 7S 9C AS 9S TD 8H QD KD QC 6H
JH 6D TC 7C 9H KS KH KC JS 9D 8C AH TS 8S JC AC QH TH

JH AD 7C AS 6D TC JD 7D 7S AC QC 6H 9D TH TS 7H 8C 9H
QD KH 8H KD KC QH TD JC 9C 8D AH 6S 8S 9S JS 6C QS KS

9C 6S QS 7C TS JD AD 8D 7D TC AH 9D 6H 8H KS 9S KH QC
JS 7H 9H KC QH QD AS 6D 8S KD TD 8C JC TH AC JH 7S 6C

KH 7H QD QC 8D QH TC 6D 8S AH JD TS 8C TH 7C 7S 9H 6S
9C 7D KS KC JH KD TD QS 6H 9D 9S AC 8H JC JS 6C AS AD
    """

    hand_rows = hands_text.split('\n')

    need_size = read_int()
    need_rows = need_size * 3 - 1

    print(*hand_rows[:need_rows], sep='\n')


if __name__ == '__main__':
    solve()
