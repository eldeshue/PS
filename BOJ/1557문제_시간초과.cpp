// 백준 1557번 문제, 제곱 ㄴㄴ 수
// 제곱 ㄴㄴ 수란, 1이 아닌 제곱 수로 나누어 지지 않는 수이다.
// 즉 해당 수는 1이 아닌 제곱 수를 인자로 갖지 않는 수를 말한다.


#include<iostream>
#include<vector>
#include<cmath>

class K {
private:
	int k, now_square_nn; // now_square_nn 현재 구한 잠재적 제곱 ㄴㄴ수
	int previous_square_nn = 2;
	int biggest_square_yy = 0; // 지금까지 찾은 가장 큰 제곱 ㅇㅇ수	
	int previous_j = 1;

	int previous_max_prime = 2;
	std::vector<int> prime;

public:
	K(int k) :k(k),now_square_nn(k) {
		prime.push_back(2);
	};
	~K() {};

	bool check_prime(int target) {
		
		for (const auto& p : prime) {
			if (target % p == 0) {
				//소수가 아니라면, false
				return false;
			}
		}
		//소수가 맞다면, true
		return true;
	}

	void Find_new_prime() {
		// sqrt(now_square_nn) 보다 작은 새로운 소수를 찾아서 
		// 해당 소수를 찾으면 prime에 추가한다.

		for (int i = previous_max_prime; i < std::sqrt(now_square_nn); i++) {
			if (check_prime(i)) {
				prime.push_back(i);
				previous_max_prime = i;
			}

		}

	}

	bool check_square_yy(int target) {
		// 해당 숫자가 제곱ㅇㅇ 이면 true를 반환하기
		for (const auto& prime_num : prime) {
			if (target % (prime_num * prime_num) == 0) {
				return true;
			}
		}
		return false;
	}

	// 재귀적으로 확인 및 체크.
	int Find_square_nn() {
		
		int new_square_yy_num = 0;
		// 새로운 소수 찾기
		Find_new_prime();

		//for ( const auto& i : prime) {
		//	for (int j = previous_j; i * i * j <= now_square_nn; j++) {
		//		if (i * i * j > biggest_square_yy) {
		//			previous_j = j;
		//			biggest_square_yy = i * i * j;
		//			new_square_yy_num++;
		//		}				
		//	}
		//}

		// previous_square_nn 과 now_square_nn 사이의 square_yy를 찾아서 추가하면 됨.
		int i = previous_square_nn + 1;
		while (i <= now_square_nn) {
			if (check_square_yy(i)) { // yy이면 추가
				new_square_yy_num++;
			}
			i++;
		}


		// 입력받은 k 에 대하여, k보다 작은 제곱수의 배수들을 모두 제외한다.
		// 즉, 제외한 수 만큼 result에 더해준다.
		// 더해준 result에는 새로운 제곱 ㅇㅇ 수가 포함된다.
		// 다시 걸러주어야 마땅하다.
		previous_square_nn = now_square_nn;
		now_square_nn += new_square_yy_num;
		// 만약 현재 제곱ㄴㄴ수가 k번째가 확실하다면, 
		// 추가로 찾아지는 제곱 ㅇㅇ 수가 없다면
		// loop를 탈출한다.
		if (new_square_yy_num == 0) {
			return now_square_nn;
		}
		else {			
			return Find_square_nn();
		}
	}
};


int main() {
	// 입력
	int k;	
	std::cin >> k;
	//k = 1234567; // 
	// 초기값 설정
	K solution(k);

	// 구현
	// 문제는 입력받은 k번째에 해당하는 제곱 ㄴㄴ수를 찾기를 바란다.
	// k 까지의 수 중에서 제곱을 인자로 갖는 수의 갯수만큼을 더한다.
	// 더한 수 중에서 제곱을 인자로 갖는 수의 갯수만큼을 더한다.
	// 
	// 작은 순서부터, 제곱을 인자로 갖는 수, 제곱 ㅇㅇ수를 찾는다
	// 제곱ㅇㅇ 수 : 4 8 9 12 16 18 20 24 25 ....

	// 입력받은 k 에 대하여, k보다 작은 제곱수의 배수들을 모두 제외한다.
	// 제외한 수 만큼 k에 더해준다.

	// 출력
	std::cout << solution.Find_square_nn();
	
}



