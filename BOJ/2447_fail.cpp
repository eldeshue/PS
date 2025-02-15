/*
#include<iostream>

class matrix {
private:
	int size;
	bool** table;

public:
	matrix(int n) : size(n) {
		table = new bool* [size];
		for (int i = 0; i < size; i++) {
			table[i] = new bool[size];
			for (int j = 0; j < size; j++) {
				table[i][j] = true;
			}
		}
	}
	~matrix() {
		for (int i = 0; i < size; i++) {
			delete[] table[i];
		}
		delete[] table;
	}
	void delete_middle(int start_row, int start_col, int step) {
		// delete middle
		for (int i = start_row + step; i < start_row + step * 2; i++) {
			for (int j = start_col + step; j < start_col + step * 2; j++) {
				table[i][j] = false;
			}
		}
		// call function around the middle
		if (step > 0) {			
			delete_middle(0, 0, step / 3); // by meeting "result", it stopped earlier than expected;
			delete_middle(0, 0 + step, step / 3);
			delete_middle(0, 0 + step * 2, step / 3);
			delete_middle(0 + step, 0, step / 3);
			//
			delete_middle(0 + step, 0 + step * 2, step / 3);
			delete_middle(0 + step * 2, 0, step / 3);
			delete_middle(0 + step * 2, 0 + step, step / 3);
			delete_middle(0 + step * 2, 0 + step * 2, step / 3);
		}
		else {	
			return;			
		}		
	}
	void print_table() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (table[i][j] == 1) {
					std::cout << "*";
				}
				else {
					std::cout << " ";
				}
			}
			std::cout << std::endl;
		}
	}

};


int main() {
	int N = 27;
	//std::cin >> N;
	matrix data(N);

	data.delete_middle(0, 0, N/3);

	data.print_table();
	
}
*/