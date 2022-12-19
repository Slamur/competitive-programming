#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;

void solve_test(int need_size) {	
	string values = "6789TJQKA";
	string modes = "CDSH";
	
    	int nine = values.find('9');
	int players_count = 2;
	
	vii all_cards;
    	for (int mode = 0; mode < modes.size(); ++mode) {
    		for (int value = 0; value < values.size(); ++value) {
    			all_cards.emplace_back(value - nine, mode);
    		}
    	}

	int hand_size = all_cards.size() / players_count;
	
	int left_size = nine + 1;
        int right_size = values.size() - nine;

	int empty = left_size * right_size;
	ii empty_segment = make_pair(1, -1);
	
	int total = empty + 1;

	auto segments_to_state = [&](vii& segments) {
            int state = 0;
            for (auto [left, right] : segments) {
                int segment_value = empty;

                if (left <= 0 && right >= 0) {
                    segment_value = abs(left) * right_size + abs(right);
                }

                state *= total;
                state += segment_value;
            }

            return state;
        };
	
	auto get_ans = [&]() {
		vii segments(modes.size(), empty_segment);
		vi waiting_counts(players_count, hand_size);
	
		using cache_type = vector<int>;
		
		int max_state = segments_to_state(segments) + 1;
		int none = -100500;
		vector<cache_type> best_result(players_count, cache_type(max_state, none));
		
		vector<vi> card_to_index(modes.size(), vi(values.size()));
		for (int card_index = 0; card_index < all_cards.size(); ++card_index) {
			auto& [value, mode] = all_cards[card_index];
			card_to_index[mode][value + nine] = card_index;
		}
		
		function<int(int)> calc_result = [&](int player) {
	            int state = segments_to_state(segments);
		    if (best_result[player][state] != none) {
	                return best_result[player][state];
	            }

		    vi possible;

		    for (int mode = 0; mode < modes.size(); ++mode) {
		    	if (segments[mode] == empty_segment) {
		    		int nine_index = card_to_index[mode][nine];
		    		if (nine_index / hand_size == player) {
		    			possible.push_back(nine_index);
		    		}
		    	} else {
		    		auto& [left, right] = segments[mode];
		    		
		    		int next_left = left - 1;
		    		if (next_left + nine >= 0) {
		    			int card_index = card_to_index[mode][next_left + nine];
		    			if (card_index / hand_size == player) {
		    				possible.push_back(card_index);
		    			}
		    		}
		    		
		    		int next_right = right + 1;
		    		if (next_right + nine < values.size()) {
		    			int card_index = card_to_index[mode][next_right + nine];
		    			if (card_index / hand_size == player) {
		    				possible.push_back(card_index);
		    			}
		    		}
		    	}
		    }

		    int other_player = 1 - player;

		    if (possible.empty()) {
		        best_result[player][state] = calc_result(other_player);  
		    } else if (waiting_counts[player] == 1) {
		        waiting_counts[player] -= 1;
		        best_result[player][state] = waiting_counts[1] - waiting_counts[0];
		        waiting_counts[player] += 1;
		    } else {
		        best_result[player][state] = hand_size * (player == 0 ? -1 : 1);

		        for (auto& card_index : possible) {
		        	auto& [value, mode] = all_cards[card_index];
		        
		        	auto mode_segment = segments[mode];
		        	
		        	auto& [left, right] = mode_segment;
		            	segments[mode] = make_pair(
		            		min(left, value),
		            		max(right, value)
            			);

		            	waiting_counts[player] -= 1;
		            	int result = calc_result(other_player);
		            	waiting_counts[player] += 1;

		            	segments[mode] = mode_segment;

			        best_result[player][state] = (player == 0) 
			        	? max(best_result[player][state], result)
			        	: min(best_result[player][state], result);
			}
		    }	

		    return best_result[player][state];
		};
		
		int alice = 0, bob = 1;

	        int alice_result = calc_result(alice);
	        int bob_result = calc_result(bob);

        	return abs(alice_result - bob_result);
	};
	
	auto card_to_str = [&](ii& card) {
	        auto [value, mode] = card;
	        
	        string card_str(2, '?');
	        
	        card_str[0] = values[value + nine];
	        card_str[1] = modes[mode];
	        
	        return card_str;
	};

	unordered_map<int, vector<vector<string>>> results_to_hands;

	auto rng = std::default_random_engine {};
	
	while (results_to_hands.size() < need_size) {
		std::shuffle(std::begin(all_cards), std::end(all_cards), rng);

        	int result = get_ans();
	        if (!results_to_hands.count(result)) {	
	        	results_to_hands[result].resize(players_count);
	        	for (int card_index = 0; card_index < all_cards.size(); ++card_index) {
	        		results_to_hands[result][card_index / hand_size].push_back(
	        			card_to_str(all_cards[card_index])
	        		);
	        	}
	        }
	}
	
	for (auto [_, ans_hands] : results_to_hands) {
		for (auto ans_hand : ans_hands) {
			for (auto card : ans_hand) cout << card << " ";
			cout << "\n";
		}
		cout << "\n";
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int need_size;
    	cin >> need_size;
    	
    	using namespace std::chrono;
    	
    	auto start = high_resolution_clock::now();
    	
    	solve_test(need_size);
    	
    	auto stop = high_resolution_clock::now();
    	auto duration = duration_cast<milliseconds>(stop - start);
 
 	int millis_total = duration.count();
 	int seconds = millis_total / 1000, millis = millis_total % 1000;
 	
	cout << "Time taken: " << seconds << " sec " << millis << " ms" << endl;
	
	return 0;
}
