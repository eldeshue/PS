
/*
	longest bitonic subsequence

	dp를 두 번 수행하면 됨.
*/
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<int> A(N);
	std::vector<int> cache1(N), cache2(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> A[i];
	}
	// first dp, increasing subseq from 0 to N, O(N ^ 2)
	for(int curPos = 0; curPos < N; ++curPos)
	{
		cache1[curPos] = 0;
		for (int prevPos = 0; prevPos < curPos; ++prevPos)
		{
			if (A[prevPos] < A[curPos] && cache1[prevPos] > cache1[curPos])
			{
				cache1[curPos] = cache1[prevPos];
			}
		}
		cache1[curPos]++;
	}
	// second dp, increasing subseq from N -1 to 0, O(N ^ 2)
	for(int curPos = N - 1; curPos >= 0; --curPos)
	{
		cache2[curPos] = 0;
		for (int prevPos = N - 1; prevPos > curPos; --prevPos)
		{
			if (A[prevPos] < A[curPos] && cache2[prevPos] > cache2[curPos])
			{
				cache2[curPos] = cache2[prevPos];
			}
		}
		cache2[curPos]++;
	}
	// get result
	int result = 0;
	for (int i = 0; i < N; ++i)
	{
		result = std::max(result, cache1[i] + cache2[i] - 1);
	}
	std::cout << result;
}
