
#include <iostream>
#include <vector>
#include <algorithm>

/*
	input : L, K, C

	L : length of the log
	K : positon to cut the log
	C : maximum count to cut the log

	minimize the maximum length of the cut

	단순 이진탐색일 줄 알았는데, 대단히 공격적인 예외 케이스를 가진, 상당히 사이코같은 문제.
*/

std::pair<long long, bool> cutLog(const std::vector<long long> &pos, const long long maxCutCnt, const long long maxCutLen)
{
	long long cutCnt = 0, prevPos = pos[0], prevCutPos = pos[0], cutSum = 0;
	bool isInRange = true;

	for (int idx = 1; idx < pos.size(); ++idx)
	{
		long long curCutLen = prevPos - pos[idx];
		if (curCutLen > maxCutLen)
		{
			isInRange = false;
			break;
		}
		else if (idx == pos.size() - 1)
		{
			if (cutSum + curCutLen > maxCutLen)
			{
				prevCutPos = prevPos;
				cutCnt++;
			}
		}
		else if (curCutLen + cutSum == maxCutLen)
		{
			prevCutPos = pos[idx];
			cutSum = 0;
			cutCnt++;
		}
		else if (curCutLen + cutSum > maxCutLen)
		{
			prevCutPos = prevPos;
			cutSum = curCutLen;
			cutCnt++;
		}
		else
		{
			cutSum += curCutLen;
		}
		prevPos = pos[idx];
	}
	if (cutCnt < maxCutCnt) // 여유가 있다면, 한 번 더 자를 수 있다!!!!!
	{
		prevCutPos = pos[pos.size() - 2];
	}
	return std::make_pair(prevCutPos, isInRange && (maxCutCnt >= cutCnt));
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int L, K, C;
	std::cin >> L >> K >> C;
	std::vector<long long> pos(K);
	for (int i = 0; i < K; ++i)
		std::cin >> pos[i];
	pos.push_back(0);
	pos.push_back(L);
	std::sort(pos.begin(), pos.end(), std::greater<int>());
	// parametric search, binary search
	int left = 1, right = L + 1, result = 0;
	while (left < right)
	{
		int mid = (left + right) >> 1;
		const auto [firstCut, isOk] = cutLog(pos, C, mid);
		if (isOk)
		{
			result = firstCut;
			right = mid;
		}
		else
		{
			left = mid + 1;
		}
	}
	// print result
	std::cout << left << ' ' << result;
}
