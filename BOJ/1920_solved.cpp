// BOJ 1920
#include <iostream>
#include <algorithm>
#include <vector>

int N, M;
std::vector<int> vec;

bool BinarySerach(int tgtNum)
{
	int begin = 0;		  // included
	int end = vec.size(); // not included
	int mid;

	while (begin < end)
	{
		mid = (begin + end) >> 1; // middle of the range

		if (tgtNum == vec[mid])
		{
			return true;
		}
		else if (tgtNum > vec[mid])
		{
			begin = mid + 1;
		}
		else
		{
			end = mid;
		}
	}
	return false;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N;
	vec.resize(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> vec[i];
	}
	std::sort(vec.begin(), vec.end()); // ascending order
	int input;
	std::cin >> M;
	for (int i = 0; i < M; ++i)
	{
		std::cin >> input;
		if (BinarySerach(input))
		{
			std::cout << "1\n";
		}
		else
		{
			std::cout << "0\n";
		}
	}
}