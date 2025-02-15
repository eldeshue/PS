/*
#include<iostream>
#include<cmath>
#include<stack>


class bottles {
private:
	int number_of_bottles; // 물병 수	
	int added_bottle = 0;  // 합쳐진 병의 수
	int limit;             // 물병 수 제한
	
	int order = 23;
	std::stack<int> previous;


public:
	bottles(int n, int k) : number_of_bottles(n), limit(k) {}
	~bottles() {}
	int calculate_extra_bottle() {
		// water보다 작으면서, 가장 큰 2의 지수 찾기
		while (pow(2, order) > number_of_bottles) {
			order--;
		}
		// 하나씩 빼기
		while (added_bottle < limit ) {
			int temp = pow(2, order);
			if (number_of_bottles >= temp) {
				number_of_bottles -= temp;
				previous.push(temp);
				added_bottle++;
				order--;
			}
			else {
				order--;
				continue;
			}			
		}

		if (number_of_bottles > 0) {
			return (previous.top() - number_of_bottles);
		}
		else if (number_of_bottles == 0) {
			return 0;
		}
		else {
			return -1;
		}

	}

};

int main() {
	// input
	int N;
	std::cin >> N;
	int K;
	std::cin >> K;
	bottles data(N, K);
	// output
	std::cout << data.calculate_extra_bottle() << std::endl;
}

*/