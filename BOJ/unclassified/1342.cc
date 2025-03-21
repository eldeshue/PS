
/*
	그래프로 모델링
	주어진 모든 노드를 정해진 횟수만큼 탐색하는데, 이전 노드와 현재 노드가 달라야 함.
*/
#include <iostream>
#include <string>
#include <memory.h>

int N;
int charTable[26];

int dfs(int prevNode)
{
	int result = 0;
	bool baseFlag = true;

	for (int i = 0; i < 26; ++i)
	{
		if (i != prevNode && charTable[i] > 0)
		{
			baseFlag = false;
			charTable[i]--;
			result += dfs(i);
			charTable[i]++;
		}
	}
	if (baseFlag && charTable[prevNode] == 0)
	{
		return 1;
	}
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(charTable, 0, sizeof(charTable));

	std::string str;
	std::cin >> str;
	N = str.size();
	for (const char& c : str)
		charTable[c - 'a']++;
	int result = 0;
	for (int i = 0; i < 26; ++i)
	{
		if (charTable[i] > 0)
		{
			charTable[i]--;
			result += dfs(i);
			charTable[i]++;
		}
	}
	std::cout << result;
}
