
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::vector<std::vector<int>> abcd(4, std::vector<int>(N, 0));
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::cin >> abcd[j][i];
		}
	}
	std::vector<int> abSumVec, cdSumVec;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			abSumVec.push_back(abcd[0][i] + abcd[1][j]);
			cdSumVec.push_back(-abcd[2][i] - abcd[3][j]);
		}
	}
	std::sort(abSumVec.begin(), abSumVec.end());
	std::sort(cdSumVec.begin(), cdSumVec.end());
	int result = 0, abPos = 0, cdPos = 0;
	while (abPos < abSumVec.size() || cdPos < cdSumVec.size())
	{
		// find match
		while (abSumVec[abPos] != cdSumVec[cdPos])
		{
			if (abSumVec[abPos] < cdSumVec[cdPos])
				abPos++;
			else
				cdPos++;
		}
		// count each number
		int abCnt = 0, cdCnt = 0;
		for (; abPos < abSumVec.size() - 1; abPos++)
		{
			abCnt++;
			if (abSumVec[abPos] != abSumVec[abPos + 1])
				break;
		}
		for (; cdPos < cdSumVec.size() - 1; cdPos++)
		{
			cdCnt++;
			if (cdSumVec[cdPos] != cdSumVec[cdPos + 1])
				break;
		}
		// update result
		result += abCnt * cdCnt;
		abPos++;
		cdPos++;
	}
	std::cout << result;
}
