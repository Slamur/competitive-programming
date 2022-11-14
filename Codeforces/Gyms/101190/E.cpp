#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;
using vi = vector<int>;
using vll = vector<ll>;
using ii = pair<int, int>;

void init_io(const string& filename) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	if (filename.size() > 0) {
	    freopen((filename + ".in").c_str(), "rt", stdin);
	    freopen((filename + ".out").c_str(), "wt", stdout);   
	}
	
	cout << setprecision(10) << fixed;
}

pair<vector<ii>, int> create_segments(const vector<ii>& operations) {
	vector<ii> segments; // height, length
	
	int last_height = 0;
	int last_time = 0;

	for (auto& [time, count] : operations) {
		segments.emplace_back(
			last_height, 
			time - last_time
		);
		
		last_height -= count; // reverse sign
		last_time = time;
	}
	
	return make_pair(segments, last_height);
}

const int SEGMENT = 0, QUERY = 1;

vector<pair<int, ii>> create_events(const vector<ii>& segments, const vi& queries) {
	vector<pair<int, ii>> events; // height, type, index
	for (int i = 0; i < segments.size(); ++i) {
		auto& [height, length] = segments[i];
		events.emplace_back(
			height, make_pair(SEGMENT, i)
		);
	}
	
	for (int j = 0; j < queries.size(); ++j) {
		events.emplace_back(
			queries[j], make_pair(QUERY, j)
		);
	}
	
	return events;
}

int calc_min_height(const vector<ii>& segments) {
	int min_height = 0;
	for (auto& [height, _] : segments) {
		min_height = min(min_height, height);
	}
	return min_height;
}

ll calc_total_wait(const vector<ii>& segments, int min_height) {
	ll total_wait = 0;
	for (auto& [height, length] : segments) {
		total_wait += (ll)length * (height - min_height);
	}
	
	return total_wait;
}

void solve() {
	// read
	int n, q;
	cin >> n >> q;
	
	vector<ii> operations(n);
	for (auto& [time, count] : operations) {
		string sign;
		cin >> sign >> time >> count;
		
		if ("-" == sign) count = -count;
	}
	
	vi queries(q);
	for (auto& query : queries) cin >> query;
	
	// create segments and inf_height
	// (height, length)
	auto [segments, inf_height] = create_segments(operations);
	
	// create events
	// (height, type, index)
	auto events = create_events(segments, queries);
			
	// calc answers
	vector<bool> is_inf(q, false);
	vll answers(q, -1);
	
	// init values
	int min_height = calc_min_height(segments);
	ll total_wait = calc_total_wait(segments, min_height);
	
	int last_height = min_height;
	int total_length = operations.back().first;
	
	// process events
	sort(events.begin(), events.end());
	for (auto& [height, info] : events) {
	
		// increase histogram level
		ll skipped_wait = (ll)total_length * (height - last_height);
		total_wait -= skipped_wait;
		last_height = height;
	
		// process event
		auto& [type, index] = info;
		
		if (type == SEGMENT) {
			auto& [_, length] = segments[index];
			total_length -= length;
		}
		
		if (type == QUERY) {
			if (height < inf_height) is_inf[index] = true;
			else answers[index] = total_wait;
		}
	}
	
	for (int j = 0; j < q; ++j) {
		if (is_inf[j]) cout << "INFINITY";
		else cout << answers[j];
		cout << "\n";
	}
}

int main() {
	init_io("expect");
	solve();
	
	return 0;
}
