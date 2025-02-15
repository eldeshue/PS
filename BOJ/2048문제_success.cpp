// 삼성전자 소프트웨어 역량시험문제, 2048게임
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

	Game_board(const Game_board& copy) : length(copy.length) { // 복사 생성자
		
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


	// 보드의 숫자들을 해당 방향으로 움직인다.
	// 선택된 줄의 숫자들을 큐에 넣고, 큐에 들어간 숫자들을 순서대로 다시 뿌려준다.
	// 뿌려주는 과정에서 같은 숫자들이라면 더해주고, 그렇지 않다면 쌓는다.
	void up_shift() {
		
		// 맨 위에 줄부터 움직인다.
		for (int colum = 0; colum < length; colum++) { // colum choice
			// 숫자를 넣을 큐를 준비한다. 선입선출
			std::queue<int> temp;
			for (int row = 0; row < length; row++) {
				// 0이 아니라면, 큐에 넣는다.
				if (board[row][colum]) {
					
					temp.push(board[row][colum]);
					board[row][colum] = 0; // 뽑은 자리는 지움.

				}

			}
			// 큐에 들어간 숫자들을 다음과 같은 연산을 한 후, 다시 배열에 넣는다.
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
				// 0이 아니라면, 큐에 넣는다.
				if (board[row][colum]) {

					temp.push(board[row][colum]);
					board[row][colum] = 0; // 빈자리는 0으로 채움.

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
				// 0이 아니라면, 큐에 넣는다.
				if (board[row][colum]) {

					temp.push(board[row][colum]);
					board[row][colum] = 0; // 빈자리는 0으로 채움.

				}

			}
			// 큐에 들어간 숫자들을 다음과 같은 연산을 한 후, 다시 배열에 재할당한다.
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
				// 0이 아니라면, 큐에 넣는다.
				if (board[row][colum]) {

					temp.push(board[row][colum]);
					board[row][colum] = 0; // 빈자리는 0으로 채움.

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
	// backtracking 하면서 pop
	// forwarding 하면서 push

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
		// 백트래킹, 
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
					// 모든 status 값이 0인 경우,
					return 1;
				}

			}
		}

	}

	// DFS 탐색 알고리즘 수행
	// depth firsht searching 깊이 우선 탐색
	int DFS_search( int* max_value) {

		// 1. 깊이 탐색
		// depth가 충분하지 않으면, 깊이를 우선적으로 탐색한다.
		if (depth < 5) {
			previous_board.push(now_board);
			now_board.move(status[depth]);

			depth++;
			return DFS_search(max_value);
		}
		else {
			// 2.백트래킹
			// depth가 5에 도달하면, 최댓값 계산을 수행하고, 되돌린다.

			// 최댓값 비교 및 갱신.
			if (*max_value < now_board.get_max()) {
				*max_value = now_board.get_max();
			}

			switch (Back_tracking()) {
			case false:
				// 3. 횡탐색
				// 새로운 경로를 탐색한다. 
				return DFS_search(max_value);
			case true:
				// 4. 종료 조건
				// status 의 상태가 모두 0인 경우, 종료한다.
				return 0;
			}


		}

		
	}

};

int main() {
	// 입력부
	// 행의 길이 입력
	
	int length;
	std::cin >> length;
	Game_board map(length);
	// 초기화
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