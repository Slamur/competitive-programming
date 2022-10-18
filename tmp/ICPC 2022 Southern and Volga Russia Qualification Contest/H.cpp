#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

int main() {
	int n, last_page;
	cin >> n >> last_page;
	
	int first_page = 1;
	
	vector<pair<int, int>> already_read(n);
	for (auto& student : already_read) {
		cin >> student.first >> student.second;
	}
	
	const int START = 0, CHECK = 1, END = 2;
	
	vector<pair<int, int>> events;
	events.emplace_back(first_page, CHECK);
	events.emplace_back(last_page, CHECK);
	
	for (auto& [student_first, student_last] : already_read) {
		if (student_first > first_page) {
			events.emplace_back(student_first - 1, CHECK);
		}
		events.emplace_back(student_first, START);
		events.emplace_back(student_last, END);
		if (student_last < last_page) {
			events.emplace_back(student_last + 1, CHECK);
		}
	}
	
	sort(events.begin(), events.end());
	
	int first_not_checked = last_page + 1;
	int last_not_checked = first_page - 1;
	
	int open = 0;
	for (auto& [page, status] : events) {
		if (START == status) {
			open++;
		}
		if (CHECK == status) {
			if (0 == open) {
				first_not_checked = min(first_not_checked, page);
				last_not_checked = max(last_not_checked, page);
			}
		}
		if (END == status) {
			open--;
		}
	}
	
	int ans = max(0, last_not_checked - first_not_checked + 1);
	cout << ans << "\n";

	return 0;
}
