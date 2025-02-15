/*
#include<iostream>

class board {
private:
	int row, col;
	bool data[50][50];
public:
	board(int N, int M) : row(N), col(M) {}
	board(const board& A) : row(A.row), col(A.col) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				this->data[i][j] = A.data[i][j];
			}
		}
	}
	~board(){}
	void set(int i, int j, bool value) {
		data[i][j] = value;
	}
	bool is_same(const board& A) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (this->data[i][j] != A.data[i][j]) {
					return false;
				}
			}
		}
		return true;
	}
	void change(int start_row, int start_col) {
		for (int i = start_row; i < start_row + 3; i++) {
			for (int j = start_col; j < start_col + 3; j++) {
				data[i][j] = !(data[i][j]);
			}
		}
	}
	
};


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	// input
	int N, M;
	std::cin >> N >> M;
	board A(N, M), B(N, M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			bool temp;
			std::cin >> temp;
			A.set(i, j, temp);
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			bool temp;
			std::cin >> temp;
			B.set(i, j, temp);
		}
	}
	// calculation
	// 바꿀수 있는지 없는지
	// 있다면 몇번만에 바꿀 수 있는지


	// output


}

*/