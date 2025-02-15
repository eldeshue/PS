
#include <iostream>
#include <memory.h>
#include <string>
#include <map>
#include <vector>

int test, numConnect;
std::map<std::string, int> nameToID;
int parent[200001];

int find(int target_index);
void Union(int node1, int node2);

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string str[2];
	std::cin >> test;
	for (int i = 0; i < test; ++i)
	{
		memset(parent, -1, sizeof(parent));
		nameToID.clear();
		
		int nextIndex = 0;
		std::cin >> numConnect;
		for (int j = 0; j < numConnect; ++j)
		{
			std::cin >> str[0] >> str[1];
			for (int k = 0; k < 2; ++k)
			{
				// if new friend, add 
				if (nameToID.find(str[k]) == nameToID.end())
				{
					nameToID.insert(std::make_pair(str[k], nextIndex++));
				}
			}

			// union
			Union(nameToID[str[0]], nameToID[str[1]]);
			// find
			std::cout << std::abs(parent[find(nameToID[str[0]])]) << "\n";
		}
	}
}

int find(int target_index)
{
	if (parent[target_index] < 0)
	{	// 크기가 1이고, 부모이므로, 자기 자신 하나
		return target_index;
	}
	else
	{
		int p = find(parent[target_index]); // recursively
		parent[target_index] = p;
		return p;
	}
}

void Union(int node1, int node2)
{
	node1 = find(node1);
	node2 = find(node2);

	if (node1 == node2)	// 이미 같은 부모임
	{
		return;
	}

	// 둘의 부모가 다르다
	// 두 노드 모두 부모를 찾았으므로, parent값이 음수임
	// 크기가 작은 트리가 크기가 큰 트리의 밑으로 들어가야 함.
	// 즉 보다 작은 쪽을 부모로
	if (parent[node1] < parent[node2])
	{
		parent[node1] += parent[node2];
		parent[node2] = node1;
	}
	else
	{
		parent[node2] += parent[node1];
		parent[node1] = node2;
	}
}

