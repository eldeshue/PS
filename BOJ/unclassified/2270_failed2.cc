
/*
	  응용 하노이탑 문제

	  잘못 움직인 하노이 탑 문제.
	하노이 탑이라는 문제의 특징이 보다 작은 것을 해결하지 못하면, 그 위의 원소를 움직일 수 없음.

	따라서 위에서부터 정리하면서 내려가야 함.

	-> failed, 풀이 방향이 완전히 다름. 생각 자체가 틀려먹었다...
*/
#include <iostream>
#include <array>
#include <deque>

int N;
std::array<std::deque<int>, 3> hanoiTower;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int f, s, t, temp;
	std::cin >> N >> f >> s >> t;
	for (int i = 0; i < f; ++i)
	{
		std::cin >> temp;
		hanoiTower[0].push_back(temp);
	}
	for (int i = 0; i < s; ++i)
	{
		std::cin >> temp;
		hanoiTower[1].push_back(temp);
	}
	for (int i = 0; i < t; ++i)
	{
		std::cin >> temp;
		hanoiTower[2].push_back(temp);
	}
	// target tower
	int resultTower, topTower;
	for (int i = 0; i < 3; ++i)
	{
		if (hanoiTower[i].front() == N)
			resultTower = i;
		if (hanoiTower[i].back() == 1)
			topTower = i;
	}
	std::cout << resultTower + 1 << '\n';
	for (int i = 0; ; ++i)
	{
		if (hanoiTower[resultTower].front() != N - i)
			break;
		hanoiTower[resultTower].pop_front();
	}
	// move tower
	int result = 0;
	while (!hanoiTower[0].empty()
		|| !hanoiTower[1].empty()
		|| !hanoiTower[2].empty())	// O(N)
	{
		// find mid
		int targetTower;
		if (hanoiTower[(topTower + 1) % 3].empty())
			targetTower = (topTower + 2) % 3;
		else if (hanoiTower[(topTower + 2) % 3].empty())
			targetTower = (topTower + 1) % 3;
		else if (hanoiTower[(topTower + 1) % 3].back() < hanoiTower[(topTower + 2) % 3].back())
			targetTower = (topTower + 1) % 3;
		else
			targetTower = (topTower + 2) % 3;
		// count
		result = (result + (1 << (hanoiTower[targetTower].back() - 1)) - 1) % 1000000;
		// pop
		while (!hanoiTower[topTower].empty() && hanoiTower[topTower].back() < hanoiTower[targetTower].back())
			hanoiTower[topTower].pop_back();
		// update topTower
		topTower = targetTower;
	}
	std::cout << result << '\n';
}
