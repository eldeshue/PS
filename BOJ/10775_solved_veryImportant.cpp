// 10775�� : ����.
// �����̳� Ǯ�̰� �������� �ʰ�, ������ ������.
// ���Ͽ� ���ε��� Ư���� ���� ���� ���ذ� �����Ǿ�� �ϴ� ����.

// ���Ͽ� ���ε��� ���ε�� �ᱹ �θ� ����Ű�� ������ �����Ų ������� ��.
// �� ���� Ȱ���Ͽ� �������� �Ҵ���(�׸����ϰ� ������ ���� ��)�� ������ �����Ѵ�.
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

