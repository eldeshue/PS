
/*
	2024.08.23, 정해찬 솔루션 디버깅

	==============================

	1. 오버플로우

	2. 솔루션 fail
		반례 : -10 0 2 3 4 8
		오답 : -10 0 8
		정답 : -10 2 8
*/
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

struct smallResults
{
	int left;
	int right;
	int mid;
	smallResults(int l, int r, int m)
	{
		this->left = l;
		this->right = r;
		this->mid = m;
	}
};

int main(void)
{
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	int n;
	std::cin >> n;
	std::vector<int> myVec(n);
	for (int i = 0; i < n; i++)
	{
		std::cin >> myVec[i];
	}
	std::sort(myVec.begin(), myVec.end());
	std::map<int, smallResults> resultMap;
	int left = 0, right = myVec.size() - 1;
	while (left + 1 < right)
	{
		std::vector<int>::iterator it = std::lower_bound(myVec.begin() + left + 1, myVec.begin() + right, 0 - (myVec[left] + myVec[right]));
		if (it == myVec.begin() + right)
		{
			it--;
		}
		int value = *it;
		if (left + 2 < right)
		{
			if (abs(*it - (myVec[left] + myVec[right])) > abs(*(it - 1) - (myVec[left] + myVec[right])))
			{
				value = *(it - 1);
			}
		}
		int smallResult = myVec[left] + myVec[right] + value;
		resultMap.insert(std::make_pair(abs(smallResult), smallResults(myVec[left], myVec[right], value)));
		if (smallResult > 0)
		{
			right -= 1;
		}
		else
		{
			left += 1;
		}
	}
	std::map<int, smallResults>::iterator resIt = resultMap.begin();
	std::cout << resIt->second.left << ' ' << resIt->second.mid << ' ' << resIt->second.right << std::endl;
	return 0;
}
