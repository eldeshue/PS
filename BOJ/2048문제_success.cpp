// �Ｚ���� ����Ʈ���� �������蹮��, 2048����
// 

/*

#include<iostream>
#include<stack>
#include<queue>

class Game_board {
	int board[20][20];
	int length;

public:
	Game_board(int length) : length(length) {
		for (int i = 0; i < length; i++) {

			for (int j = 0; j < length; j++) {
				board[i][j] = 0;
			}
		}
	}

	Game_board(const Game_board& copy) : length(copy.length) { // ���� ������
		
		for (int i = 0; i < length; i++) {
			
			for (int j = 0; j < length; j++) {
				board[i][j] = copy.board[i][j];
			}
		}
	}

	~Game_board() {
		
	}

	Game_board& operator=(const Game_board& copy) {
		length = copy.length;

		for (int i = 0; i < length; i++) {
			for (int j = 0; j < length; j++) {
				board[i][j] = copy.board[i][j];
			}
		}

		return *this;
	}

	int get(int row, int colum ){
		return board[row][colum];
	}

	void set(int row, int colum, int value) {
		board[row][colum] = value;
	}

	void print() {
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < length; j++) {
				std::cout << board[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	int get_max() {
		int max = 0;
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < length; j++) {
				if (max < board[i][j])
					max = board[i][j];
			}
		}

		return max;
	}


	// ������ ���ڵ��� �ش� �������� �����δ�.
	// ���õ� ���� ���ڵ��� ť�� �ְ�, ť�� �� ���ڵ��� ������� �ٽ� �ѷ��ش�.
	// �ѷ��ִ� �������� ���� ���ڵ��̶�� �����ְ�, �׷��� �ʴٸ� �״´�.
	void up_shift() {
		
		// �� ���� �ٺ��� �����δ�.
		for (int colum = 0; colum < length; colum++) { // colum choice
			// ���ڸ� ���� ť�� �غ��Ѵ�. ���Լ���
			std::queue<int> temp;
			for (int row = 0; row < length; row++) {
				// 0�� �ƴ϶��, ť�� �ִ´�.
				if (board[row][colum]) {
					
					temp.push(board[row][colum]);
					board[row][colum] = 0; // ���� �ڸ��� ����.

				}

			}
			// ť�� �� ���ڵ��� ������ ���� ������ �� ��, �ٽ� �迭�� �ִ´�.
			int row = 0;
			while (!temp.empty()) {
				int temp1 = temp.front();
				temp.pop();				
				if (!temp.empty()) {
					if (temp1 == temp.front()) {
						temp1 += temp.front();
						temp.pop();
						board[row][colum] = temp1;
					}
					else {
						board[row][colum] = temp1;
					}
				}
				else {
					board[row][colum] = temp1;
				}
				row++;
			}			
			
		}

	}

	void down_shift() {
		for (int colum = length - 1; colum >= 0; colum--) { // colum choice
			std::queue<int> temp;
			for (int row = length - 1; row >= 0; row--) {
				// 0�� �ƴ϶��, ť�� �ִ´�.
				if (board[row][colum]) {

					temp.push(board[row][colum]);
					board[row][colum] = 0; // ���ڸ��� 0���� ä��.

				}

			}

			int row = length - 1;
			while (!temp.empty()) {
				int temp1 = temp.front();
				temp.pop();
				if (!temp.empty()) {
					if (temp1 == temp.front()) {
						temp1 += temp.front();
						temp.pop();
						board[row][colum] = temp1;
					}
					else {
						board[row][colum] = temp1;
					}
				}
				else {
					board[row][colum] = temp1;
				}
				row--;
			}



		}

	}

	void left_shift() {
		
		for (int row = 0; row < length; row++) { // row choice
			std::queue<int> temp;
			for (int colum = 0; colum < length; colum++) {
				// 0�� �ƴ϶��, ť�� �ִ´�.
				if (board[row][colum]) {

					temp.push(board[row][colum]);
					board[row][colum] = 0; // ���ڸ��� 0���� ä��.

				}

			}
			// ť�� �� ���ڵ��� ������ ���� ������ �� ��, �ٽ� �迭�� ���Ҵ��Ѵ�.
			int colum = 0;
			while (!temp.empty()) {
				int temp1 = temp.front();
				temp.pop();
				if (!temp.empty()) {
					if (temp1 == temp.front()) {
						temp1 += temp.front();
						temp.pop();
						board[row][colum] = temp1;
					}
					else {
						board[row][colum] = temp1;
					}
				}
				else {
					board[row][colum] = temp1;
				}
				colum++;
			}


		}

	}

	void right_shift() {

		for (int row = length - 1; row >= 0; row--) { // row choice
			std::queue<int> temp;
			for (int colum = length - 1; colum >= 0; colum--) {
				// 0�� �ƴ϶��, ť�� �ִ´�.
				if (board[row][colum]) {

					temp.push(board[row][colum]);
					board[row][colum] = 0; // ���ڸ��� 0���� ä��.

				}

			}

			int colum = length - 1;
			while (!temp.empty()) {
				int temp1 = temp.front();
				temp.pop();
				if (!temp.empty()) {
					if (temp1 == temp.front()) {
						temp1 += temp.front();
						temp.pop();
						board[row][colum] = temp1;
					}
					else {
						board[row][colum] = temp1;
					}
				}
				else {
					board[row][colum] = temp1;
				}
				colum--;
			}

		}

	}

	void move(int way) {
		switch (way) {
		case 0:
			up_shift();
			break;
		case 1:
			down_shift();
			break;
		case 2:
			left_shift();
			break;
		case 3:
			right_shift();
			break;
		default:
			std::cout << "wrong order" << std::endl;
			break;
		}
	}

};

class board_tree {
	int depth = 0;
	int* status; // int status[depth] = { width, width, width, ... };
	Game_board now_board;
	std::stack<Game_board> previous_board;
	// stack.push();
	// stack.pop();
	// backtracking �ϸ鼭 pop
	// forwarding �ϸ鼭 push

public:
	board_tree( Game_board original) : now_board(original) {
		status = new int[5];
		for (int i = 0; i < 5; i++) {
			status[i] = 3;
		}
	}

	~board_tree() {
		if (status != nullptr) {
			delete[] status;
			status = nullptr;
			while (!previous_board.empty()) {
				previous_board.pop();
			}
		}
	}

	bool Back_tracking() {
		// ��Ʈ��ŷ, 
		for (int i = 4; i >= 0; i--) {
			now_board = previous_board.top();
			previous_board.pop();
			depth--;

			if (status[i] != 0) {
				status[i]--;				
				return 0;
			}
			else {
				// status[i] == 0;				
				status[i] = 3;				

				if (i != 0) {					
					continue;
				}
				else {
					// ��� status ���� 0�� ���,
					return 1;
				}

			}
		}

	}

	// DFS Ž�� �˰��� ����
	// depth firsht searching ���� �켱 Ž��
	int DFS_search( int* max_value) {

		// 1. ���� Ž��
		// depth�� ������� ������, ���̸� �켱������ Ž���Ѵ�.
		if (depth < 5) {
			previous_board.push(now_board);
			now_board.move(status[depth]);

			depth++;
			return DFS_search(max_value);
		}
		else {
			// 2.��Ʈ��ŷ
			// depth�� 5�� �����ϸ�, �ִ� ����� �����ϰ�, �ǵ�����.

			// �ִ� �� �� ����.
			if (*max_value < now_board.get_max()) {
				*max_value = now_board.get_max();
			}

			switch (Back_tracking()) {
			case false:
				// 3. ȾŽ��
				// ���ο� ��θ� Ž���Ѵ�. 
				return DFS_search(max_value);
			case true:
				// 4. ���� ����
				// status �� ���°� ��� 0�� ���, �����Ѵ�.
				return 0;
			}


		}

		
	}

};

int main() {
	// �Էº�
	// ���� ���� �Է�
	
	int length;
	std::cin >> length;
	Game_board map(length);
	// �ʱ�ȭ
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			int temp;
			std::cin >> temp;
			map.set(i, j, temp);
		}
	}
	
	// test case
	
	//int length = 3;
	//Game_board map(length);
	//for (int i = 0; i < 3; i++) {
	//	map.set(i, 0, 2);
	//	map.set(i, 1, 4);
	//	map.set(i, 2, 8);
	//}
	//map.print();
	//
	//map.move(2);
	//
	//map.print();

	
	
	board_tree B(map);
	int result = 0;
	B.DFS_search(&result);	
	
	std::cout << result << std::endl;

}

*/