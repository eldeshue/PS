
/*

	boj 1634, 완전 이진트리

	트리의 레벨이 k -> 트리를 구성하는 노드의 개수가 2 ^ k -> leaf 노드의 개수는 2 ^ (k - 1).
	k가 최대 12이므로, 입력으로 주어지는 두 트리의 leaf의 최대 개수는 2 * 2 ^ (k - 1) = 2 ^ k 임.
	즉 4096

	4096 ^ 2 * 2 -> 대략 32M.

	각 리프 노드들을 순회해면서 키를 패어 <left, right>, 밸류를 dist로 삼는 해시맵을 구성함
	두 해시맵을 비교해서 일치하는 개수를 답으로 삼는다.

*/

#include <iostream>
#include <memory.h>
#include <unordered_set>

int leaf1[4096];
int leaf2[4096];
int dist[4097][4097];

int get_dist_between_node(int lpos, int rpos)
{
	int result = 0;
	while (lpos != rpos)
	{
		lpos >>= 1;
		rpos >>= 1;
		result += 2;
	}
	return result;
}

int main()
{
	std::ios_base ::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(dist, -1, sizeof(dist));

	int K, offset;
	std::cin >> K;
	for (int i = 0; i < 1 << (K - 1); ++i)
	{
		std::cin >> leaf1[i];
	}
	for (int i = 0; i < 1 << (K - 1); ++i)
	{
		std::cin >> leaf2[i];
	}
	// set distance table
	offset = 1 << (K - 1);
	for (int i = 0; i < offset - 1; ++i)
	{
		for (int j = i + 1; j < offset; ++j)
		{
			dist[leaf1[i]][leaf1[j]] = get_dist_between_node(offset + i, offset + j);
			dist[leaf1[j]][leaf1[i]] = dist[leaf1[i]][leaf1[j]];
		}
	}
	std::cout << "----------------------------\n";
	// count
	std::unordered_set<int> result;
	for (int i = 0; i < offset - 1; ++i)
	{
		for (int j = i + 1; j < offset; ++j)
		{
			if (dist[leaf2[i]][leaf2[j]] == get_dist_between_node(offset + i, offset + j))
			{
				result.insert(leaf2[i]);
				result.insert(leaf2[j]);
				std::cout << leaf2[i] << ' ' << leaf2[j] << ' ' << dist[leaf2[i]][leaf2[j]] << '\n';
			}
		}
	}
	// erase exception

	//
	std::cout << "----------------------------\n";
	for (const auto &num : result)
		std::cout << num << ' ';
	std::cout << '\n'
			  << "----------------------------\n";
	//
	std::cout << result.size();
}
