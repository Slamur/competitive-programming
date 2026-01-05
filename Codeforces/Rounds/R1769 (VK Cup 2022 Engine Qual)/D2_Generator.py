import random


def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


def solve():
    values = "6789TJQKA"
    modes = "CDSH"

    nine = values.index('9')
    players_count = 2

    all_cards = []
    for mode in range(len(modes)):
        for value in range(len(values)):
            all_cards.append((value - nine, mode))

    hand_size = len(all_cards) // players_count

    def get_ans(hands):
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

        best_result = [dict() for _ in range(players_count)]

        def calc_result(segments, player, waiting_counts):
            state = segments_to_state(segments)
            if state in best_result[player]:
                return best_result[player][state]

            possible = []
            waiting_count = waiting_counts[player]

            hand = hands[player]
            for card in hand:
                value, mode = card
                if segments[mode] is None:
                    if value == 0:
                        possible.append(card)
                else:
                    left, right = segments[mode]
                    if value == left - 1 or value == right + 1:
                        possible.append(card)

            other_player = 1 - player

            if len(possible) == 0:
                best_result[player][state] = calc_result(segments, other_player, waiting_counts)
            elif waiting_count == 1:
                waiting_counts[player] -= 1
                best_result[player][state] = waiting_counts[1] - waiting_counts[0]
                waiting_counts[player] += 1
            else:
                best_result[player][state] = hand_size * (-1 if player == 0 else 1)
                player_func = max if player == 0 else min

                for value, mode in possible:
                    mode_segment = segments[mode]

                    if value == 0:
                        segments[mode] = (0, 0)
                    else:
                        left, right = mode_segment
                        segments[mode] = (min(left, value), max(right, value))

                    waiting_counts[player] -= 1
                    result = calc_result(segments, other_player, waiting_counts)
                    waiting_counts[player] += 1

                    segments[mode] = mode_segment

                    best_result[player][state] = player_func(best_result[player][state], result)

            return best_result[player][state]

        alice, bob = 0, 1

        start = [None] * 4
        start_waiting = [hand_size, hand_size]
        alice_result = calc_result(start, alice, start_waiting)
        bob_result = calc_result(start, bob, start_waiting)

        return abs(alice_result - bob_result)

    def card_to_str(card):
        value, mode = card
        return values[value + nine] + modes[mode]

    need_size = read_int()

    results_to_hands = dict()
    while len(results_to_hands) < need_size:
        random.shuffle(all_cards)

        gen_hands = [
            all_cards[player * hand_size:(player + 1) * hand_size]
            for player in range(players_count)
        ]

        result = get_ans(gen_hands)
        if result not in results_to_hands:
            results_to_hands[result] = [
                list(map(card_to_str, hand))
                for hand in gen_hands
            ]

    ans_hands_list = list(results_to_hands.values())[:need_size]
    for ans_hands in ans_hands_list:
        for ans_hand in ans_hands:
            print(*ans_hand)
        print()


if __name__ == '__main__':
    solve()
