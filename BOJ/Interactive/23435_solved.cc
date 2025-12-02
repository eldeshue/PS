
/*
	BOJ 23435

	값을 알 수 없는 배열이 있음.

	주어진 배열에 대해서 대소관계를 질문할 수 있음

	두 번째로 작은 값을 반드시 찾는 알고리즘을 구현하시오

	질문 횟수에는 제한이 존재, N+20임.

	N <= 10^5

	===============================================

	ford-johnson like한 알고리즘

	승자조랑 패자 조를 나눠서 일종의 2진 트리를 만들며며 최솟값 탐색함.

	최솟값한테 패배한 원소들을 비교하면 됨

	트리 만드는데, O(N), 트리 탐색하는데 O(log N)임.
*/
#include <iostream>
#include <vector>
#include <deque>
#include <numeric>


int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::deque<int> indices(N, 0);
	std::vector<std::deque<int>> loosers(N);
	std::iota(indices.begin(), indices.end(), 0);
	while (indices.size() > 1)	// O(N)
	{
		// pop two from front, push 1 back
		int const i = indices[0];
		int const j = indices[1];
		std::cout << "? " << i << ' ' << j << std::endl;
		indices.pop_front();
		indices.pop_front();

		char c;
		std::cin >> c;
		if (c == '<')
		{
			indices.push_back(i);
			loosers[i].push_back(j);
		}
		else // c == '>
		{
			indices.push_back(j);
			loosers[j].push_back(i);
		}
	}

	int const min = indices.front();
	auto& target = loosers[min];
	while (target.size() > 1) // O(log N)
	{
		// pop two from front, push 1 back
		int const i = target[0];
		int const j = target[1];
		std::cout << "? " << i << ' ' << j << std::endl;
		target.pop_front();
		target.pop_front();

		char c;
		std::cin >> c;
		if (c == '<')
		{
			target.push_back(i);
		}
		else // c == '>
		{
			target.push_back(j);
		}
	}

	std::cout << "! " << loosers[min].front() << std::endl;
}
