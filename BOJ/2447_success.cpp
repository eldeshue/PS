/*
#include<iostream>

void print(bool n) {
	if (n) {
		std::cout << "*";
	}
	else {
		std::cout << " ";
	}
}

void check_and_print_star(int row, int col, int order) {
	if (((row / order) == 1) && ((col / order) == 1)) {
		print(false);
		return;
	}
	else if (order == 1) {
		print(true);
		return;
	}
	else {
		return check_and_print_star(row % order, col % order, order / 3);
	}
}

int main() {
	//input
	int N;
	std::cin >> N;

	int row, col;
	for (row = 0; row < N; row++) {
		for (col = 0; col < N; col++) {
			check_and_print_star(row, col, N / 3);
		}
		std::cout << std::endl;
	}

}
*/