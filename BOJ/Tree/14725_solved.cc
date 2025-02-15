
/*
	트라이

	기존의 트라이와는 다르게 트리의 노드가 하나의 문자열(기존의 트라이는 노드가 문자)

	트라이란 일반적으로 문자열을 검색하기 위해서 만들어낸, 트리 자료구조임.
	임의 개수의 자식을 갖는 트리 자료구조, 일반적으로 해시맵을 사용하여 구현함(안그러면 메모리가 너무 많이 낭비됨.)

	몇개의 자식을 가질 지 예상이 불가능 하기에 하나의 벡터에 트라이를 구성하는 모든 노드를 다 때려넣고,
	노드는 기본적으로 테이블로 구현됨. 테이블의 key - value 관계에서 value로 하여금 자식 노드의 위치를 가리키도록 함.

	트리의 노드는 테이블, 테이블은 배열, 해시맵, 맵으로 구현됨.
	기본적으로 트라이는 루트 노드를 가져야 함.
*/
#include <iostream>
#include <string>
#include <vector>
#include <map> // node of trie should have an order, lexicographical

using trieNode = std::map<std::string, int>;

inline void printTrie(const std::vector<trieNode> &trie, int depth, int curNode) // will be called recursively
{
	for (const auto &strInt : trie[curNode])
	{
		for (int i = 0; i < depth; ++i)
		{
			std::cout << "--";
		}
		std::cout << strInt.first << '\n';
		printTrie(trie, depth + 1, strInt.second);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::vector<trieNode> trie;

	std::string str;
	int N, K, node;
	// input, build trie
	std::cin >> N;
	trie.push_back(trieNode()); // root node of trie
	for (int i = 0; i < N; ++i)
	{
		std::cin >> K;
		node = 0;
		for (int j = 0; j < K; ++j)
		{
			std::cin >> str;
			if (trie[node].find(str) == trie[node].end())
			{
				trie[node].insert(std::make_pair(str, trie.size()));
				trie.push_back(trieNode());
			}
			node = trie[node][str];
		}
	}
	// result, print trie recursively
	printTrie(trie, 0, 0);
}
