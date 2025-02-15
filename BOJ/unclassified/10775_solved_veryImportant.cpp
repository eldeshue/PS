// 10775번 : 공항.
// 구현이나 풀이가 복잡하지 않고, 참으로 간결함.
// 유니온 파인드의 특성에 대한 깊은 이해가 전제되어야 하는 문제.

// 유니온 파인드의 파인드는 결국 부모를 가리키는 과정을 단축시킨 구조라는 점.
// 이 점을 활용하여 다음으로 할당할(그리디하게 추적한 작은 값)을 빠르게 제공한다.
#include <iostream>
#include <memory.h>
#include <vector>

int find(int target_index);

int G, P;
int parent[100001];
int input_g[100000];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> G >> P;
	// initialize parent array, to use disjoint set
	for (int i = 1; i <= G; ++i)
	{
		parent[i] = i;
	}
	// set input
	for (int i = 0; i < P; ++i)
	{
		std::cin >> input_g[i];
	}

	// cal
	int result = 0;
	for (int i = 0; i < P; ++i)
	{
		int nextPos = find(input_g[i]);
		if (nextPos != 0)
		{
			parent[nextPos]--;	// Union, greedy
			result++;
		}
		else
		{
			break;
		}
	}
	std::cout << result;
}

int find(int target_index)
{
	if (parent[target_index] == target_index)
	{	
		return target_index;
	}
	else
	{
		int p = find(parent[target_index]); 
		parent[target_index] = p;
		return p;
	}
}

