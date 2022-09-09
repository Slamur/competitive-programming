def second_transform(formula):
    return formula.lower()


def third_transform(formula):
    vowels = "aeoiu"
    return "".join(map(lambda c: "?" if c in vowels else c, formula))


needs_count = int(input())
needs = input().split()

first = set(needs)
second = dict()
third = dict()

for i, formula in enumerate(needs):
    sf = second_transform(formula)
    tf = third_transform(sf)

    if not sf in second:
        second[sf] = i

    if not tf in third:
        third[tf] = i


def match(formula):
    if formula in first:
        return formula

    sf = second_transform(formula)
    if sf in second:
        return needs[second[sf]]

    tf = third_transform(sf)
    if tf in third:
        return needs[third[tf]]

    return ""


formulas_count = int(input())
formulas = input().split()
answer = list(map(match, formulas))
print(*answer)
