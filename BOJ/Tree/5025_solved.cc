
/*
	prefix 존재 여부를 판정하는 문제.

	입력되는 문자열의 크기 순서를 알 수 없기 때문에 다음의 두 가지 경우를 고려해야 함.

	자신이 이미 등록된 문자열의 prefix인 경우
		-> branch를 타고 진행만 하고, 그 어떤 expand도 존재하지 않음
*/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using TrieNode = std::unordered_map<char, int>;
using Trie = std::vector<TrieNode>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int testNum, n;
	std::cin >> testNum;
	while (testNum-- > 0)
	{
		std::vector<std::string> strBuffer;
		std::string input;
		Trie t;
		bool resultFlag = true;

		t.push_back(TrieNode());
		std::cin >> n;
		while (n-- > 0)
		{
			std::cin >> input;
			strBuffer.push_back(input);
		}
		std::sort(strBuffer.begin(), strBuffer.end(),
				  [](const std::string &str1, const std::string &str2) -> bool
				  { return str1.size() > str2.size(); });
		for (const std::string &str : strBuffer)
		{
			bool isPrefix = true;
			int curNode = 0;
			for (const char &c : str)
			{
				if (t[curNode].find(c) == t[curNode].end()) // not found, expand
				{
					t[curNode].insert(std::make_pair(c, t.size()));
					t.push_back(TrieNode());
					isPrefix = false;
				}
				// go to next node
				curNode = t[curNode][c];
			}
			// prefix check
			if (isPrefix)
				resultFlag = false;
		}
		if (resultFlag)
			std::cout << "YES\n";
		else
			std::cout << "NO\n";
	}
}
