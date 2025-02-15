
/*
	2진탐색, why???
	-> 그 정체는 완전 탐색....
		골드 4 답게 쉽게쉽게 생각하자...
*/

#include <iostream>
#include <vector>
#include <algorithm>

int N, M, L, num;

bool is_ok(const std::vector<int>& post, int dist)
{
	int count = 0;
	for (int i = 1; i < post.size(); ++i)
	{
		count += (post[i] - post[i - 1]) / dist;
		if ((post[i] - post[i - 1]) % dist == 0)
			count--;
	}
	return count > M;	// 정확하게 M이 아님
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::vector<int> post;

	// preprocessing
	std::cin >> N >> M >> L;
	post.push_back(0);
	post.push_back(L);		// ????
	for (int i = 0; i < N; ++i)
	{
		std::cin >> num;
		post.push_back(num);
	}
	std::sort(post.begin(), post.end());

	// binary search
	int left = 1, right = L;
	while (left < right)
	{
		int mid = (left + right) >> 1;
		if (is_ok(post, mid))
			left = mid + 1;
		else
			right = mid;
	}
	std::cout << right;
}