
/*
	BOJ 2482 색상환

	N과 K가 주어짐.

	N개의 정수 1~N 중에서 서로 인접하지 않게 K개를 뽑아야 함.
	그 가짓수를 구하기.

	====================================================
	대략적인 개요는 알았는데, 문제에서 요구하는 환이라는 환경이 문제임.

	즉 내가 길이 N까지 구한 답(갯수)에 대하여 길이 1을 선택한 경우를 제외해줘야 함.
	즉 맨 앞과 맨 뒤가 동시에 선택되는 경우를 제거해줘야 하는데....

	====================================================

	ex) N = 10, K = 5
	result = 2
	{1 3 5 7 9}, {2 4 6 8 10}

	ex) N = 10, K = 6
	result = 0
	N / K < 2이므로, 무조건 인접이 발생함.

	ex) N = 10, K = 1
	result = 10
	뭐를 뽑아도 중복이 발생하지 않음.

	ex) N = 4, K = 2
	result = 2

	ex) N = 5, K = 2
	result = 5

	ex) N = 5, K = 1
	result = 5

	ex) N = 6, K = 2
	result = 9
*/
#include <iostream>
#include <vector>

using C = std::vector<std::vector<int>>;
constexpr const int MOD = 1000'000'003;

int memoize(C& cache, int n, int k)
{
	// base case
	if (k > (n + 1) / 2) return 0; // 인접하지 않게 k개 못 고름
	else if (k == 0) return 1;	// 아무것도 고르지 않는 경우의 수는 1가지 반드시 존재
	else if (n == 0) return 0;	// 뽑은 원소가 0개 -> 존재하지 않음.
	else if (cache[n][k] != -1)
	{
		// cache hit
		return cache[n][k];
	}

	// cache miss
	return cache[n][k] = (
		memoize(cache, n - 1, k)	// n번째 원소를 선택하지 않음.
		+ memoize(cache, n - 2, k - 1)// n번째 원소를 선택함.
		) % MOD;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K;
	std::cin >> N >> K;
	C cache(N + 1, std::vector<int>(K + 1, -1));

	// 1번 원소를 선택한 경우와 1번 원소를 선택하지 않은 경우
	std::cout << (memoize(cache, N - 1, K) + memoize(cache, N - 3, K - 1)) % MOD;
}