
#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>

using node = std::pair<std::string, int>;

// transforms
std::string tA(const std::string& str)	// reverse
{
	std::string result(8, '\0');

	for (int i = 0; i < 8; ++i)
	{
		result[i] = str[7 - i];
	}
	return result;
}

std::string tB(const std::string& str)
{
	std::string result(8, '\0');

	result[0] = str[3];
	for (int i = 1; i < 4; ++i)
	{
		result[i] = str[i - 1];
	}
	result[7] = str[4];
	for (int i = 4; i < 7; ++i)
	{
		result[i] = str[i + 1];
	}
	return result;
}

std::string tC(const std::string& str)
{
	std::string result(str);

	result[1] = str[2];
	result[2] = str[5];
	result[5] = str[6];
	result[6] = str[1];
	return result;
}

std::string tD(const std::string& str)
{
	std::string result(str);

	std::swap(result[0], result[4]);
	return result;
}

// bfs
int bfs(const std::string& goal)
{
	std::queue<node> Q;
	std::unordered_set<std::string> visited;
	std::string str;
	int result = 0;

	Q.push(std::make_pair("12345678", 0));
	while (!Q.empty())
	{
		if (Q.front().first == goal)
			return Q.front().second;	// result
		str = tA(Q.front().first);
		if (visited.find(str) == visited.end())
		{
			visited.insert(str);
			Q.push(make_pair(str, Q.front().second + 1));
		}
		str = tB(Q.front().first);
		if (visited.find(str) == visited.end())
		{
			visited.insert(str);
			Q.push(make_pair(str, Q.front().second + 1));
		}
		str = tC(Q.front().first);
		if (visited.find(str) == visited.end())
		{
			visited.insert(str);
			Q.push(make_pair(str, Q.front().second + 1));
		}
		str = tD(Q.front().first);
		if (visited.find(str) == visited.end())
		{
			visited.insert(str);
			Q.push(make_pair(str, Q.front().second + 1));
		}
		Q.pop();
	}
	// not gonna happen
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string goal(8, '\0');
	for (int i = 0; i < 8; ++i)
	{
		std::cin >> goal[i];
	}
	std::cout << bfs(goal);
}