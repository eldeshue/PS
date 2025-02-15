// int 형 배열로 만들어보고, 가능하면 비트마스크로도 구현해보기
// int* target;
	// 10101010 
	// int pattern_1 = 170;
	// 01010101
	// int pattern_2 = 85;

/*
#include<iostream>

class board {
private:
	int row_limit, colum_limit;
	bool target[50][50];
	bool pattern[9] = { 1,0,1,0,1,0,1,0,1 };
	
public:
	board(int m, int n) : row_limit(m), colum_limit(n) {}
	~board() {}
	void set_board(int i, int j, char value) {
		if (value == 'B') {
			target[i][j] = 1;
		}
		else { // w
			target[i][j] = 0;
		}
	}
	// pattern 1 : 10101010
	int compare_row_pattern1(int target_row, int start_col) {
		int result = 0;
		for (int i = 0; i < 8; i++) {
			if (target[target_row][start_col + i] != pattern[i]) {
				result++;
			}
		}
		return result;
	}
	// pattern 2 : 01010101
	int compare_row_pattern2(int target_row, int start_col) {
		int result = 0;
		for (int i = 0; i < 8; i++) {
			if (target[target_row][start_col + i] != pattern[i + 1]) {
				result++;
			}
		}
		return result;
	}
	// 10101010
	// 01010101 ...
	int compare_board_type1(int start_row, int start_col) {
		int result = 0;

		result += compare_row_pattern1(start_row, start_col);
		result += compare_row_pattern2(start_row + 1, start_col);
		result += compare_row_pattern1(start_row + 2, start_col);
		result += compare_row_pattern2(start_row + 3, start_col);
		result += compare_row_pattern1(start_row + 4, start_col);
		result += compare_row_pattern2(start_row + 5, start_col);
		result += compare_row_pattern1(start_row + 6, start_col);
		result += compare_row_pattern2(start_row + 7, start_col);

		return result;
	}
	// 01010101
	// 10101010...
	int compare_board_type2(int start_row, int start_col) {
		int result = 0;

		result += compare_row_pattern2(start_row, start_col);
		result += compare_row_pattern1(start_row + 1, start_col);
		result += compare_row_pattern2(start_row + 2, start_col);
		result += compare_row_pattern1(start_row + 3, start_col);
		result += compare_row_pattern2(start_row + 4, start_col);
		result += compare_row_pattern1(start_row + 5, start_col);
		result += compare_row_pattern2(start_row + 6, start_col);
		result += compare_row_pattern1(start_row + 7, start_col);

		return result;
	}
	int select_board_and_find_min() {
		int result = 64;

		for (int i = 0; i < row_limit - 7; i++) {
			for (int j = 0; j < colum_limit - 7; j++) {
				int temp1 = compare_board_type1(i, j);
				int temp2 = compare_board_type2(i, j);
				if (temp1 < result) {
					result = temp1;
				}
				if (temp2 < result) {
					result = temp2;
				}
			}
		}

		return result;
	}
	void show() {
		for (int i = 0; i < row_limit; i++) {
			for (int j = 0; j < colum_limit; j++) {
				std::cout << target[i][j];
			}
			std::cout << '\n';
		}
	}

 };

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	// input
	int m, n;
	std::cin >> m >> n;
	board target(m, n);
	// w == 0, b == 1
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			char temp_value;
			std::cin >> temp_value;
			target.set_board(i, j, temp_value);
		}
	}
	//target.show();
	// calculation & output
	std::cout << target.select_board_and_find_min() << '\n';	
}
*/