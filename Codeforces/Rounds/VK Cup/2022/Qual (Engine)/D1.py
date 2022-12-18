def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


def solve():
    values = "6789TJQKA"
    nine = values.index('9')

    modes = "CDSH"

    def parse_card(card_str):
        value = values.index(card_str[0])
        mode = modes.index(card_str[1])

        return value - nine, mode

    def read_hand():
        return list(map(parse_card, input().split()))

    players_count = 2
    hands = [read_hand() for _ in range(players_count)]

    def get_ans():
        left_size = nine + 1
        right_size = len(values) - nine

        empty = left_size * right_size
        total = empty + 1

        def segments_to_state(segments):
            state = 0
            for segment in segments:
                segment_value = empty

                if segment is not None:
                    left, right = segment
                    segment_value = abs(left) * right_size + abs(right)

                state *= total
                state += segment_value

            return state

        win = [dict() for _ in range(players_count)]

        def is_winner(segments, player):
            state = segments_to_state(segments)
            if state in win[player]:
                return win[player][state]

            used = 0
            possible = []

            hand = hands[player]
            for card in hand:
                value, mode = card
                if segments[mode] is None:
                    if value == 0:
                        possible.append(card)
                else:
                    left, right = segments[mode]
                    if left <= value <= right:
                        used += 1
                    elif value == left - 1 or value == right + 1:
                        possible.append(card)

            other_player = 1 - player

            if len(possible) == 0:
                win[player][state] = not is_winner(segments, other_player)
            elif used == len(hand) - 1:
                win[player][state] = True
            else:
                win[player][state] = False

                for value, mode in possible:
                    mode_segment = segments[mode]

                    if value == 0:
                        segments[mode] = (0, 0)
                    else:
                        left, right = mode_segment
                        segments[mode] = (min(left, value), max(right, value))

                    other_is_winner = is_winner(segments, other_player)
                    segments[mode] = mode_segment

                    if not other_is_winner:
                        win[player][state] = True
                        break

            return win[player][state]

        alice, bob = 0, 1
        return alice if is_winner([None] * 4, alice) else bob

    winner = get_ans()
    names = ['Alice', 'Bob']
    print(names[winner])


if __name__ == '__main__':
    solve()
