
/*

	* boj 1124, under prime

	언더프라임이란 그 자신을 소인수 분해해서 얻은 소수의 개수가 소수인 수
	에라토스테네스의 채를 이용한 문제임.

	채를 초기화하는 과정에서 소수는 0, 소수가 아니라면 그 소인수의 개수로 맞춰줘야 함.

*/
#include <iostream>
#include <memory.h>

int is_prime[100001];

bool is_under_prime(int num)
{
	return (is_prime[is_prime[num]] == 1);
}

// init filter
void make_underprime()
{
	memset(is_prime, 0, sizeof(is_prime));
	for (long long i = 2; i <= 100000; ++i)
	{
		if (is_prime[i] == 0)
			is_prime[i] = 1;
		for (long long j = 2; j <= 100000; ++j)
		{
			if (i * j > 100000)
				break;
			is_prime[i * j] = is_prime[i] + is_prime[j];
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int start, end, result = 0;
	std::cin >> start >> end;
	make_underprime();
	for (int i = start; i <= end; ++i)
	{
		if (is_under_prime(i))
			result++;
	}
	std::cout << result;
}
