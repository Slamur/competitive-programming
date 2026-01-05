#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;


int get_bit(ll mask, int bit) {
	return (mask >> bit) & 1;
};

int ceil_log(ll x) {
	int res = 0;
	while ((ll(1) << res) < x) ++res;
	return res;
}

ll all_mask(int bits) {
	return (ll(1) << bits) - 1;
}

void solve_test(int need_size) {	
	string values = "6789TJQKA";
	string modes = "CDSH";
	
	int mode_shift = ceil_log(modes.size());
	int mode_mask = all_mask(mode_shift);
	
    	int nine = values.find('9');
	int players_count = 2;
	
	int alice = 0, bob = 1;
    	
	auto card_to_str = [&](int card) {
		int value = (card >> mode_shift), mode = card & mode_mask;
	        
	        string card_str(2, '?');
	        
	        card_str[0] = values[value];
	        card_str[1] = modes[mode];
	        
	        return card_str;
	};
	
	int cards_count = values.size() * modes.size();
	int card_shift = ceil_log(cards_count);
	int card_mask = all_mask(card_shift);

	int hand_size = cards_count / players_count;
	
	int left_size = nine + 1;
	
	int left_shift = ceil_log(left_size);
	int left_mask = all_mask(left_shift);
	
        int right_size = values.size() - nine;

	int empty = (right_size << left_shift);
	
	int total = empty + 1;
	int segment_shift = ceil_log(total);
	int segment_mask = all_mask(segment_shift);
        	
        int max_shift = segment_shift * modes.size();
	int max_state = (1 << max_shift);
	
	int player_shift = ceil_log(players_count);
	int player_mask = all_mask(player_shift);
	
	int cache_size = max_state << player_shift;
	
	using cache_type = vector<int>;
	int none = -100500;
	
	cache_type best_results(cache_size, none);
	vector<ll> last_iterations(cache_size, -1);
	
	auto get_ans = [&](ll player_hands) {
		vi waiting_counts(players_count, hand_size);
		
		int state = 0;
		for (int mode = modes.size() - 1; mode >= 0; --mode) {
			state <<= segment_shift;
			state |= empty;
		}
		
		function<int(int)> calc_result = [&](int player) {
		    int other_player = 1 - player;
		    if (waiting_counts[other_player] == 0) {
		    	return waiting_counts[bob] - waiting_counts[alice];
		    }
	            
	            int full_state = (state << player_shift) | player;
		    if (last_iterations[full_state] == player_hands) {
	                return best_results[full_state];
	            }
	            
	            last_iterations[full_state] = player_hands;

		    ll possible = 0;
		    
		    for (int mode = 0, state_tmp = state; mode < modes.size(); ++mode, state_tmp >>= segment_shift) {
		    	int segment = state_tmp & segment_mask;
		    	int right = segment >> left_shift, left = -(segment & left_mask);
		    	if (segment == empty) right = -1, left = 1;
	    		
	    		int next_left = left - 1;
	    		if (next_left + nine >= 0) {
	    			int card_index = ((next_left + nine) << mode_shift) | mode;
				if (get_bit(player_hands, card_index) == player) {
	    				possible <<= card_shift;
	    				possible |= card_index + 1;
	    			}
	    		}
	    		
	    		int next_right = right + 1;
	    		if (next_right + nine < values.size()) {
	    			int card_index = ((next_right + nine) << mode_shift) | mode;
	    			if (get_bit(player_hands, card_index) == player) {
	    				possible <<= card_shift;
	    				possible |= card_index + 1; 
	    			}
	    		}
		    }

		    int best_result = hand_size * (player == alice ? -1 : 1);

		    if (possible == 0) {
		        best_result = calc_result(other_player);  
		    } else {
		        for (; possible != 0; possible >>= card_shift) {
		        	int card_index = possible & card_mask;
		        	--card_index;
			        
			        int value = (card_index >> mode_shift) - nine, mode = card_index & mode_mask;

		        	int mode_segment_shift = segment_shift * mode;
		        	int mode_segment = (state >> mode_segment_shift) & segment_mask;
		        	
		        	int right = mode_segment >> left_shift, left = -(mode_segment & left_mask);
		        	if (mode_segment == empty) right = -1, left = 1;
		        	
		        	int next_right = max(right, value), next_left = min(left, value);
		        	int next_mode_segment = (next_right << left_shift) | (-next_left);
		        	
		        	int state_update = ((mode_segment ^ next_mode_segment) << mode_segment_shift);
		        	
		        	state ^= state_update;
		            	waiting_counts[player] -= 1;
		            	
		            	int result = calc_result(other_player);
		            	
		            	waiting_counts[player] += 1;
		            	state ^= state_update;

			        best_result = (player == alice) 
			        	? max(best_result, result)
			        	: min(best_result, result);
			}
		    }	

		    return best_results[full_state] = best_result;
		};

	        int alice_result = calc_result(alice);
	        int bob_result = calc_result(bob);
	        
        	return abs(alice_result - bob_result);
	};

	ll all_cards_mask = (ll(1) << cards_count) - 1;
	
	vi all_card_indexes(cards_count);
	for (int i = 0; i < cards_count; ++i) all_card_indexes[i] = i;
	
	auto mask_to_vectors = [&](ll player_hands) {
		vector<vector<string>> ans_hands(players_count);
		for (int card_index = 0; card_index < cards_count	; ++card_index) {
			int player = get_bit(player_hands, card_index);
			ans_hands[player].push_back(
				card_to_str(card_index)
			);
		}
		return ans_hands;
	};
	
	auto print_hands = [&](vector<vector<string>>& ans_hands) {
		for (auto ans_hand : ans_hands) {
			for (auto card : ans_hand) cout << card << " ";
			cout << "\n";
		}
		cout << endl;
	};
	
	unordered_map<int, vector<vector<string>>> results_to_hands;
	unordered_set<ll> processed_hands;
	
	auto rng = std::default_random_engine {};
	
	int verbose = 1000;
	for (int it = 0; results_to_hands.size() < need_size; ++it) {
		shuffle(all_card_indexes.begin(), all_card_indexes.end(), rng);
		
		auto start = all_card_indexes.begin(), mid = start + hand_size, end = mid + hand_size;
		vi alice_hand(start, mid), bob_hand(mid, end);
		
		ll player_hands = 0;
		for (int card : alice_hand) player_hands |= (ll(alice) << card);
		for (int card : bob_hand) player_hands |= (ll(bob) << card);
	
		ll reverse_hands = all_cards_mask ^ player_hands;
		
		if (it % verbose == verbose - 1) {
			cout << it << " " << processed_hands.size() << " " << results_to_hands.size() << endl;
			for (auto& [result, _] : results_to_hands) {
				cout << result << " ";
			}
			cout << endl;
		}
		
		ll cache_hands = min(player_hands, reverse_hands);
		if (processed_hands.count(cache_hands)) continue;
		processed_hands.insert(cache_hands);
		
        	int result = get_ans(player_hands);
        	
        	if (!results_to_hands.count(result)) {	
        		results_to_hands[result] = mask_to_vectors(player_hands);
        	}
		
	}
	
	for (auto [_, ans_hands] : results_to_hands) {
		print_hands(ans_hands);
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
