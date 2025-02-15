/*
* 백준 온라인 저지 1105번, 8
* 주어진 범위 내의 숫자들 중, 8을 가장 적게 가진 수와, 8의 갯수찾기

* solution 1.
* 판단 대상이 된 숫자에 대하여, 
* 먼저 10으로 나눈 나머지를 확인하여 8이 있는지를 확인해본다.
* 10으로 나눈 몫을 전달하고, 다시 10으로 나눈 나머지를 확인한다
* 이를 반복하여 8의 갯수를 확인한다.
* fail, 시간 초과

#include<iostream>

int Left, Right;
int temp_result = 0;
int result = 9; // Right < 2000,000,000

int count_8_(int target) {
	if ((target % 10) == 8) {
		temp_result++;
	}
	// 탈출 조건
	if (target < 10) {
		return 0;
	}
	return count_8_(target / 10);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	// input
	std::cin >> Left >> Right;
	// calculation
	for (int i = Left; i <= Right; i++) {
		// i 에 대하여 갯수 검사
		count_8_(i);
		// 최댓값 갱신
		if (temp_result < result) {
			result = temp_result;
		}
		// 임시값 초기화
		temp_result = 0;
	}
	// output
	std::cout << result << '\n';
}

* solution 2.
* 판단의 기준을 간소화 하는 것으로 연산 양을 최소화 시킨다.
* 입력으로 주어진 두 경계값에 대해서 판단한다.

#include<iostream>

int Left, Right;
int temp_result = 0;

int count_int_length(int n, int result = 0) {
	if ((n / 10) > 0) {
		return count_int_length(n / 10, result + 1);
	}
	else {
		return result;
	}
}

int count_8_(int l, int r) {
	// 두 수 l, r의 자릿 수를 확인함
	int s_l = count_int_length(l);
	int s_r = count_int_length(r);
	// 자릿수가 다르다면, 0을 리턴
	if (s_l != s_r) {
		return 0;
	}
	// 자릿수가 같다면,
	// l과 r의 각 자리에 대하여 공유하는 부분에서
	// 8의 갯수를 세어서 출력함
	else {
		int result = 0;
		int den = [](int n)-> int {
			int pow = 1;
			for (int i = 0; i < n; i++) {
				pow *= 10;
			}
			return pow;
		}(s_l);
		for (int i = s_l; i >= 0; --i) {

			int j_l = l / den;
			int j_r = r / den;
			l -= j_l * den;
			r -= j_r * den;
			den /= 10;
			if (j_l == j_r) {
				if (j_l == 8) {
					result++;
				}
			}
			else {
				break;
			}
		}
		return result;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	// input
	std::cin >> Left >> Right;
	
	// test 
	//Left = 8808;
	//Right = 8889;
	 
	// calculation
	std::cout << count_8_(Left, Right) << '\n';
}

*/