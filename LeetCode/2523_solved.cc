#include <vector>

using namespace std;

class Solution {
public:
	vector<int> closestPrimes(int left, int right) {
		// 에라토스 테네스의 채를 이용하여 10^6 이하의 소수를 모두 구하고,
		// 이후 left, right의 범위에 대해서 답을 구한다.

		// sieve of erasthosthenese, O(N)
		vector<int> sieve(1000001, -1);
		sieve[0] = 0;
		sieve[1] = 0;
		for (int i = 2; i <= 1000000; ++i)
		{
			if (sieve[i] != -1)
				continue;
			sieve[i] = 1;
			int j = i + i;
			while (j <= 1000000)
			{
				sieve[j] = 0;
				j += i;
			}
		}

		// search result
		vector<int> result(2, -1);
		int last_prime = -1e9, min_dist = 1e9;
		for (int i = left; i <= right; ++i)
		{
			if (sieve[i])
			{
				// update result
				if ((i - last_prime) < min_dist)
				{
					min_dist = i - last_prime;
					result[0] = last_prime;
					result[1] = i;
				}
				// update last prime number
				last_prime = i;
			}
		}
		return result;
	}
};
