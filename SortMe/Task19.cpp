#include <bits/stdc++.h>

int main() {
	int rows_count, columns_count, colors_count;
	std::cin >> rows_count >> columns_count >> colors_count;
	
	std::vector<std::vector<int>> colors(rows_count, std::vector<int>(columns_count));
	for (auto& row : colors) {
		for (auto& color : row) std::cin >> color;
	}
	
	std::vector<std::vector<int>> up_heights(rows_count, std::vector<int>(columns_count, 1));
	for (int i = 1; i < rows_count; ++i) {
		for (int j = 0; j < columns_count; ++j) {
			if (colors[i][j] == colors[i - 1][j]) {
				up_heights[i][j] += up_heights[i - 1][j];
			}
		}
	}
	
	auto calculate_left = [&]() {
		std::vector<std::vector<int>> left_sizes(rows_count, std::vector<int>(columns_count, 1));
		
		for (int i = 0; i < rows_count; ++i) {
			std::vector<std::pair<int, int>> stack;
			for (int j = 0; j < columns_count; ++j) {
				if (0 == j || colors[i][j - 1] != colors[i][j]) {
					stack.clear();
					stack.emplace_back(-1, j - 1);
				}
				
				int height = up_heights[i][j];
				
				while (stack.back().first >= height) {
					stack.pop_back();
				}
				
				left_sizes[i][j] = j - stack.back().second;
				stack.emplace_back(height, j);
			}
		}
			
		return left_sizes;
	};
	
	auto calculate_right = [&]() {
		for (auto& row : colors) std::reverse(row.begin(), row.end());
		for (auto& row : up_heights) std::reverse(row.begin(), row.end());
		
		auto right_sizes = calculate_left();
		
		for (auto& row : colors) std::reverse(row.begin(), row.end());
		for (auto& row : up_heights) std::reverse(row.begin(), row.end());
		
		for (auto& row : right_sizes) std::reverse(row.begin(), row.end());
		
		return right_sizes;
	};
	
	auto left_sizes = calculate_left();
	
	auto right_sizes = calculate_right();
	
	int ans = 0;
	for (int i = 0; i < rows_count; ++i) {
		for (int j = 0; j < columns_count; ++j) {
			int height = up_heights[i][j];
			int width = left_sizes[i][j] + right_sizes[i][j] - 1;
			ans = std::max(ans, height * width);
		}
	}
	
	std::cout << ans << std::endl;
	
	return 0;
}

