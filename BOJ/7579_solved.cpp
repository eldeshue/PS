/*
	< ���� �賶���� >

	�۵��� �޸𸮿� �� cost�� �־�����, M �̻��� �޸𸮸� ���� ��, �ּ��� cost�� ���ϱ�
	������ ������ �����Ѵ�.
	
	�־��� �۵��� ��ü �޸𸮿��� M�� ���� capacity�Ⱑ �ǰ�,
	�� ���Ŀ��� capacity�� ���� �����鼭 cost�� �ִ밡 �ǵ��� �۵��� �����ϰ�
	
	�� �ִ� cost�� total cost���� ���ָ� M�� �����鼭 �ּ��� cost�� ��.
*/
#include <iostream>
#include <limits>
#include <vector>
#include <array>

#define byte first
#define cost second

using Proc = std::pair<long long, long long>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	long long numApp, neededMem, capacity = 0, totalCost = 0;
	std::cin >> numApp >> neededMem;
	std::vector<Proc> apps(numApp, { 0, 0 });
	for (long long i = 0; i < numApp; ++i)
	{
		std::cin >> apps[i].byte;
		capacity += apps[i].byte;
	}
	capacity -= neededMem;
	for (long long i = 0; i < numApp; ++i)
	{
		std::cin >> apps[i].cost;
		totalCost += apps[i].cost;
	}
	// using dp, solve 01 napsack problem
	long long maxCost = 0;
	std::array<long long, 10001> cache1; // cache[cost] = memory
	std::array<long long, 10001> cache2; // cache[cost] = memory
	std::fill(cache1.begin(), cache1.end(), 2e9);
	std::fill(cache2.begin(), cache2.end(), 2e9);
	std::array<long long, 10001>& curCache = cache1;
	std::array<long long, 10001>& prevCache = cache2;
	curCache[0] = 0;
	prevCache[0] = 0;
	for (long long i = 0; i < numApp; ++i)
	{
		for (long long  curCost = 0; curCost <= 10000; ++curCost)
		{
			if (curCost - apps[i].cost < 2e9)
			{
				curCache[curCost] = std::min(prevCache[curCost],
					prevCache[curCost - apps[i].cost] + apps[i].byte);
				if (curCache[curCost] <= capacity)
					maxCost = std::max(maxCost, curCost);
			}
		}
		std::swap(curCache, prevCache);
	}
	// result, totalCost - maxCost
	std::cout << totalCost - maxCost << '\n';
	return 0;
}