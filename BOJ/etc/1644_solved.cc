

#include <iostream>
#include <algorithm>
#include <vector>

constexpr int MAX = 4000001;
bool prime[MAX];

// 일정 간격으로 특정 불린값으로 바꾸는 인라인 함수
inline void change_bool(int strt, int acc, bool flag)
{
	for (int i = strt; i < MAX; i += acc)
	{
		prime[i] = flag;
	}
}

void eratosthenes()
{
	std::fill_n(prime, MAX, false); // 배열을 초기화한다.
	prime[2] = true;				// 2는 소수다.
	prime[3] = true;				// 3은 소수다. 이러면 5 이상의 홀수만 판별하면 된다.
	// 5 (mod 6) 과 1 (mod 6)을 참으로 설정한다. 이들은 2의배수도 아니고 3의 배수도 아닌 숫자집합이다.
	// 단, 1은 소수가 아니기에 1 (mod 6)은 7부터 시작한다.
	change_bool(5, 6, true);
	change_bool(7, 6, true);

	for (int i = 5, j = 25; j < MAX;)
	{
		int nxt = (i - 3) % 6; // 현재의 i가 5 (mod 6) 이면 2, 1 (mod 6) 이면 4가 된다.
		if (prime[i] == true)
		{
			int addi = i * 6; // i를 6배로 하여 x (mod 6)인 수만 검색하게 한다.

			// i * i 이상의 수를 지워나간다. 어차피 이 미만의 수들은 이미 소수 여부가 판별되었다.
			change_bool(j, addi, false);

			// 이전 루프에서 누락된 부분을 마저 지워나간다.
			change_bool(nxt * i + j, addi, false); // nxt * i + j == i * ( i + nxt)
		}
		// 다음 루프 진행을 위한 준비. 현재의 i가 5 (mod 6) 이면 2를, 1 (mod 6)이면 4를 더한다.
		i += nxt;
		j = i * i;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	eratosthenes();
	std::vector<int> primeNums;
	for (int i = 0; i < 4000000; ++i)
	{
		if (prime[i])
			primeNums.push_back(i);
	}
	// two pointer
	int fast = 0, slow = 0, sum = 0, result = 0;
	for (; fast < primeNums.size(); ++fast)
	{
		sum += primeNums[fast];
		while (sum > N)
			sum -= primeNums[slow++];
		if (sum == N)
			result++;
	}
	std::cout << result;
}
