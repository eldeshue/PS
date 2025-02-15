
/*
	유사 two pointer solution.

	한 ptr는 source 문자열, 한 ptr는 bomb 문자열을 가리킴.



	status라 이름붙인 stack에 bomb의 인덱스를 저장함.

*/
#include <iostream>
#include <string>
#include <deque>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::deque<int> status;

	int bombIdx = 0, srcIdx = 0;
	std::string src, bomb, result;
	std::cin >> src >> bomb;
	const int bombSize = bomb.size();
	for (; srcIdx < src.size(); ++srcIdx)
	{
		if (status.empty() && (src[srcIdx] != bomb[0] || srcIdx + bombSize > src.size()))
		{
			result.push_back(src[srcIdx]);
		}
		else if (src[srcIdx] == bomb[0]) // possible new bomb
		{
			if (bombSize != 1)
				status.push_back(1);
		}
		else if (src[srcIdx] != bomb[status.back()]) // not bomb
		{
			while (!status.empty())
			{
				result.append(bomb.substr(0, status.front()));
				status.pop_front();
			}
			result.push_back(src[srcIdx]);
		}
		else if (src[srcIdx] == bomb[status.back()]) // is bomb
		{
			status.back()++;
			if (status.back() == bombSize)
				status.pop_back();
		}
	}
	while (!status.empty())
	{
		result.append(bomb.substr(0, status.front()));
		status.pop_front();
	}
	if (result == "")
		result = "FRULA";
	std::cout << result;
}
